#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

class Song {
public:
    float duration;
    float bars_confidence;
    float danceability;
    float energy;
    float key_confidence;
    float loudness;
    float mode_confidence;
    float song_hotttnesss;
public:
    Song(const float _duration, const string _artist_name, const string _title, const float _bars_confidence, const float _danceability, const float _energy, const float _key_confidence, const float _loudness, const float _mode_confidence, const float _song_hotttnesss) :
            duration(_duration), artist_name(_artist_name), title(_title), bars_confidence(_bars_confidence), danceability(_danceability), energy(_energy), loudness(_loudness), mode_confidence(_mode_confidence), song_hotttnesss(_song_hotttnesss), key_confidence(_key_confidence){
        data = sqrt(pow(key_confidence, 2) + pow((duration), 2) + pow(bars_confidence, 2) + pow(danceability, 2) + pow(energy, 2) + pow(loudness, 2) + pow(mode_confidence, 2) + pow(song_hotttnesss, 2));
    }
    Song() {}
    float data;
    string artist_name;
    string title;
};

class minHeap {
private:
    vector<Song> arr;
    int capacity;
    void heapifyDown(int index);
    int getParent(int index);
    int getRightChild(int index);
    int getLeftChild(int index);
public:
    int currSize;
    minHeap(int _capacity);
    minHeap();
    void push(const Song& song);
    Song pop();
    bool isEmpty();
    void setSize(int _size);
};

