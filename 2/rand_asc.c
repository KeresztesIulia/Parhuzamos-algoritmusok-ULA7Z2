#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float nr_read(float min, float max);
float rand_nr(int min, int max);
void gen_asc_rand(float* array, int array_size, float min, float max);
void print_array(float* array, int array_size);
int is_asc(float* array, int array_size);
int bin_search(float* array, int array_size, float nr_to_search);
int bin_search_recursive(float* array, int array_size, float nr_to_search, int start, int end);
void write_times(const char* path, int n, clock_t bin_start, clock_t bin_end, clock_t bin_rec_start, clock_t bin_rec_end);

int main()
{
    int n = 10000, is_asc_array, bin_i, bin_rec_i;
    clock_t bin_start, bin_end, bin_rec_start, bin_rec_end;
    float rand_nrs[n], nr_to_search;
    int min = 0, max = 1000;
    char* path = "txt/rand_asc_times.txt";
    
    gen_asc_rand(rand_nrs, n, min, max);
    print_array(rand_nrs, n);
    if(is_asc(rand_nrs, n) == 0)
    {
        printf("\nA tomb nem novekvo sorrendu.\n");
    }
    else
    {
        printf("\nA tomb novekvo sorrendu.\n");
    }
    printf("Milyen szamot keressunk meg? ");
    nr_to_search = nr_read(0, RAND_MAX);

    bin_start = clock();
    bin_i = bin_search(rand_nrs, n, nr_to_search);
    bin_end = clock();

    bin_rec_start = clock();
    bin_rec_i = bin_search_recursive(rand_nrs, n, nr_to_search, 0, n-1);
    bin_rec_end = clock();

    printf("bin_search: %d, bin_search_recursive: %d ", bin_i, bin_rec_i);
    write_times(path, n, bin_start, bin_end, bin_rec_start, bin_rec_end);
}

float nr_read(float min, float max)
{
    int ok;
    float nr;
    do
    {
        ok = 1;
        scanf("%f", &nr);
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
    int interval = max-min;
    return (rand() / (float)RAND_MAX) * interval + min;
}

void gen_asc_rand(float* array, int array_size, float min, float max)
{
    float nr;
    int i;
    //valamiért nem úgy megy nagy elemszámra mint kéne
    for (i = 0; i < array_size; i++)
    {
        nr = rand_nr(min, max);
        array[i] = nr;
        min = nr+0.01;
        if (nr+1 > RAND_MAX)
        {
            max = RAND_MAX;
        }
        else
        {
            max = nr+1;
        }
    }
}

void print_array(float* array, int array_size)
{
    int i;
    for (i = 0; i < array_size; i++)
    {
        printf("%.10f ", array[i]);
    }
}

int is_asc(float* array, int array_size)
{
    int i;
    for (i = 0; i < array_size-1; i++)
    {
        if (array[i] > array[i+1])
        {
            return 0;
        }
    }
    return 1;
}

int bin_search(float* array, int array_size, float nr_to_search)
{
    int start = 0, end = array_size-1, array_mid = (start + end)/2;
    while (start != end && array[array_mid] != nr_to_search)
    {
        if (array[array_mid] < nr_to_search)
        {
            start = array_mid;
        }
        else
        {
            end = array_mid;
        }
        array_mid = (start + end) / 2;
        if (array_mid == start)
        {
            printf(" %f ", array[start]);
            if (array[end] == nr_to_search)
            {
                return end;
            }
            else if (array[start] == nr_to_search)
            {
                return start;
            }
            else
            {
                return -1;
            }
        }
    }
    if (start == end && array[start] == nr_to_search)
    {
        return start;
    }
    else if (start == end && array[start] != nr_to_search)
    {
        return -1;
    }
    else
    {
        return array_mid;
    }
}

int bin_search_recursive(float* array, int array_size, float nr_to_search, int start, int end)
{
    int array_mid = (start + end)/2;
    if (start < 0 || end > array_size-1)
    {
        printf("Nem megfelelo hatarok!\n");
        return -2;
    }
    if (array[array_mid] == nr_to_search)
    {
        return array_mid;
    }
    if (start == array_mid)
    {
        if (array[end] == nr_to_search)
        {
            return end;
        }
        else if (array[start] == nr_to_search)
        {
            return start;
        }
        else
        {
            return -1;
        }
    }

    if (array[array_mid] < nr_to_search)
    {
        start = array_mid;
    }
    else if (array[array_mid] > nr_to_search)
    {
        end = array_mid;
    }
    return bin_search_recursive(array, array_size, nr_to_search, start, end);

    if (start != end && array[array_mid] != nr_to_search)
    {
        if (array[array_mid] < nr_to_search)
        {
            start = array_mid;
        }
        else
        {
            end = array_mid;
        }
        array_mid = (start + end) / 2;
        if (array_mid == start)
        {
            if (array[end] == nr_to_search)
            {
                return end;
            }
            else
            {
                return -1;
            }
        }
    }
    if (start == end && array[start] == nr_to_search)
    {
        return start;
    }
    else if (start == end && array[start] != nr_to_search)
    {
        return -1;
    }
    else
    {
        return array_mid;
    }
}

void write_times(const char* path, int n, clock_t bin_start, clock_t bin_end, clock_t bin_rec_start, clock_t bin_rec_end)
{
    FILE* file = fopen(path, "a");
    double bin_time = (double)(bin_start - bin_end) / CLOCKS_PER_SEC;
    double bin_rec_time = (double)(bin_rec_start - bin_rec_end) / CLOCKS_PER_SEC;

    if (file == NULL)
    {
        printf("Sikertelen fajl megnyitas.\n");
        return;
    }

    fprintf(file, "%d: %.20lf   %.20lf\n", n, bin_time, bin_rec_time);
    fclose(file);
}

