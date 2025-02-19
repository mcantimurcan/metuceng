#include "the1.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

std::pair<int, int> partition(unsigned short* A, int size, long& swap) {
    int i = 1, j = 1, k = size - 1;
    unsigned short pivot = A[0];
    while (j <= k) {
        if (A[j] == pivot) {
            j++;
        } else if (A[j] < pivot) {
            std::swap(A[i], A[j]);
            i++;
            j++;
            swap++;
        } else {
            std::swap(A[j], A[k]);
            k--;
            swap++;
        }
    }
    std::swap(A[i-1], A[0]);
    swap++;
    return std::make_pair(i-1, j);
}

void quick_sort(
    unsigned short* arr,
    unsigned int size,
    long& swap,
    unsigned int& recursive_calls) {

    if (size <= 1) return;

    auto [left, right] = partition(arr, size, swap);

    recursive_calls++;
    quick_sort(arr, left, swap, recursive_calls);

    recursive_calls++;
    quick_sort(arr + right, size - right, swap, recursive_calls);
}

std::pair<unsigned short, unsigned int> quick_select_3_helper(
    unsigned short* arr,
    unsigned int size,
    unsigned int index,
    long& swap,
    unsigned int& recursive_calls) {
        
    if (size == 0) {
        return std::make_pair(0, recursive_calls);
    }
    
    if (size == 1) {
        return std::make_pair(arr[0], recursive_calls);
    }
        
    auto [left, right] = partition(arr, size, swap);
    
    if (index < left) {
        recursive_calls++;
        return quick_select_3_helper(arr, left, index, swap, recursive_calls);
    } else if (index < right) {
        return std::make_pair(arr[index], recursive_calls);
    } else {
        recursive_calls++;
        return quick_select_3_helper(arr + right, size - right, index - right, swap, recursive_calls);
    }
}


std::pair<unsigned short, unsigned int> select_k_with_quick_sort3(unsigned short *arr,
                                                                  const unsigned int size,
                                                                  const unsigned int index,
                                                                  long &swap){
    unsigned int recursive_calls = 0;
    recursive_calls++;
    quick_sort(arr, size, swap, recursive_calls);
    return std::make_pair(arr[index], recursive_calls);
}


std::pair<unsigned short, unsigned int> quick_select3(unsigned short *arr,
                                                      const unsigned int size,
                                                      const unsigned int index,
                                                      long &swap){
    // your code here
    unsigned int recursive_calls = 0;
    recursive_calls++;
    return quick_select_3_helper(arr, size, index, swap, recursive_calls);
}
