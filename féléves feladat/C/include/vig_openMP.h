#ifndef VIGENERE_OPENMP_H
#define VIGENERE_OPENMP_H

#include "gen.h"

void openMP(Vigenere* vigenere_data);
void normalize_openMP(char* string);
void toupper_string_openMP(char* string);
void code_openMP(char* to_code, const char* keyword);

void remove_nonalpha_openMP(char* string);

#endif