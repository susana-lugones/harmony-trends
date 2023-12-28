#pragma once
#include "Heap.h"

int partition(vector<Song>& arr, int low, int high) {
    float pivot = arr[high].data;
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (arr[j].data < pivot) {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i + 1],arr[high]);
    return i + 1;
}

void sort(vector<Song>& arr, int left, int right){
    if (left < right){
        int index = partition(arr,left,right);
        sort(arr,left,index - 1);
        sort(arr,index + 1,right);
    }
}

void quickSort(vector<Song>& arr){
    sort(arr, 0, arr.size() - 1);
}

Song findSong(const vector<Song>& arr, string name, string title){
    for (int i = 0 ; i < arr.size(); i++){
        if (arr[i].title.find(title) != std::string::npos && arr[i].artist_name.find(name) != string::npos){
            return arr[i];
        }
    }
    cout << "search was not successful" << endl;
    return Song();
}
