#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARGUMENTS 2
#define INT_BASE 2

// reads the file and prints out its contents
int main(int argc, char *argv[]){
    
    // no files are specified 
    if (argc < REQUIRED_ARGUMENTS){
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    char *line = NULL;
    char prev_char;
    size_t lineBufferLength = 0;
    int i, j;
    int count = 0;

    // read until all arguments are exahuseted
    for(i = 1; i < argc; i++){
        
        fp = fopen(argv[i], "r");

        // fopen() fails
        if(fp == NULL){
            printf("wzip: cannot open file\n");
            exit(1);
        }

        //initialisation, prev_char is set to the first 
        //character of the first file
        if(i == 1){
            prev_char = (char) fgetc(fp);
            fseek(fp, 0, SEEK_SET);
        }

        while(getline(&line, &lineBufferLength, fp) != -1){
            for(j = 0;j<strlen(line); j++){
                if(line[j] != prev_char){
                    fwrite(&count, sizeof(int), 1, stdout);
                    fwrite(&prev_char, sizeof(char), 1, stdout);
                    count = 1;
                } else {
                    count++;
                }
                prev_char = line[j];
            }
        }

        //last character of the last file has been reached
        //perform a final output
        if (i == argc - 1) {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&prev_char, sizeof(char), 1, stdout);
        }

        fclose(fp);
    }

    return 0;
}