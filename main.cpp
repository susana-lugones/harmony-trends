#include "src/HarmonyTrends.h"
#include "src/Quicksort.h"
using namespace std;

vector<Song> readCSV() {
    vector<Song> songs;
    ifstream file("C:/Users/desti/CLionProjects/COP3530/Project3/music_clean.csv");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    string header;
    getline(file, header);

    istringstream ss(header);
    string token;
    vector<string> headerTokens;
    while (getline(ss, token, ',')) {
        headerTokens.push_back(token);
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::string token;

        std::vector<std::string> dataTokens;
        while (getline(lineStream, token, ',')) {
            dataTokens.push_back(token);
        }

        float duration = stof(dataTokens[0]);
        string artist_name = dataTokens[1];
        string title = dataTokens[2];
        float bars_confidence = stof(dataTokens[3]);
        float danceability = stof(dataTokens[4]);
        float energy = stof(dataTokens[5]);
        float key_confidence = stof(dataTokens[6]);
        float loudness = stof(dataTokens[7]);
        float mode_confidence = stof(dataTokens[8]);
        float song_hotttnesss = stof(dataTokens[9]);

        Song song(duration, artist_name, title, bars_confidence, danceability, energy, key_confidence, loudness, mode_confidence, song_hotttnesss);
        songs.push_back(song);
    }

    return songs;
}



int main() {

    vector<Song> db = readCSV();
    HarmonyTrendsApp app;
    app.run(db);
    return 0;
}