#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARGUMENTS 2

// reads the file and prints out its contents
int main(int argc, char *argv[]){
    
    // no files are specified 
    if (argc < REQUIRED_ARGUMENTS){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    FILE *fp;
    char *line = NULL;
    size_t lineBufferLength = 0;

    // read from stdin if no file name is given
    if(argc == REQUIRED_ARGUMENTS){
        while(getline(&line, &lineBufferLength, stdin) != -1){
            if(strstr(line, argv[1])){
                printf("%s", line);
            }
        }
    }
    
    // read until all arguments are exahuseted
    for(int i = REQUIRED_ARGUMENTS; i < argc; i++){
        
        fp = fopen(argv[i], "r");

        // fopen() fails
        if(fp == NULL){
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        while(getline(&line, &lineBufferLength, fp) != -1){
            // check if line contains the search argument
            if(strstr(line, argv[1])){
                printf("%s", line);
            }
        }

        fclose(fp);
    }

    return 0;
}