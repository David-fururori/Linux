#include <iostream>
#include <pthread.h>
#include <ctime>

unsigned long seed = 1;
const int MY_INT_MAX = 2147483647;

int my_rand() {
    seed = seed * 1058261969 + 13569;
    return seed % MY_INT_MAX;
}

int toNumber(const char* s) {
    
    int result = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
    
    return result;
}

struct ThreadData {
    int* arr;
    long long result;
    int start;
    int end;
};


void* thread_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    
    for (int i = data->start; i < data->end; i++) {
        sum += data->arr[i];
    }
    
    data->result = sum;
    return nullptr;
}

long long single_sum(int* arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    return sum;
}



int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error count argument\n";
        return 1;
    }

    int n = toNumber(argv[1]);
    int m = toNumber(argv[2]);

    int* arr = new int[n];
    for (int i = 0; i < n; i++){
        arr[i] = my_rand();
    }


    clock_t t1 = clock();
    long long s1 = single_sum(arr, n);
    clock_t t2 = clock();
    double time_single = double(t2 - t1) / CLOCKS_PER_SEC;

    pthread_t* threads = new pthread_t[m];
    ThreadData* tdata = new ThreadData[m];

    int chunk = n / m;

    clock_t t3 = clock();

    for (int i = 0; i < m; i++) {
        tdata[i].arr = arr;
        tdata[i].start = i * chunk;
        
        if (i == m - 1) {
            tdata[i].end = n;
        } 
        else {
            tdata[i].end = (i + 1) * chunk;
        }
        
        pthread_create(&threads[i], nullptr, thread_sum, &tdata[i]);
    }

    long long total = 0;
    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], nullptr);
        total += tdata[i].result;
    }

    clock_t t4 = clock();
    double time_multi = double(t4 - t3) / CLOCKS_PER_SEC;

    std::cout << "Time spent without threads: " << time_single << "\n";
    std::cout << "Time spent with " << m << " threads: " << time_multi << "\n";

    delete[] arr;
    delete[] threads;
    delete[] tdata;

    return 0;
}
