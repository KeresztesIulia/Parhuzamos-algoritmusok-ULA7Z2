#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "gen.h"
#include "vig_sequential.h"
#include "vig_openMP.h"
#include "vig_POSIX.h"


void write_to_file(const char* text_to_write, const char* path);
void time_to_file(unsigned long n, double seq_time, double omp_time, double posix_time, const char* path);

int main()
{
    Vigenere vigenere_data;
    char* plaintext_path = "texts/plaintext.txt";
    char* coded_path = "texts/codedtext.txt";
    char time_by_textsize_path[50];
    char* time_by_threads_openMP_path = "times/time_by_threads_openMP.txt";
    char* time_by_threads_POSIX_path = "times/time_by_threads_POSIX.txt";
    clock_t start, end;
    double seq_time, omp_time, POSIX_time;
    unsigned long original_text_length;


    snprintf(time_by_textsize_path, 50, "times/time_by_textsize_%luthreads.txt", MAX_THREADS);
    init_vigenere_data(&vigenere_data, plaintext_path);
    original_text_length = strlen(vigenere_data.to_code) - 1;    

    // sequential
    start = clock();
    sequential(&vigenere_data);
    end = clock();
    seq_time = (end-start)/(double)CLOCKS_PER_SEC;
    printf("seq:    %.20lfs\n", seq_time);

    free(vigenere_data.to_code);
    free(vigenere_data.keyword);

    //openMP
    init_vigenere_data(&vigenere_data, plaintext_path);

    start = clock();
    openMP(&vigenere_data);
    end = clock();
    omp_time = (end-start)/(double)CLOCKS_PER_SEC;
    printf("openMP: %.20lfs\n", omp_time);

    free(vigenere_data.to_code);
    free(vigenere_data.keyword);

    // POSIX
    init_vigenere_data(&vigenere_data, plaintext_path);

    start = clock();
    POSIX(&vigenere_data);
    end = clock();
    POSIX_time = (end-start)/(double)CLOCKS_PER_SEC;
    printf("POSIX:  %.20lfs\n", POSIX_time);

    write_to_file(vigenere_data.to_code, coded_path);
    time_to_file(original_text_length, seq_time, omp_time, POSIX_time, time_by_textsize_path);

    free(vigenere_data.to_code);
    free(vigenere_data.keyword);
    
    printf("end %d", MAX_THREADS);
}

void write_to_file(const char* text_to_write, const char* path)
{
    FILE* file = fopen(path, "w");
    if (file == NULL)
    {
        printf("ERROR: %s\n", path);
        return;
    }
    fputs(text_to_write, file);
    fclose(file);
}

void time_to_file(unsigned long n, double seq_time, double omp_time, double posix_time, const char* path)
{
    FILE* file = fopen(path, "a");
    if (file == NULL)
    {
        printf("ERROR: %s\n", path);
        return;
    }
    fprintf(file, "%lu:\t\t%.10lf\t%.10lf\t%.10lf\n", n, seq_time, omp_time, posix_time);
    fclose(file);
}