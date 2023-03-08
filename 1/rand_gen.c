#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    srand(time(0));
    printf("%d", rand());
}