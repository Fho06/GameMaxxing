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
    sf::RectangleShape refreshButton;
public:
    GameCard(float x, float y, float width, float height, sf::Font& titleFont, sf::Font& mainTextFont);
    void draw(sf::RenderWindow& window);
    void setColors(sf::Color color1, sf::Color color2, sf::Color color3);
    void setText(std::string title, std::string link);
    bool checkClick(sf::Vector2f mousePos);
};



#endif //GAMECARD_H