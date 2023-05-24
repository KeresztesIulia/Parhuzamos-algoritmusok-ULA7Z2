#ifndef GEN_VIGENERE_H
#define GEN_VIGENERE_H

/**
 * General functions and struct for Vigenere coding (used by the iterative and the parallel algorithm)
*/

#define MAX_THREADS 20

typedef struct Vigenere
{
    unsigned long max_plaintext_length;
    unsigned long max_keyword_length;
    char* to_code;
    char* keyword;
} Vigenere;


void init_vigenere_data(Vigenere* vigenere_data, char* path);
void read_from_file(Vigenere* vigenere_data, char* path);
void remove_nonalpha(char* string);
char code_letter(const char letter_to_code, const char key_letter);


#endif
