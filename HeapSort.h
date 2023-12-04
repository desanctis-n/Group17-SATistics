#ifndef HEAPSORT_H
#define HEAPSORT_H

// DEPRECATED FILE

class Heap{
private:
    int arr[578];
    int sort;
public:
    int* extractMax(int arr[], int &size, int &val);
    int* insertHeap(int arr[], int &size, int val);
    int* sortHeap(int arr[], int &size);

};

int* Heap::insertHeap(int arr[], int &size, int val){
    size++;
    arr[size-1] = val;
    int parent = (size-1)/2;
    int child = size-1;
    while(parent >= 0 && arr[parent] < arr[child]){
        int temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;
        child = parent;
        parent = (child-1)/2;
    }
    return arr;
}

int* Heap::extractMax(int arr[], int &size, int &tempval)
{
    tempval = arr[0];
    arr[0] = arr[size - 1];
    size--;
    int index = 0;
    int leftchild = (2*index) +1;
    int rightchild = (2*index)+2;
    int placeholder;
    if(size <= 1){
        return arr;
    }
    while((leftchild <= size || rightchild <= size) && ((arr[index] < arr[leftchild] || arr[index] < arr[rightchild]))){
        if(leftchild <= size){ // If the left child is in range
            if(arr[leftchild] > arr[index]){ //If the left child is greater than the parent
                if(rightchild <= size){ //If the right child exists
                    if(arr[rightchild > arr[index]]){ // if the right child also is greater than the parent
                        if(arr[leftchild] > arr[rightchild]){ // if the left child is bigger than the right child
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
            if(arr[rightchild] > arr[index]){ //If the right child is greater than the parent
                if(leftchild <= size){ //If the left child exists
                    if(arr[leftchild > arr[index]]){ // if the left child also is greater than the parent
                        if(arr[rightchild] > arr[leftchild]){ // if the right child is bigger than the left child
                            placeholder = arr[index];
                            arr[index] = arr[rightchild];
                            arr[rightchild] = placeholder;
                            index = rightchild;
                            leftchild = (2*index) +1;
                            rightchild = (2*index)+2;
                            continue;
                        } else if(arr[leftchild] > arr[rightchild]){ //if the left child is greater than the right child
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
int* Heap::sortHeap(int arr[], int &size) {
    int sortedlist[578];
    int listsize = 0;
    int tempval;
    int temparrayval;
    int *result;
    for (int i = size; i > 0; i--) {
        if (listsize == 0) {
            result = extractMax(arr, size, tempval);
            sortedlist[0] = tempval;
            listsize++;
            continue;
        }
        result = extractMax(arr, size, tempval);
        temparrayval = arr[listsize - 1];
        sortedlist[listsize] = tempval;
        sortedlist[listsize+1] = temparrayval;
        listsize++;
    }
    size = listsize;
    return sortedlist;
}

#endif //DSA_PROJECT_3_HEAPSORT_H
