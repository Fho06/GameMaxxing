#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <set>
#include <vector>


class DatasetHLTB {
private:
    // GameData obj
    class GameData {
    public:
        std::string gameName;
        int reviewCount;
        int reviewScore;
        std::string imageUrl;
        std::string type;
        std::string desc;
        std::string dev;
        std::vector<std::string> platform;
        std::vector<std::string> genre;
        int releaseYear;

    };

    // Dataset Map
    std::unordered_map<std::string, GameData> dataset;

    // Helper function to split line correctly
    std::vector<std::string> split(std::string textToSplit, char delimiter);
public:
    DatasetHLTB(std::string filePath);

    float compare(std::string game1, std::string game2);
};