
#include "Button.h"

Button::Button(float xpos, float ypos, float width, float height) {
    buttonRect.setPosition(sf::Vector2f(xpos, ypos));
    buttonRect.setSize(sf::Vector2f(width, height));
    buttonRect.setOutlineThickness(2);

    buttonRect.setFillColor(sf::Color::White);
    buttonRect.setOutlineColor(sf::Color::Black);
}

void Button::setColor(sf::Color color, sf::Color outlineColor) {
    buttonRect.setFillColor(color);
    buttonRect.setOutlineColor(outlineColor);
}

void Button::setOnClick(std::function<void()> callback) {
    onClick = callback;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(buttonRect);
}

void Button::checkClick(sf::Vector2i clickPos) {
    if (buttonRect.getGlobalBounds().contains(sf::Vector2<float>(clickPos))) {
        onClick();
    }
}

