//
// Created by zhuguoliang on 2019-04-10.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#include <chrono>
#include <iostream>


#define DO_PREFETCH

int binarySearch(int *array, int number_of_elements, int key) {
    int low = 0, high = number_of_elements - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
#ifdef DO_PREFETCH
        // low path
            __builtin_prefetch (&array[(mid + 1 + high)/2], 0, 1);
            // high path
            __builtin_prefetch (&array[(low + mid - 1)/2], 0, 1);
#endif

        if (array[mid] < key)
            low = mid + 1;
        else if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            high = mid - 1;
    }
    return -1;
}

int main() {
    int SIZE = 1024 * 1024 * 512;
    int *array = (int *) malloc(SIZE * sizeof(int));
    //auto array = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }
    int NUM_LOOKUPS = 1024 * 1024 * 8;
    srand(time(NULL));
    int *lookups = (int *) malloc(NUM_LOOKUPS * sizeof(int));
    //auto lookups = malloc(NUM_LOOKUPS * sizeof(int));
    for (int i = 0; i < NUM_LOOKUPS; i++) {
        lookups[i] = rand() % SIZE;
    }


    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_LOOKUPS; i++) {
        int result = binarySearch(array, SIZE, lookups[i]);
    }

    auto end_time = std::chrono::high_resolution_clock::now();


//    auto elapse = start_time-end_time;
    double elapse = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() /
                    static_cast<double>(1e9);

    std::cout << "test elapsed for " << elapse << "seconds \n";
    free(array);
    free(lookups);
}