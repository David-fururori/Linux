
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
    if (argc < 3){
        perror("Error, need 2 file name");
        return 1;
    }
    
    const char* file_name1 = argv[1];
    const char* file_name2 = argv[2];
    
    std::ifstream in(file_name1, std::ios::binary);
    if (!in){
        std::cerr << "Error, we can't open file";
        return 1;
    }
    
    std::ofstream out(file_name2, std::ios::binary);
    if (!out){
        std::cerr << "Error, we can't open file";
        return 1;
    }
    
    out << in.rdbuf();
    
    out.close();
    in.close();
    
    std::cout << "Code Nice";
    return 0;
}
