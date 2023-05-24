#ifndef VIGENERE_POSIX_H
#define VIGENERE_POSIX_H

#include "gen.h"

typedef struct Normalize_task
{
    char* text;
    unsigned long start_index;
    unsigned long end_index;
} Normalize_task;

typedef struct Code_task
{
    Vigenere* vigenere_data;
    unsigned long start_index;
    unsigned long end_index;
} Code_task;

void POSIX(Vigenere* vigenere_data);
void init_normalize_task(Normalize_task* task, char* text, unsigned long start, unsigned long end);
void normalize_POSIX(Normalize_task* task);
void toupper_string_POSIX(Normalize_task* main_task);
void toupper_part_POSIX(Normalize_task* task);

void init_code_task(Code_task* task, Vigenere* vigenere_data, unsigned long start, unsigned long end);
void code_POSIX(Code_task* main_task);
void code_part_POSIX(Code_task* task);


#endif