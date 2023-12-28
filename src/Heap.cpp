#include "Heap.h"

minHeap::minHeap(int _capacity) {
    capacity = _capacity;
    currSize = 0;
    arr.resize(_capacity);
}

minHeap::minHeap(){
    capacity = 0;
    currSize = 10000;
    arr.resize(capacity);
}

int minHeap::getParent(int index) {
    return index - 1 / 2;
}

int minHeap::getRightChild(int index) {
    return index * 2 + 2;
}

int minHeap::getLeftChild(int index) {
    return index * 2 + 1;
}


void minHeap::push(const Song& song) {
    if (currSize == capacity) {
        throw runtime_error("HEAP OVERFLOW, MAXIMUM CAPACITY REACHED");
    }
    currSize++;
    int index = currSize - 1;
    arr[index] = song;
    while (index > 0
           && arr[(index - 1) / 2].data > arr[index].data) {
        swap(arr[index], arr[(index - 1) / 2]);
        // Move up the tree to the parent of the current
        // element
        index = (index - 1) / 2;
    }
}

void minHeap::heapifyDown(int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int smallest = index;
    if (left < currSize && arr[left].data < arr[index].data){
        smallest = left;
    }
    if (right < currSize && arr[right].data < arr[smallest].data){
        smallest = right;
    }
    if (smallest != index){
        swap(arr[index], arr[smallest]);
        heapifyDown(smallest);
    }
}

Song minHeap::pop() {
    if (currSize == 0){
        throw runtime_error("NO ITEMS LEFT IN THE HEAP");
    }
    if (currSize == 1){return arr[--currSize];}
    Song root = arr[0];
    arr[0] = arr[--currSize]; // decrease and put last element then heapify down
    heapifyDown(0);
    return root;
}

bool minHeap::isEmpty() {return currSize == 0;}

void minHeap::setSize(int _size) {capacity == _size;}
