#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

const int MAX_THREADS = 8;

pthread_mutex_t n_threads_mutex = PTHREAD_MUTEX_INITIALIZER;
int n_threads = 1;

typedef struct Task
{
  double* array;
  int start;
  int end;
  int count;
} Task;

int nr_read(int min, unsigned int max);
float rand_nr(int min, int max);
double* gen_rand(unsigned int size, int min, int max);
void t_count_posix(Task* task);
int t_count_iter(double* array, unsigned int size);
int times_to_file(const char* path, clock_t rec_start, clock_t rec_end, clock_t iter_start, clock_t iter_end, int n);


int main()
{
    unsigned int n, count, max_n;
    char* path = "txt/t_count_times.txt";
    Task task;
    clock_t rec_start, rec_end, iter_start, iter_end;
    max_n = 9999999999;
    printf("Mennyi tombelem legyen? ");
    n = nr_read(1, max_n);
    task.array = gen_rand(n, -500, 500);

    if (task.array == NULL)
    {
        return -1;
    }

    task.start = 0;
    task.end = n-1;
    task.count = 0;
    
    rec_start = clock();
    t_count_posix(&task);
    rec_end = clock();

    iter_start = clock();
    count = t_count_iter(task.array, n);
    iter_end = clock();

    printf(" rec: %d\niter: %d\n", task.count, count);
    return times_to_file(path, rec_start, rec_end, iter_start, iter_end, n);

}

int nr_read(int min, unsigned int max)
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

double* gen_rand(unsigned int size, int min, int max)
{
    int interval=min-max;
    int i;
    double* array;

    if (max<=min)
    {
        printf("Helytelen intervallum");
        return NULL;
    }

    array = (double*)malloc(size * sizeof(double));
    srand(time(0));
    for (i = 0; i < size; i++)
    {
        array[i] = rand_nr(min, max);
    }
    return array;
}

void t_count_posix(Task* task)
{
    int count = 0, mid;
    Task task1, task2;
    pthread_t thread;

    if (task->start == task->end)
    {
        task->count = task->array[task->start] < 0;
    }
    else
    {
        mid = (task->start + task->end) / 2;
        task1.array = task->array;
        task2.array = task->array;
        task1.start = task->start;
        task1.end = mid;
        task2.start = mid + 1;
        task2.end = task->end;

        pthread_mutex_lock(&n_threads_mutex);

        if (n_threads < MAX_THREADS)
        {
            pthread_create(&thread, NULL, t_count_posix, &task1);
            n_threads++;
            pthread_mutex_unlock(&n_threads_mutex);

            t_count_posix(&task2);
            pthread_join(thread, NULL);

            pthread_mutex_lock(&n_threads_mutex);
            n_threads--;
            pthread_mutex_unlock(&n_threads_mutex);
        }
        else
        {
            pthread_mutex_unlock(&n_threads_mutex);
            t_count_posix(&task1);
            t_count_posix(&task2);
        }
        task->count = task1.count + task2.count;
    }
}

int t_count_iter(double* array, unsigned int size)
{
    int count = 0, i;
    for (i = 0; i < size; i++)
    {
        if (array[i] < 0)
        {
            count++;
        }
    }
    return count;
}

int times_to_file(const char* path, clock_t rec_start, clock_t rec_end, clock_t iter_start, clock_t iter_end, int n)
{
    FILE* file = fopen(path, "a");
    double rec_time, iter_time;
    if (file == NULL)
    {
        printf("Sikertelen fajl megnyitasa.\n");
        return -1;
    }

    rec_time = (double)(rec_end-rec_start)/CLOCKS_PER_SEC;
    iter_time = (double)(iter_end-iter_start)/CLOCKS_PER_SEC;
    fprintf(file, "%d: rec_time - %lf, iter_time - %lf\n", n, rec_time, iter_time);
    fclose(file);
    return 0;
}