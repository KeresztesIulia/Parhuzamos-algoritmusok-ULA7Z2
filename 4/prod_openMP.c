#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <omp.h>

#define N_THREADS = 10;

int nr_read(int min, int max);
double rand_nr(double min, double max);
int gen_rand(double* array, int size, double min, double max);
double prod_iterative(double* array, int size);
double prod_openMP_for(double* array, int size);
double prod_openMP_reduction(double* array, int size);
double calc_time(clock_t start, clock_t end);
int times_to_file(const char* path, int n, double iter_time, double openMP_time, double openMP_red_time);


int main()
{
    int n;
    double prod_iter, prod_OpenMP, prod_red;
    double iter_time, for_time, red_time;
    clock_t start, end;
    char* path = "txt/prod_times.txt";
    printf("Mennyi eleme legyen a tombnek? ");
    n = nr_read(1, 999999999);
    double nr_array[n];
    gen_rand(nr_array, n, 0.7, 1.32);

    start = clock();
    prod_iter = prod_iterative(nr_array, n);
    end = clock();
    iter_time = calc_time(start, end);

    start = clock();
    prod_OpenMP = prod_openMP_for(nr_array, n);
    end = clock();
    for_time = calc_time(start, end);

    start = clock();
    prod_red = prod_openMP_reduction(nr_array, n);
    end = clock();
    red_time = calc_time(start, end);

    printf("openMP: %lf\n  iter: %lf\n   red: %lf\n", prod_OpenMP, prod_iter, prod_red);
    printf("iter_time: %lf, openfor_time: %lf, red_time: %lf\n", iter_time, for_time, red_time);
    times_to_file(path, n, iter_time, for_time, red_time);
}

int nr_read(int min, int max)
{
    int ok, nr;
    do
    {
        ok = 1;
        scanf("%d", &nr);
        if (nr<min || nr>max)
        {
            printf("Hatarokon kivul eso input. Ujra!\n");
            ok=0;
        }
    } while (!ok);
    return nr;
}

double rand_nr(double min, double max)
{
    double interval=max-min;
    return (rand()/(double)RAND_MAX)*interval+min;
}

int gen_rand(double* array, int size, double min, double max)
{
    int i;
    if (max<=min)
    {
        printf("Helytelen intervallum");
        return -2;
    }

    srand(time(0));
    for (i = 0; i < size; i++)
    {
        array[i] = rand_nr(min, max);
    }
    return 0;
}

double prod_iterative(double* array, int size)
{
    double prod = 1;
    int i;
    for (i = 0; i < size; i++)
    {
        prod *= array[i];
    }
    return prod;
}
double prod_openMP_for(double* array, int size)
{
    double prod = 1;
    int i;
    #pragma omp for
    for (i = 0; i < size; i++)
    {
        prod *= array[i];
    }
    return prod;
}

double prod_openMP_reduction(double* array, int size)
{
    double prod = 1;
    int i;
    #pragma omp parallel for reduction (*:prod)
    for (i = 0; i < size; i++)
    {
        prod *= array[i];
    }
    return prod;
}

double calc_time(clock_t start, clock_t end)
{
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int times_to_file(const char* path, int n, double iter_time, double openMP_time, double openMP_red_time)
{
    FILE* file = fopen(path, "a");
    if (file == NULL)
    {
        printf("Sikertelen fajl megnyitasa.\n");
        return -1;
    }

    fprintf(file, "%d: iter_time - %lf, openMP_for_time - %lf, openMP_red_time: %lf\n", n, iter_time, openMP_time, openMP_red_time);
    fclose(file);
    return 0;
}