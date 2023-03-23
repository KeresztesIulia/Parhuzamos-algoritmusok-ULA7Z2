#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int nr_read(int min, int max);
float rand_nr(int min, int max);
int gen_rand(int nr, int min, int max, const char* path);
int read_rands(char* path, int* array, int arr_size);
void print_array(int array[], int size);

int main()
{
    int n, a, b, err;
    
    char* path = "txt/rand_nrs.txt";

    printf("Hany szam legyen generalva?\n");
    n = nr_read(1, 999999999);

    int rands[n];
    
    printf("Also hatar?\n");
    a = nr_read(-RAND_MAX, RAND_MAX);

    printf("Felso hatar?\n");
    b = nr_read(a+1, RAND_MAX);

    err = gen_rand(n, a, b, path);
    if (err != 0) return err;
    err = read_rands(path, rands, n);
    if (err != 0) return err;
    print_array(rands, n);

    return 0;
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
    FILE* file = fopen(path, "w");
    if (file == NULL)
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
    for (i = 0; i < nr; i++)
    {
        float the_rand_nr = rand_nr(min, max);
        printf("%.2f\n", the_rand_nr);
        fprintf(file, "%.2f ", the_rand_nr);
    }
    fclose(file);
    return 0;
}

int read_rands(char* path, int* array, int arr_size)
{
    int i = 0;
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Sikertelen fajl megnyitasa!\n");
        return -1;
    }

    while (fscanf(file, "%d ", &array[i]) != '\0' && i<arr_size) //????
    {
        printf(" %d   ", array[i]);
        i++;
    }
    fclose(file);
    return 0;
}

void print_array(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++) // && array[i] != NULL?
    {
        printf("%d ", array[i]);
    }
    
}
