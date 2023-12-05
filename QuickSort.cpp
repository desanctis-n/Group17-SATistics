#include "Scores.h"

// ---------------------- QUICKSORT FUNCTIONS ----------------------- //

void Scores::quickSortHelper(vector<Report*>& arr, int low, int high, const string &sortCriteria) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high, sortCriteria);
        quickSortHelper(arr, low, partitionIndex - 1, sortCriteria);
        quickSortHelper(arr, partitionIndex + 1, high, sortCriteria);
    }
}
int Scores::partition(vector<Report*>& arr, int low, int high, const string &sortCriteria) {
    Report* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j]->criteriaToValue[sortCriteria] >= pivot->criteriaToValue[sortCriteria]) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
