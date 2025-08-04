#include "Game.h"

float Game::reccLevel(Game g2){
  // Declare similarity score value
  float similarityScore = 0;

  // If a game is being compared to itself return 0 so that its not used as recomendation
  if(gameName == g2.gameName){
    return 0;
  }

  // Add reviews to similarity score;
  float reviewWeight = 1;

  if(g2.reviewCount <= 50){
    reviewWeight = 0.2;
  }

  similarityScore += g2.reviewScore / 100 * reviewWeight;

  // Add genres to similarity score
  float genreWeight = 1;

  int matchingGenres = 0;
  for(auto genre1 : genre){
    for(auto genre2 : g2.genre){
      if(genre1 == genre2){
        matchingGenres++;
        break;
      }
    }
  }
  if (genre.size() != 0) {
    similarityScore += 100 * matchingGenres / genre.size();
  }
  else {
    genreWeight = 0;
  }
  // Add dev to similarity score
  if(dev == g2.dev){
    similarityScore += 50;
  }

  // Calculate max possible score
  float maxScore = 100 * reviewWeight + 100 * genreWeight + 50;

  // Return final normalized similarity score
  return similarityScore / maxScore;
}