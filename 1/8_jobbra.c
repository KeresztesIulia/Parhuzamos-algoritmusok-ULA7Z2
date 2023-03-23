#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int n = 10, max_len = 8, i, j;
    srand(time(0));
    for(i = 0; i<n; i++)
    {
        int n_digits, rand_nr = rand();
        printf("             ");
        if(rand_nr != 0)
        {
            n_digits = floor(log10(rand_nr))+1;
        }
        else
        {
            n_digits = 1;
        }
        for(j = 0; j<n-n_digits; j++)
        {
            printf("0");
        }
        printf("%d\n", rand_nr);
    }
}