#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "gen.h"

void init_vigenere_data(Vigenere* vigenere_data, char* path)
{
    vigenere_data->max_plaintext_length = 1000000001;
    vigenere_data->max_keyword_length = 1000;

    vigenere_data->to_code = malloc(sizeof(char) * vigenere_data->max_plaintext_length);
    vigenere_data->keyword = malloc(sizeof(char) * vigenere_data->max_keyword_length);

    read_from_file(vigenere_data, path);
}

void read_from_file(Vigenere* vigenere_data, char* path)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        printf("FILE OPEN ERROR!\n");
    }
    fgets(vigenere_data->to_code, vigenere_data->max_plaintext_length, file);
    fgets(vigenere_data->keyword, vigenere_data->max_keyword_length, file);
    fclose(file);
}

void remove_nonalpha(char* string)
{
    long string_length = strlen(string), i, j;
    j = 0;
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

char code_letter(const char letter_to_code, const char key_letter)
{
    char coded;
    coded = letter_to_code + key_letter - 'A';
    if (coded > 'Z')
    {
        coded = 'A' + (coded - 'Z') - 1;
    }
    return coded;
}

