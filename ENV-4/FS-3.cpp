
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Error, arguments count\n";
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY);
    if(fd == -1) {
        perror("Error, can't open file");
        exit(1);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if(size == -1) {
        perror("Error function Lseek No1");
        close(fd);
        exit(1);
    }

    if(lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error function Lseek No2");
        close(fd);
        exit(1);
    }

    size_t BUFFER_SIZE = 4096;
    std::vector<char> buffer(BUFFER_SIZE, 0);


    off_t all_write = 0;
    while(all_write < size) {
        size_t count_write = BUFFER_SIZE;
        if(size - all_write < BUFFER_SIZE) {
            count_write = size - all_write;
        }

        ssize_t written = write(fd, buffer.data(), count_write);
        if(written == -1) {
            perror("Write error");
            close(fd);
            return 1;
        }
        all_write += written;
    }

    close(fd);


    if(unlink(argv[1]) == -1) {
        perror("Delete error");
        exit(1);
    }

    return 0;
}
