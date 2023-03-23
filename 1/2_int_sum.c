#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int a, b, sum;
    clock_t start, finish;
    srand(time(0));
    a=rand();
    b=rand();

    printf("Mennyi a kovetkezo osszeg?\n%d + %d = ", a, b);
    start = clock();
    scanf("%d", &sum);
    finish = clock();
    
    printf("Az osszeg kiszamitasara %lf masodpercre volt szuksege, ", (double)(finish-start)/CLOCKS_PER_SEC);
    if(sum == a+b)
    {
        printf("es a valasz helyes.\n");
    }
    else
    {
        printf("a helyes valasz azonban %d.\n", a+b);
    }
}