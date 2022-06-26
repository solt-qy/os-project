#include <stdio.h>
#include <stdlib.h>

#define REQUIRED_ARGUMENTS 2
#define MAX_LINE_LENGTH 256

// reads the file and prints out its contents
int main(int argc, char *argv[]){
    
    // no files are specified 
    if (argc < REQUIRED_ARGUMENTS){
        exit(0);
    }

    char *buffer = (char *) malloc(sizeof(char)*MAX_LINE_LENGTH);
    
    for(int i = 1; i < argc; i++){
        FILE *fp;
        fp = fopen(argv[i], "r");

        // fopen() fails
        if(fp == NULL){
            printf("wcat: cannot open file\n");
            exit(1);
        }

        while(fgets(buffer, MAX_LINE_LENGTH, fp) != NULL){
            printf("%s", buffer);
        }
        
        fclose(fp);
    }

    free(buffer);

    return 0;
}