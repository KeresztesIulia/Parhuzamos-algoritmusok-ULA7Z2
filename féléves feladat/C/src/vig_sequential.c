#include "vig_sequential.h"

#include <string.h>
#include <ctype.h>


void sequential(Vigenere* vigenere_data)
{
    normalize_sequential(vigenere_data->to_code);
    normalize_sequential(vigenere_data->keyword); 
    code_sequential(vigenere_data->to_code, vigenere_data->keyword);    
}

void normalize_sequential(char* string)
{
    remove_nonalpha(string);
    toupper_string_sequential(string);
}

void toupper_string_sequential(char* string)
{
    long string_length = strlen(string), i;
    for (i = 0; i<string_length; i++)
    {
        string[i] = toupper(string[i]);
    }
}

void code_sequential(char* to_code, const char* keyword)
{
    long text_length = strlen(to_code), keyword_length = strlen(keyword);
    long i, keyword_index;
    for (i = 0; i < text_length; i++)
    {
        keyword_index = i % keyword_length;
        if (to_code[i] >= 'A' && to_code[i] <= 'Z')
        {
            to_code[i] = code_letter(to_code[i], keyword[keyword_index]);
        }
    }
}
