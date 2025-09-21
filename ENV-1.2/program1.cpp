#include <iostream>
#include <cstdlib>

int max(int a, int b){
    if (a > b){
	return a;
    }
    return b;
}

int min(int a, int b){
    if (a < b){
	return a;
    }
    return b;
}


int main (int args, char* argv[]) {
     if (args != 4) {
        std::cout << "Usage: " << argv[0] << " a b c\n";
        return 1;
    }
    
    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    int c = std::atoi(argv[3]);
    
    std::cout << "max: " << max(a, max(b, c)) << " min: " << min(a, min(b, c));
    return 0;
}
