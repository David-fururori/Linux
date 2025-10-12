
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error, arguments count\n";
        exit(1);
    }


    int fd1 = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd1 == -1) {
        perror("Error open file");
        exit(1);
    }
    
    int fd2 = dup(fd1);
    if(fd2 == -1) {
        perror("Dup error");
        exit(1);
    }
    
    const char* line1 = "line 1\n";
    ssize_t bytes_write1 = write(fd1, line1, 11);
    
    if(bytes_write1 == -1) {
        perror("Error writing");
        close(fd1);
        close(fd2);
        exit(1);
    }
    
    const char* line2 = "line 2\n";
    ssize_t bytes_write2 = write(fd2, line2, 12);
    if(bytes_write2 == -1) {
        perror("Error writing");
        close(fd1);
        close(fd2);
        exit(1);
    }
    
    close(fd1);
    close(fd2);
    
    return 0;
}
