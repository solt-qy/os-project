#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARGUMENTS 2
#define INT_BASE 2

// reads the file and prints out its contents
int main(int argc, char *argv[]){
    
    // no files are specified 
    if (argc < REQUIRED_ARGUMENTS){
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    int num;
    char character;
    int i, j;

    // read until all arguments are exahuseted
    for(i = 1; i < argc; i++){
        
        fp = fopen(argv[i], "r");

        // fopen() fails
        if(fp == NULL){
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        while(fread(&num, sizeof(int), 1, fp) == 1 &&
              fread(&character, sizeof(char), 1, fp) == 1) {
                for (j = 0; j < num; j++){
                    printf("%c", character);
                }
            }

        fclose(fp);
    }

    return 0;
}