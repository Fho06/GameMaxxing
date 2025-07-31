#include "DatasetHLTB.h"

std::vector<std::string> split(std::string& textToSplit, char delimiter){
    // Declare output vector and buffer string
    std::vector<std::string> output;
    std::string buffer = "";

    // Declare bool for quote logic
    bool inQuotes;

    // Loop through the characters in the line
    for(char c : textToSplit){
        // Push the string saved into the buffer into the output vector and reset the buffer
        if(!inQuotes && c == delimiter){
            output.push_back(buffer);
            buffer = "";
        }
        // Toggle whether the text is in quotes or not. If it is commas will be pushed into buffer instead of splitting the values.
        else if(c = '"'){
            inQuotes = !inQuotes;
        }
        // Push character into the buffer
        else{
            buffer += c;
        }
    }

    return output;
}

DatasetHLTB::DatasetHLTB(std::string filePath) {
    // Open dataset file
    std::ifstream file(filePath);

    // Check if file was opened
    if(!file.is_open()) {
        std::cout << "File not found: " << filePath << "\n";
    }

    // Create buffer string to read lines into
    std::string lineBuffer;

    // Read first line (header)
    std::getline(file, lineBuffer); 

    while(std::getline(file, lineBuffer)){
        // Separate lines by comma
        std::vector<std::string> splitLine = split(lineBuffer, ',');
        
        // Create empty game data object to store data
        GameData gameDataObj;

        // Populate gameData obj
        gameDataObj.gameName = splitLine[2];
        gameDataObj.reviewCount = stoi(splitLine[10]);
        gameDataObj.reviewScore = stoi(splitLine[11]);
        gameDataObj.imageUrl = splitLine[13];
        gameDataObj.type = splitLine[14];
        gameDataObj.desc = splitLine[16];
        gameDataObj.dev = splitLine[17];
        gameDataObj.platform = split(splitLine[19], ',');
        gameDataObj.genre = split(splitLine[20], ',');
        gameDataObj.releaseYear = stoi(split(splitLine[25], '-')[0]);

        // Add game data obj to map
        dataset.insert({gameDataObj.gameName, gameDataObj});
    }
}

float DatasetHLTB::compare(std::string game1, std::string game2){
    // Get both games
    GameData g1 = dataset[game1];
    GameData g2 = dataset[game2];
    
    // Declare similarity score value
    float similarityScore = 0;

    // If a game is being compared to itself return 0 so that its not used as recomendation
    if(g1.gameName == g2.gameName){
        return 0;
    }

    // Add reviews to similarity score;
    float reviewWeight = 1;
    
    if(g2.reviewCount <= 100){
        reviewWeight = 0.2;
    }

    similarityScore += g2.reviewScore / 100 * reviewWeight;

    // Add genres to similarity score
    int matchingGenres = 0;
    for(auto genre1 : g1.genre){
        for(auto genre2 : g2.genre){
            if(genre1 == genre2){
                matchingGenres++;
                break;
            }
        }
    }

    similarityScore += 100 * matchingGenres / g1.genre.size();

    // Add dev to similarity score
    if(g1.dev == g2.dev){
        similarityScore += 50;
    }

    // Add release year to similarity factor
    if(abs(g1.releaseYear - g2.releaseYear) <= 10){
        similarityScore += 50;
    }

    // Calculate max possible score
    float maxScore = 100 * reviewWeight + 100 + 50 + 50;

    // Return final normalized similarity socre
    return similarityScore / maxScore;
}