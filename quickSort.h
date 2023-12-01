#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <functional>
#include "Scores.h"

using namespace std;

template<typename T>
void quickSorts(vector<T>& data, int low, int high, function<bool(const T&, const T&)> compare) {
    // Base case
    if (low >= high) {
        return;
    }

    // Random index for pivot
    int index = low + rand() % (high - low + 1);

    // Pivot moved to the end
    swap(data[index], data[high]);
    T pivot = data[high];

    // Partition
    int i = low - 1;
    for (int j = low; j < high; j++) {
        // If values j is lower than pivot
        if (compare(data[j], pivot)) {
            i++;
            // Swap values at i and j
            swap(data[i], data[j]);
        }
    }

    // Move pivot to correct position
    swap(data[i + 1], data[high]);

    // Recursive sort left of pivot
    quickSorts(data, low, i, compare);

    // Recursive sort right of pivot
    quickSorts(data, i + 2, high, compare);
}

#endif