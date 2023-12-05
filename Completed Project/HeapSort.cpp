#include "Scores.h"

// ---------------------- HEAPSORT FUNCTIONS ----------------------- //

Scores::Heap::Heap() {

}
vector<Scores::Report*> Scores::Heap::extractMax(Report*& val, string& sortCriteria) {
    if (size <= 0)
        return vector<Report*>();
    vector<Report*> result;
    result.push_back(arr[0]);
    val = arr[0];
    swap(arr[0], arr[size - 1]);
    size--;
    heapify(arr, size, 0, sortCriteria);
    return result;
}
void Scores::Heap::heapify(vector<Scores::Report*>& arr, int n, int i, string& sortCriteria) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left]->criteriaToValue[sortCriteria] < arr[smallest]->criteriaToValue[sortCriteria])
        smallest = left;
    if (right < n && arr[right]->criteriaToValue[sortCriteria] < arr[smallest]->criteriaToValue[sortCriteria])
        smallest = right;
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest, sortCriteria);
    }
}
vector<Scores::Report*> Scores::Heap::insertHeap(Report* val, string& sortCriteria) {
    arr.push_back(val);
    size++;
    int i = size - 1;
    while (i > 0 && arr[(i - 1) / 2]->criteriaToValue[sortCriteria] < arr[i]->criteriaToValue[sortCriteria]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return arr;
}
vector<Scores::Report*> Scores::Heap::sortHeap(string& sortCriteria) {
    bool isSorted = true;
    for (int i = 1; i < size; i++) {
        if (arr[i - 1]->criteriaToValue[sortCriteria] < arr[i]->criteriaToValue[sortCriteria]) {
            isSorted = false;
            break;
        }
    }
    if (isSorted)
        return arr;
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i, sortCriteria);
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, sortCriteria);
    }
    return arr;
}
