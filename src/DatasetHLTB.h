#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <Game.h>

class DatasetHLTB {
private:
    // Dataset vector
    std::vector<Game> dataset;

    // Helper function to split line correctly
    std::vector<std::string> split(std::string textToSplit, char delimiter);
public:
    DatasetHLTB(std::string filePath);

    float compare(std::string game1, std::string game2);

    std::vector<Game> getDataset();
};