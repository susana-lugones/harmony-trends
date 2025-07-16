# HarmonyTrends

An interactive C++ application that analyzes and visualizes song similarity using a combination of **graph algorithms**, **heaps**, and **sorting**, all rendered in a GUI built with **SFML**.

---

## **Overview**

This project is a full-stack implementation of a song analytics and visualization tool, built entirely in **C++**. It leverages a custom-built **graph**, **heap-based ranking**, and **quicksort module** to explore closeness between songs based on attributes like energy, danceability, and loudness.

The system visualizes results through a graphical interface powered by **SFML**, offering an engaging way to interact with and interpret song data.

---

## **Key Features**

- **Graphical Interface**: Built using SFML for real-time interaction and visualization.  
- **Feature-Based Song Similarity**: Compares tracks using multidimensional audio attributes.  
- **Heap Ranking System**: Ranks songs by “closeness” using Euclidean feature scoring.  
- **CSV Data Integration**: Parses real-world song data from a structured CSV file.  
- **Quicksort Integration**: Efficient sorting of songs for ordered display or analysis.  

---

## **Architecture**

The application is divided into the following core components:

### 1. **Song Model**
- Defines each song as an object with key musical attributes.  
- Calculates a composite similarity score from features like `danceability`, `energy`, and `loudness`.

### 2. **Heap Structure**
- A custom heap implementation is used to maintain ranked song recommendations.  
- Efficiently retrieves top-N similar songs based on calculated feature distance.

### 3. **Graphical UI (SFML)**
- Displays interactive elements in a windowed environment.  
- Handles user events, visual rendering, and dynamic updates.

### 4. **CSV Parser**
- Loads and parses song data from `music_clean.csv`.  
- Extracts attributes and constructs a vector of `Song` objects.

### 5. **Sorting Module (Quicksort)**
- Implements a fast comparison-based sort to assist in song ordering.  
- Can be used for visualizations or pre-processing.

---

## **Testing & Modularity**

- The project includes individual classes (e.g., `Heap`, `Song`, `HarmonyTrendsApp`) organized in the `src/` directory for modular design.  
- **CMake** is used to structure and build the project efficiently.

---

## **Data Input**

The dataset used is `music_clean.csv`, containing normalized audio metrics per song.

Each row includes the following columns:  
- `duration`  
- `artist_name`  
- `title`  
- `bars_confidence`  
- `danceability`  
- `energy`  
- `key_confidence`  
- `loudness`  
- `mode_confidence`  
- `song_hotttnesss`

---

## **Build Instructions**

To compile and run HarmonyTrends:

```bash
mkdir build && cd build
cmake ..
make
./HarmonyTrends
