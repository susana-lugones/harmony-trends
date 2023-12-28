#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <iomanip>
#include "Quicksort.h"

using namespace std;
using namespace sf;

class HarmonyTrendsApp {
public:
    //Initializes the app and creates the main window
    HarmonyTrendsApp() {
        window.create(VideoMode(960, 540), "HarmonyTrends");
        initialize();
    }

    //Takes a list of songs and handles the app's main loop
    void run(const vector<Song>& _songs) {
        songs = _songs;
        while (window.isOpen()) {
            handleEvents();
            draw();
        }
    }

    // Function to URL encode a string (useful for making web requests)
    string urlEncode(const string &value) {
        ostringstream escaped;
        escaped.fill('0');
        escaped << hex;

        for (char c : value) {
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
                continue;
            }
            escaped << uppercase;
            escaped << '%' << setw(2) << int((unsigned char) c);
            escaped << nouppercase;
        }
        return escaped.str();
    }

    // Resets the state of the app, clearing all input and analysis data
    void resetState() {
        comparisonSong.clear();
        comparisonSongText.setString("");
        songName.clear();
        analysisDisplayed = false;
        searchPerformed = false;

        for (int i = 0; i < 3; ++i) {
            similarSongsText[i].setString("");
            similarArtistsText[i].setString("");
        }
    }

private:
    // Declaration of variables and objects
    vector<Song> songs;
    RenderWindow window;
    Texture backgroundTexture;
    Font font;
    Sprite background;
    RectangleShape textBox1, textBox2, searchButton;
    Text userInput1, userInput2, songNameText;
    string inputString1, inputString2, songName, comparisonSong;
    bool typing1, typing2;
    FloatRect spotifyArea, soundCloudArea, youtubeArea;

    // Arrays for displaying similar songs and artists
    Text similarSongsText[3], similarArtistsText[3];
    bool searchPerformed = false;
    bool analysisDisplayed = false;

    // Text for comparison song
    Text comparisonSongText;

    // Arrays for song analysis categories and placeholders
    Text songAnalysisCategoryTitles[5];
    Text songAnalysisPlaceholders[5];

    // Arrays for song comparison data
    Text firstSongComp[5], firstSongHold[5];
    Text secondSongComp[5], secondSongHold[5];

    // Function to initialize various components of the GUI
    void initialize() {

        // Load and set the background texture
        if (!backgroundTexture.loadFromFile("image/finalFinalFinal_back.jpg")) {
            exit(1); // Exit if the texture fails to load
        }
        backgroundTexture.setSmooth(true);
        background.setTexture(backgroundTexture);
        // Scale the background to fit the window size
        background.setScale(float(window.getSize().x) / backgroundTexture.getSize().x, float(window.getSize().y) / backgroundTexture.getSize().y);

        // Load the font for text elements
        if (!font.loadFromFile("image/calibri.ttf")) {
            exit(1); // Exit if the font fails to load
        }

        // Set up the first text box
        textBox1.setSize(Vector2f(300, 50));
        textBox1.setPosition(30, 35);
        textBox1.setFillColor(sf::Color::White);

        // Set up the second text box
        textBox2.setSize(Vector2f(300, 50));
        textBox2.setPosition(410, 35);
        textBox2.setFillColor(sf::Color::White);

        // Set up the search button
        searchButton.setSize(Vector2f(150, 50));
        searchButton.setPosition(780, 35);
        searchButton.setFillColor(sf::Color::Blue);

        // Configure user input fields
        userInput1.setFont(font);
        userInput1.setPosition(115, 41);
        userInput1.setFillColor(sf::Color::Black);
        userInput1.setCharacterSize(20);

        userInput2.setFont(font);
        userInput2.setPosition(470, 40);
        userInput2.setFillColor(sf::Color::Black);
        userInput2.setCharacterSize(20);

        // Set up the text for displaying the song name
        songNameText.setFont(font);
        songNameText.setPosition(630, 200);
        songNameText.setFillColor(sf::Color::White);
        songNameText.setCharacterSize(20);

        // Define clickable areas for different music platforms
        spotifyArea = FloatRect(165, 100, 50, 50);
        soundCloudArea = FloatRect(300, 100, 50, 50);
        youtubeArea = FloatRect(400, 100, 50, 50);

        // Initialize typing states and default song name
        typing1 = false;
        typing2 = false;
        songName = "Default Song Name";

        // Set up similar songs and artists text elements
        for (int i = 0; i < 3; ++i) {
            similarSongsText[i].setFont(font);
            similarSongsText[i].setString("Song " + to_string(i + 1));
            similarSongsText[i].setPosition(50, 245 + i * 30);
            similarSongsText[i].setFillColor(sf::Color::White);
            similarSongsText[i].setCharacterSize(20);

            similarArtistsText[i].setFont(font);
            similarArtistsText[i].setString("Artist " + to_string(i + 1));
            similarArtistsText[i].setPosition(50, 415 + i * 30);
            similarArtistsText[i].setFillColor(sf::Color::White);
            similarArtistsText[i].setCharacterSize(20);
        }

        // Set up the text for comparison song
        comparisonSongText.setFont(font);
        comparisonSongText.setString("");
        comparisonSongText.setPosition(780, 200);
        comparisonSongText.setFillColor(sf::Color::White);
        comparisonSongText.setCharacterSize(20);

        // Set up song analysis categories and placeholders
        for (int i = 0; i < 5; ++i) {
            songAnalysisCategoryTitles[i].setFont(font);
            songAnalysisCategoryTitles[i].setFillColor(sf::Color::White);
            songAnalysisCategoryTitles[i].setCharacterSize(18);
            songAnalysisCategoryTitles[i].setStyle(sf::Text::Bold);
            songAnalysisCategoryTitles[i].setPosition(380, 243 + i * 53);

            songAnalysisPlaceholders[i].setFont(font);
            songAnalysisPlaceholders[i].setFillColor(sf::Color::White);
            songAnalysisPlaceholders[i].setCharacterSize(18);
            songAnalysisPlaceholders[i].setPosition(380, 263 + i * 53);
        }

        songAnalysisCategoryTitles[0].setString("Category 1");
        songAnalysisPlaceholders[0].setString("[Placeholder]");

        songAnalysisCategoryTitles[1].setString("Category 2");
        songAnalysisPlaceholders[1].setString("[Placeholder]");

        songAnalysisCategoryTitles[2].setString("Category 3");
        songAnalysisPlaceholders[2].setString("[Placeholder]");

        songAnalysisCategoryTitles[3].setString("Category 4");
        songAnalysisPlaceholders[3].setString("[Placeholder]");

        songAnalysisCategoryTitles[4].setString("Category 5");
        songAnalysisPlaceholders[4].setString("[Placeholder]");


        //Same as above, but for the comparison chart (first song aka inputted)
        for (int i = 0; i < 5; ++i) {
            firstSongComp[i].setFont(font);
            firstSongComp[i].setFillColor(sf::Color::White);
            firstSongComp[i].setCharacterSize(18);
            firstSongComp[i].setStyle(sf::Text::Bold);
            firstSongComp[i].setPosition(605, 237 + i * 55);

            firstSongHold[i].setFont(font);
            firstSongHold[i].setFillColor(sf::Color::White);
            firstSongHold[i].setCharacterSize(18);
            firstSongHold[i].setPosition(605, 257 + i * 55);
        }

        firstSongComp[0].setString("Artist");
        firstSongComp[1].setString("Bar Confidence");
        firstSongComp[2].setString("Song Hotttnesss");
        firstSongComp[3].setString("Loudness");
        firstSongComp[4].setString("Mode Confidence");


        //Same as above, but for the comparison chart (second song)
        for (int i = 0; i < 5; ++i) {
            secondSongComp[i].setFont(font);
            secondSongComp[i].setFillColor(sf::Color::White);
            secondSongComp[i].setCharacterSize(18);
            secondSongComp[i].setStyle(sf::Text::Bold);
            secondSongComp[i].setPosition(780, 237 + i * 55);

            secondSongHold[i].setFont(font);
            secondSongHold[i].setFillColor(sf::Color::White);
            secondSongHold[i].setCharacterSize(18);
            secondSongHold[i].setPosition(780, 257 + i * 55);
        }

        secondSongComp[0].setString("Artist");
        secondSongComp[1].setString("Bar Confidence");
        secondSongComp[2].setString("Song Hotttnesss");
        secondSongComp[3].setString("Loudness");
        secondSongComp[4].setString("Mode Confidence");
    }

    // Function to handle different events in the application.
    void handleEvents() {
        Event event;

        // Loop to process all pending events.
        while (window.pollEvent(event)) {

            // Close the window if the Close event is triggered.
            if (event.type == Event::Closed) {
                window.close();
            }

            // Check if a mouse button was pressed.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Static variables to store songs information.
                static Song song1, song2, song3;

                // Check if the search button is clicked.
                if (searchButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    resetState();

                    // Ensure both song and artist strings are not empty.
                    if (!inputString1.empty() && !inputString2.empty()) {
                        // Find the song based on the input strings.
                        Song search = findSong(songs, inputString2, inputString1);
                        cout << search.title << " " << search.artist_name << endl;

                        // Create a min-heap and a vector to store differences between songs.
                        minHeap pq(10000);
                        vector<Song> diff = songs;

                        // Calculate the difference in data for each song.
                        for (auto& song : diff){
                            song.data = abs(song.data - search.data);
                        }

                        // Push unique songs to the priority queue.
                        for (auto& song : diff){
                            if (song.artist_name != inputString2 && song.title != inputString1){
                                pq.push(song);
                            }
                        }

                        // Pop top three songs from the priority queue.
                        song1 = pq.pop();
                        song2 = pq.pop();
                        song3 = pq.pop();

                        // Empty the priority queue.
                        while (!pq.isEmpty()){
                            pq.pop();
                        }

                        quickSort(diff);

                        diff.erase(diff.begin(), diff.end());

                        // Set strings for similar songs and artists.
                        similarSongsText[0].setString(diff[1].title);
                        similarSongsText[1].setString(diff[2].title);
                        similarSongsText[2].setString(diff[3].title);

                        similarArtistsText[0].setString(song1.artist_name);
                        similarArtistsText[1].setString(song2.artist_name);
                        similarArtistsText[2].setString(song3.artist_name);

                        firstSongHold[4].setString(to_string(search.duration));
                        firstSongHold[3].setString(to_string(search.energy));
                        firstSongHold[2].setString(to_string(search.danceability));
                        firstSongHold[1].setString(to_string(search.key_confidence));
                        firstSongHold[0].setString(search.title);

                        songAnalysisCategoryTitles[0].setString("Song Title");
                        songAnalysisPlaceholders[0].setString(search.title);

                        songAnalysisCategoryTitles[1].setString("Energy");
                        songAnalysisPlaceholders[1].setString(to_string(search.energy));

                        songAnalysisCategoryTitles[2].setString("Danceability");
                        songAnalysisPlaceholders[2].setString(to_string(search.danceability));

                        songAnalysisCategoryTitles[3].setString("Key Confidence");
                        songAnalysisPlaceholders[3].setString(to_string(search.danceability));

                        songAnalysisCategoryTitles[4].setString("Duration (seconds)");
                        songAnalysisPlaceholders[4].setString(to_string(search.duration));

                        songName = inputString1;
                        songNameText.setString(songName);

                        searchPerformed = true;
                        analysisDisplayed = true;
                    }
                }

                string encodedSongName = urlEncode(songName);

                // Open the song in Spotify, SoundCloud, or YouTube based on the area clicked.
                if (spotifyArea.contains(event.mouseButton.x, event.mouseButton.y)) {
                    string spotifyUrl = "https://open.spotify.com/search/" + encodedSongName;
                    system(("start " + spotifyUrl).c_str());
                }
                else if (soundCloudArea.contains(event.mouseButton.x, event.mouseButton.y)) {
                    string soundCloudUrl = "https://soundcloud.com/search?q=" + encodedSongName;
                    system(("start " + soundCloudUrl).c_str());
                }
                else if (youtubeArea.contains(event.mouseButton.x, event.mouseButton.y)) {
                    string youtubeUrl = "https://www.youtube.com/results?search_query=" + encodedSongName;
                    system(("start " + youtubeUrl).c_str());
                }

                if (textBox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    typing1 = true;
                    typing2 = false;
                } else if (textBox2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    typing2 = true;
                    typing1 = false;
                } else {
                    typing1 = typing2 = false;
                }

                for (int i = 0; i < 3; ++i) {
                    if (similarSongsText[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                        if (similarSongsText[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            secondSongHold[4].setString(to_string(song1.duration));
                            secondSongHold[3].setString(to_string(song1.energy));
                            secondSongHold[2].setString(to_string(song1.danceability));
                            secondSongHold[1].setString(to_string(song1.key_confidence));
                            secondSongHold[0].setString(song1.artist_name);
                        }
                        else if (similarSongsText[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            secondSongHold[4].setString(to_string(song2.duration));
                            secondSongHold[3].setString(to_string(song2.energy));
                            secondSongHold[2].setString(to_string(song2.danceability));
                            secondSongHold[1].setString(to_string(song2.key_confidence));
                            secondSongHold[0].setString(song2.artist_name);
                        }
                        else if (similarSongsText[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            secondSongHold[4].setString(to_string(song3.duration));
                            secondSongHold[3].setString(to_string(song3.energy));
                            secondSongHold[2].setString(to_string(song3.danceability));
                            secondSongHold[1].setString(to_string(song3.key_confidence));
                            secondSongHold[0].setString(song3.artist_name);
                        }

                        comparisonSong = similarSongsText[i].getString();
                        comparisonSongText.setString(comparisonSong);
                    }
                }
            }

            if (typing1 && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!inputString1.empty()) {
                        inputString1.erase(inputString1.size() - 1);
                    }
                } else if (event.text.unicode < 128) {
                    inputString1 += event.text.unicode;
                }
                userInput1.setString(inputString1);
                if (!inputString1.empty() || !inputString2.empty()) {
                    resetState();
                }
            }

            if (typing2 && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!inputString2.empty()) {
                        inputString2.erase(inputString2.size() - 1);
                    }
                } else if (event.text.unicode < 128) {
                    inputString2 += event.text.unicode;
                }
                userInput2.setString(inputString2);
            }
        }
    }

    void draw() {
        // Clears the window to prepare for new drawing (removing previous content).
        window.clear();

        // Draws the background, userInput1, userInput2, and songNameText onto the window.
        window.draw(background);
        window.draw(userInput1);
        window.draw(userInput2);
        window.draw(songNameText);

        // If a search has been performed, draw similar songs and artists.
        if (searchPerformed) {
            for (int i = 0; i < 3; ++i) {
                window.draw(similarSongsText[i]);
                window.draw(similarArtistsText[i]);
            }
        }

        // If a comparison song is selected, draw its text.
        if (!comparisonSong.empty()) {
            window.draw(comparisonSongText);
        }

        // If analysis is to be displayed, draw song analysis details.
        if (analysisDisplayed) {
            for (int i = 0; i < 5; ++i) {
                window.draw(songAnalysisCategoryTitles[i]);
                window.draw(songAnalysisPlaceholders[i]);
                window.draw(firstSongComp[i]);
                window.draw(firstSongHold[i]);
                window.draw(secondSongComp[i]);
                window.draw(secondSongHold[i]);
            }
        }

        // Displays the newly drawn content on the screen.
        window.display();
    }
};
