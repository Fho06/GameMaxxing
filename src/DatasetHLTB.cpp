#include "DatasetHLTB.h"

// Helper function
int safeStoi(std::string s) {
    try {
        return stoi(s);
    } catch (...) {
        return 0;
    }
}

std::vector<std::string> DatasetHLTB::split(std::string textToSplit, char delimiter) {
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
        else if(c == '"'){
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

        if (splitLine.size() > 20) {
            // Create empty game data object to store data
            Game gameDataObj;

            // Populate gameData obj
            gameDataObj.gameName = splitLine[2];
            gameDataObj.reviewCount = safeStoi(splitLine[10]);
            gameDataObj.reviewScore = safeStoi(splitLine[11]);
            gameDataObj.imageUrl = splitLine[13];
            gameDataObj.type = splitLine[14];
            gameDataObj.desc = splitLine[16];
            gameDataObj.dev = splitLine[17];
            gameDataObj.platform = split(splitLine[19], ',');
            gameDataObj.genre = split(splitLine[20], ',');


            // Add game data obj to vector
            dataset.push_back(gameDataObj);
        }
    }
}

std::vector<Game> DatasetHLTB::getDataset() {
    return dataset;
}
