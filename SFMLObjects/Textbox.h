#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"


class Textbox {
private:
    sf::Text text;
    sf::RectangleShape rect;
    bool focused = false;
    std::string input;

public:
    Textbox(float x, float y, float width, float height, sf::Font& font);

    void checkClick(sf::Vector2i pos);
    void checkKeyPress(sf::Event::TextEntered text);

    void draw(sf::RenderWindow& window);

    std::string getInput();
};



#endif //TEXTBOX_H