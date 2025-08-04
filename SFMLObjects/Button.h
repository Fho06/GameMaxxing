#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class Button {
private:
    // Rectangle shape object to represent button
    sf::RectangleShape buttonRect;
    std::function<void()> onClick;

public:
    Button(float xpos, float ypos, float width, float height);

    void setColor(sf::Color color, sf::Color outlineColor = sf::Color::Black);
    void setOnClick(std::function<void()> callback);

    void draw(sf::RenderWindow& window);
    void checkClick(sf::Vector2i clickPos);
};



#endif //BUTTON_H