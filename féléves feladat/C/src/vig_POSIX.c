#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

#include "vig_POSIX.h"

#define NORMALIZE_MAX_THREADS (MAX_THREADS / 2)

void POSIX(Vigenere* vigenere_data)
{
    Normalize_task to_code_task;
    Normalize_task keyword_task;
    Code_task encode;
    pthread_t thread;

    init_normalize_task(&to_code_task, vigenere_data->to_code, 0, strlen(vigenere_data->to_code));
    init_normalize_task(&keyword_task, vigenere_data->keyword, 0, strlen(vigenere_data->keyword));

    pthread_create(&thread, NULL, normalize_POSIX, &to_code_task);
    normalize_POSIX(&keyword_task);
    pthread_join(thread, NULL);

    init_code_task(&encode, vigenere_data, 0, strlen(vigenere_data->to_code));
    code_POSIX(&encode);
}

void init_normalize_task(Normalize_task* task, char* text, unsigned long start,  unsigned long end)
{ 
    task->text = text;
    task->start_index = start;
    task->end_index = end;
}

void init_code_task(Code_task* task, Vigenere* vigenere_data, unsigned long start, unsigned long end)
{
    task->vigenere_data = vigenere_data;
    task->start_index = start;
    task->end_index = end;
}

void normalize_POSIX(Normalize_task* task)
{
    remove_nonalpha(task->text);
    toupper_string_POSIX(task);
}

void toupper_string_POSIX(Normalize_task* main_task)
{
    unsigned long text_length = strlen(main_task->text);
    long max_threads = (text_length < NORMALIZE_MAX_THREADS ? text_length : NORMALIZE_MAX_THREADS);
    unsigned long index_diffs = text_length / max_threads, start_ind = 0;
    Normalize_task thread_tasks[max_threads - 1];
    unsigned long i;
    pthread_t threads[max_threads-1];

    for (i = 0; i < max_threads - 1; i++)
    {
        init_normalize_task(&thread_tasks[i], main_task->text, start_ind, start_ind + index_diffs);
        pthread_create(&threads[i], NULL, toupper_part_POSIX, &thread_tasks[i]);
        start_ind += index_diffs;
    }
    main_task->start_index = start_ind;
    toupper_part_POSIX(main_task);
    for (i = 0; i < max_threads-1; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void toupper_part_POSIX(Normalize_task* task)
{
    unsigned long i;
    for (i = task->start_index; i<task->end_index; i++)
    {
        task->text[i] = toupper(task->text[i]);
    }
}

void code_POSIX(Code_task* main_task)
{
    unsigned long text_length = strlen(main_task->vigenere_data->to_code);
    unsigned long index_diffs = text_length / MAX_THREADS, start_ind = 0;
    Code_task thread_tasks[MAX_THREADS - 1];
    unsigned long i;
    pthread_t threads[MAX_THREADS - 1];
    for (i = 0; i < MAX_THREADS - 1; i++)
    {
        init_code_task(&thread_tasks[i], main_task->vigenere_data, start_ind, start_ind + index_diffs);
        pthread_create(&threads[i], NULL, code_part_POSIX, &thread_tasks[i]);
        start_ind += index_diffs;
    }
    main_task->start_index = start_ind;
    code_part_POSIX(main_task);
    
    for (i = 0; i < MAX_THREADS - 1; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void code_part_POSIX(Code_task* task)
{
    unsigned long keyword_length = strlen(task->vigenere_data->keyword);
    unsigned long i, keyword_index;
    for (i = task->start_index; i < task->end_index; i++)
    {
        keyword_index = i % keyword_length;
        if (task->vigenere_data->to_code[i] >= 'A' && task->vigenere_data->to_code[i] <= 'Z')
        {
            task->vigenere_data->to_code[i] = code_letter(task->vigenere_data->to_code[i], task->vigenere_data->keyword[keyword_index]);
        }
    }
}