#include "Game.h"

int reccLevel (const Game &game, const string &inputGenre, const string &inputDev) {
  int level = 0;
  if (game.genre == inputGenre) { level += 2; }
  if (game.developers == inputDev) { level += 1 ; }
  return level;
}