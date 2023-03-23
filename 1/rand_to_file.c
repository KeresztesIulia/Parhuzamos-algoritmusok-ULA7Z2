#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nr_read(int min, int max);
float rand_nr(int min, int max);
int gen_rand(int nr, int min, int max, const char* path);

int main()
{
    int n, err;
    char c;
    char* path;
    
    printf("Hova legyen generalva a fajl? ");
    scanf(" %s", path);
    printf("Hany ertek legyen generalva? ");
    n = nr_read(0, 999999999);

    err = gen_rand(n, -RAND_MAX, RAND_MAX, path);

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

float rand_nr(int min, int max)
{
    int interval=max-min;
    return (rand()/(float)RAND_MAX)*interval+min;
}

int gen_rand(int nr, int min, int max, const char* path)
{
    int interval=min-max;
    int i;
    char* time_path = "txt/to_file_times.txt";
    clock_t start, end;
    FILE* save_file = fopen(path, "w");
    FILE* time_file = fopen(time_path, "a");
    if (save_file == NULL)
    {
        printf("Sikertelen filebeolvasas.\n");
        return -1;
    }
    if (max<=min)
    {
        printf("Helytelen intervallum");
        return -2;
    }

    srand(time(0));
    start = clock();
    for (i = 0; i < nr; i++)
    {
        float the_rand_nr = rand_nr(min, max);
        fprintf(save_file, "%.2f ", the_rand_nr);
    }
    end = clock();
    fprintf(time_file, "%d: %.20lf", nr, (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    fclose(save_file);
    end = clock();
    fprintf(time_file, ",  %.20lf\n", nr, (double)(end-start)/CLOCKS_PER_SEC);

    fclose(time_file);
    return 0;
}