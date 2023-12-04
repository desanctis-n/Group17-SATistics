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
    tempval = arr[0];
    arr[0] = arr[size - 1];
    size--;
    int index = 0;
    int leftchild = (2*index) +1;
    int rightchild = (2*index)+2;
    Scores::Report* placeholder;
    if(size <= 1){
        return arr;
    }
    while((leftchild <= size || rightchild <= size) && ((arr[index]->criteriaToValue[sortCriteria] < arr[leftchild]->criteriaToValue[sortCriteria] || arr[index]->criteriaToValue[sortCriteria] < arr[rightchild]->criteriaToValue[sortCriteria]))){
        if(leftchild <= size){ // If the left child is in range
            if(arr[leftchild]->criteriaToValue[sortCriteria] > arr[index]->criteriaToValue[sortCriteria]){ //If the left child is greater than the parent
                if(rightchild <= size){ //If the right child exists
                    if(arr[rightchild]->criteriaToValue[sortCriteria] > arr[index]->criteriaToValue[sortCriteria]){ // if the right child also is greater than the parent
                        if(arr[leftchild]->criteriaToValue[sortCriteria] > arr[rightchild]->criteriaToValue[sortCriteria]){ // if the left child is bigger than the right child
                            placeholder = arr[index];
                            arr[index] = arr[leftchild];
                            arr[leftchild] = placeholder;
                            index = leftchild;
                            leftchild = (2*index) +1;
                            rightchild = (2*index)+2;
                            continue;

                        } else if(arr[rightchild] > arr[leftchild]){ //if the right child is greater than the left child
                            placeholder = arr[index];
                            arr[index] = arr[rightchild];
                            arr[rightchild] = placeholder;
                            index = rightchild;
                            leftchild = (2*index) +1;
                            rightchild = (2*index)+2;
                            continue;
                        }
                    }
                }
            }
        } else if(rightchild <= size){ // If the right child is in range
            if(arr[rightchild]->criteriaToValue.at(sortCriteria) > arr[index]->criteriaToValue.at(sortCriteria)){ //If the right child is greater than the parent
                if(leftchild <= size){ //If the left child exists
                    if(arr[leftchild]->criteriaToValue.at(sortCriteria) > arr[index]->criteriaToValue.at(sortCriteria)){ // if the left child also is greater than the parent
                        if(arr[rightchild]->criteriaToValue.at(sortCriteria) > arr[leftchild]->criteriaToValue.at(sortCriteria)){ // if the right child is bigger than the left child
                            placeholder = arr[index];
                            arr[index] = arr[rightchild];
                            arr[rightchild] = placeholder;
                            index = rightchild;
                            leftchild = (2*index) +1;
                            rightchild = (2*index)+2;
                            continue;
                        } else if(arr[leftchild]->criteriaToValue.at(sortCriteria) > arr[rightchild]->criteriaToValue.at(sortCriteria)){ //if the left child is greater than the right child
                            placeholder = arr[index];
                            arr[index] = arr[leftchild];
                            arr[leftchild] = placeholder;
                            index = leftchild;
                            leftchild = (2*index) +1;
                            rightchild = (2*index)+2;
                            continue;
                        }
                    }
                }
            }
        }

    }
    return arr;
}
vector<Scores::Report*> Scores::Heap::sortHeap(string &sortCriteria) {
    vector<Scores::Report*> sortedlist;
    sortedlist.resize(578);
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
