#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int is_prime(int nr)
{
    int i;
    for (i = 2; i <= sqrt(nr); i++)
    {
        if (nr % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int results_to_file(const char* path, int nrs_checked, double time)
{
    FILE* file = fopen(path, "a");
    if (file == NULL)
    {
        printf("File megnyitasi hiba!\n");
        return -1;
    }
    fprintf(file, "%d: %4.20lf\n", nrs_checked, time);
    fclose(file);
    return 0;
}

int main()
{
    int n = 2000000, i, n_primes = 0;
    clock_t start, end;
    char* path = "txt/n_primes_time.txt";

    start = clock();
    for (i=1; i<=n; i++)
    {
        if (is_prime(i) == 1)
        {
            n_primes++;
        }
    }
    end = clock();
    printf("Primszamok szama az [1, %d] intervallumon: %d.\n", n, n_primes);
    return results_to_file(path, n, (double)(end-start)/CLOCKS_PER_SEC);
}