#include "Scores.h"

Scores::Heap::Heap() {
    arr.resize(578);
}
vector<Scores::Report*> Scores::Heap::insertHeap(Scores::Report* val, string &sortCriteria){
    size++;
    arr[size-1] = val;
    int parent = (size-1)/2;
    int child = size-1;
    while(parent >= 0 && arr[parent]->criteriaToValue.at(sortCriteria) < arr[child]->criteriaToValue.at(sortCriteria)){
        auto temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;
        child = parent;
        parent = (child-1)/2;
    }
    return arr;
}

vector<Scores::Report*> Scores::Heap::extractMax(Scores::Report* &tempval, string &sortCriteria)
{
    if (size <= 1) {
        return arr;
    }
    tempval = arr[0];
    arr[0] = arr[size - 1];
    size--;
    arr.resize(size);
    int index = 0;
    int leftchild;
    int rightchild;
    bool loop = true;
    while (loop) {
        leftchild = 2 * index + 1;
        rightchild = 2 * index + 2;
        int maxChildIndex = leftchild;
        if (rightchild < size && arr[rightchild]->criteriaToValue.at(sortCriteria) > arr[leftchild]->criteriaToValue.at(sortCriteria)) {
            maxChildIndex = rightchild;
        }
        if (maxChildIndex < size && arr[maxChildIndex]->criteriaToValue.at(sortCriteria) > arr[index]->criteriaToValue.at(sortCriteria)) {
            swap(arr[index], arr[maxChildIndex]);
            index = maxChildIndex;
        } else {
            break;
        }
    }
    return arr;
}

vector<Scores::Report*> Scores::Heap::sortHeap(string &sortCriteria) {
    arr.resize(size);
    vector<Scores::Report*> sortedlist;
    sortedlist.resize(size);
    int listsize = 0;
    Scores::Report* tempval;
    Scores::Report* temparrayval;
    vector<Scores::Report*> result;
    for (int i = size; i > 0; i--) {
        if (listsize == 0) {
            result = extractMax(tempval, sortCriteria);
            sortedlist[0] = tempval;
            listsize++;
            continue;
        }
        result = extractMax(tempval, sortCriteria);
        temparrayval = arr[listsize - 1];
        sortedlist[listsize] = tempval;
        sortedlist[listsize+1] = temparrayval;
        listsize++;
    }
    size = listsize;
    sortedlist.resize(size);
    return sortedlist;
}
