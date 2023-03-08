#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    srand(time(0));
    int n = 10, max_len = 8;
    for(int i = 0; i<n; i++)
    {
        printf("             ");
        int rand_nr = rand();
        int nr_len;
        if(rand_nr != 0)
        {
            nr_len = floor(log10(rand_nr))+1;
        }
        else
        {
            nr_len = 1;
        }
        for(int j = 0; j<n-nr_len; j++)
        {
            printf("0");
        }
        printf("%d\n", rand_nr);
    }
}