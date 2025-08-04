#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
using namespace std;

struct Game {
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

    //Game (string title, string genre, string developers)
    //    : title(title), genre(genre), developers(developers){}

    //CHECKS HOW CLOSE TO THE CATEGORIES A GAME IS
    float reccLevel (Game g2);
};

struct weightedGame {
    Game game;
    int score;

    weightedGame (Game game, int score) : game(game), score(score) {}

    //MAX HEAP FUNCTION
    bool operator<(const weightedGame &other) const {
      return score < other.score;
    }
};



#endif //GAME_H
