#include "Textbox.h"

Textbox::Textbox(float x, float y, float width, float height, sf::Font& font): text(font) {
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);

    text.setPosition(sf::Vector2f(x, y));
    text.setString("");
    text.setFillColor(sf::Color::Black);
}

void Textbox::checkClick(sf::Vector2i pos) {
    if (rect.getGlobalBounds().contains(sf::Vector2<float>(pos))) {
        focused = true;
    }
    else {
        focused = false;
    }
}

void Textbox::checkKeyPress(sf::Event::TextEntered textEntered) {
    if (focused) {
        if (textEntered.unicode == 8 && !input.empty()) {
            input.pop_back();
        }
        else {
            input += textEntered.unicode;
        }
        text.setString(input);
    }
}

void Textbox::draw(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(text);
}

std::string Textbox::getInput() {
    return input;
}
