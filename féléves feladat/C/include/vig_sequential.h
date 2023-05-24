#ifndef VIGENERE_SEQUENTIAL_H
#define VIGENERE_SEQUENTIAL_H

#include "gen.h"

void sequential(Vigenere* vigenere_data);
void normalize_sequential(char* string);
void remove_nonalpha(char* string);
void toupper_string_sequential(char* string);
void code_sequential(char* to_code, const char* keyword);

#endif