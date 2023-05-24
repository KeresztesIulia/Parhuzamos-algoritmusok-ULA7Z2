#include "vig_openMP.h"

#include <string.h>
#include <omp.h>
#include <ctype.h>

void openMP(Vigenere* vigenere_data)
{
    omp_set_num_threads(MAX_THREADS / 2);

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            normalize_openMP(vigenere_data->to_code);
 
            #pragma omp section
            normalize_openMP(vigenere_data->keyword);
        }
    }
    #pragma omp barrier

    omp_set_num_threads(MAX_THREADS);
    code_openMP(vigenere_data->to_code, vigenere_data->keyword);   
}

void normalize_openMP(char* string)
{
    remove_nonalpha_openMP(string);
    toupper_string_openMP(string);
}

void toupper_string_openMP(char* string)
{
    long string_length = strlen(string), i;
    #pragma omp parallel for
    for (i = 0; i<string_length; i++)
    {
        string[i] = toupper(string[i]);
    }
}

void code_openMP(char* to_code, const char* keyword)
{
    long text_length = strlen(to_code), keyword_length = strlen(keyword);
    long i, keyword_index;

    
    #pragma omp parallel for private(keyword_index)
    for (i = 0; i < text_length; i++)
    {
        keyword_index = i % keyword_length;
        if (to_code[i] >= 'A' && to_code[i] <= 'Z')
        {
            to_code[i] = code_letter(to_code[i], keyword[keyword_index]);
        }
    }
}

void remove_nonalpha_openMP(char* string)
{
    long string_length = strlen(string), i, j;
    j = 0;
    #pragma omp parallel for
    for (i = 0; i < string_length; i++)
    {
        if (isalpha(string[i]))
        {
            string[j] = string[i];
            j++;
        }
    }
    string[j] = '\0';
}