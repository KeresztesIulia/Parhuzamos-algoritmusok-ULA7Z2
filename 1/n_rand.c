#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nr_read(int min, int max)
{
    int ok;
    int nr;
    do
    {
        ok = 1;
        scanf("%d", &nr);
        if(nr<min || nr>max)
        {
            printf("Hatarokon kivul eso input. Ujra!\n");
            ok=0;
        }
        

    }while(!ok);
    return nr;
}

void gen_rand(int nr, int min, int max)
{
    int interval=min-max;
    srand(time(0));
    FILE* file = fopen("rand_nrs.txt", "w");

    for(int i=0; i<nr; i++)
    {
        float rand_nr = (rand()/(float)RAND_MAX)*interval+min+1;
        printf("%.2f\n", rand_nr);
        fprintf(file, "%.2f\n", rand_nr);
    }

    fclose(file);
}

int main()
{
    int n, a, b;
    printf("Hany szam legyen generalva?\n");
    n = nr_read(1, 999999999);
    
    printf("Also hatar?\n");
    a=nr_read(-999999999,RAND_MAX);

    printf("Felso hatar?\n");
    b=nr_read(a, RAND_MAX);


    gen_rand(n, a, b);
    

}

