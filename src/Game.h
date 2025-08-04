#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;

struct Game {
  string title, genre, developers;

  Game (string title, string genre, string developers)
        : title(title), genre(genre), developers(developers){}

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

//CHECKS HOW CLOSE TO THE CATEGORIES A GAME IS
int reccLevel (const Game &game, const string &inputGenre, const string &inputDev);


#endif //GAME_H
