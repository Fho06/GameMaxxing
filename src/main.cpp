#include <iostream>
#include <SFML/Graphics.hpp>
#include "../SFMLObjects/Button.h"

void test() {
    std::cout << "Hello World!\n";
}

void titlePage() {
    // Window Configs
    unsigned int width = 1024;
    unsigned int height = 768;
    const sf::Color backgroundColor = sf::Color(60, 60, 60);
    const sf::Color darkBackgroundColor = sf::Color(45, 45, 45);
    const sf::Color outlineColor = sf::Color(70, 130, 180);

    auto* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "GameMaxxing");

    // Create objects
    sf::Font font;
    font.openFromFile("../resources/Debrosee-ALPnL.ttf");

    sf::Text title(font, "Game Maxxing", 75);
    title.setPosition(sf::Vector2f(40, 40));
    title.setOutlineThickness(2);
    title.setFillColor(backgroundColor);
    title.setOutlineColor(outlineColor);

    auto button1 = Button(100,300,200,30);
    button1.setOnClick(test);
    button1.setColor(backgroundColor, outlineColor);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is < sf::Event::Closed>()) {
                window->close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                // Mouse Events
                sf::Vector2i pos = sf::Mouse::getPosition(*window);
                button1.checkClick(pos);
            }
            else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Keypress Events
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                }
            }
        }

        // Drawing Window
        window->clear(darkBackgroundColor);

        window->draw(title);
        button1.draw(*window);

        window->display();
    }
}

int main(){
    titlePage();
    std::cout << "closed";
    return 0;
}
