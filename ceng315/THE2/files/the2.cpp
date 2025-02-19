#include "the2.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int calculate_char_value(const std::string& str, int start, int end) {
    int key = 0;
    for (int i = start; i <= end; ++i) {
        key *= 27;
        if (i < static_cast<int>(str.length())) {
            key += str[i] - 'A' + 1;
        } else {
            key += 0;
        }
    }
    return key;
}

long counting_sort(std::string* arr, int size, int key_count, int start, int end, bool ascending, long &iterations) {
    int* count = new int[key_count]();
    std::vector<std::string> output(size);

    for (int i = 0; i < size; ++i) {
        int key = calculate_char_value(arr[i], start, end);
        count[key]++;
        iterations++;
    }

    if (ascending) {
        for (int i = 1; i < key_count; ++i) {
            count[i] += count[i - 1];
            iterations++;
        }
    } else {
        for (int i = key_count - 2; i >= 0; --i) {
            count[i] += count[i + 1];
            iterations++;
        }
    }

    for (int i = size - 1; i >= 0; --i) {
        int key = calculate_char_value(arr[i], start, end);
        output[count[key] - 1] = arr[i];
        count[key]--;
        iterations++;
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
        iterations++;
    }

    delete[] count;
}

long multi_digit_string_radix_sort(std::string* arr,
                                   const int size,
                                   const bool ascending,
                                   const int group_size) {
    long total_iterations = 0;

    int max_length = 0;
    for (int i = 0; i < size; i++) {
        max_length = std::max(max_length, static_cast<int>(arr[i].length()));
    }

    for (int pos = max_length - 1; pos >= 0; pos -= group_size) {
        int start = std::max(0, pos - group_size + 1);
        int end = pos;
        int current_group_length = end - start + 1;

        int key_count = 1;
        for (int i = 0; i < current_group_length; i++) {
            key_count *= 27;
        }

        counting_sort(arr, size, key_count, start, end, ascending, total_iterations);
    }

    return total_iterations;
}





