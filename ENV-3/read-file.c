#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc < 2){
        perror("Error, we don't get fail");
        return 1;
    }
    
    const char* file_read = argv[1];
    
    FILE *file = fopen(file_read, "r");
    if (file == NULL){
        perror("Error, file is null");
        return 1;
    }
    
    int count = 256;
    char buffer[count + 1];
    
    int i;
    while ((i = fread(buffer, 1, count, file)) > 0){
        buffer[i] = '\0';
        printf("%s", buffer);
    }
    
    
    fclose(file);
    return 0;
}
