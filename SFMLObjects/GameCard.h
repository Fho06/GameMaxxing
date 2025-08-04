#ifndef GAMECARD_H
#define GAMECARD_H
#include "Button.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"


class GameCard {
private:
    sf::RectangleShape mainBody;
    sf::Text gameName;
    sf::Text gameLink;
    Button refresh;
public:

};



#endif //GAMECARD_H