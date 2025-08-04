#include <iostream>
#include <SFML/Graphics.hpp>
#include "../SFMLObjects/Button.h"
#include "../SFMLObjects/Textbox.h"

// Kinda wish I didn't have to make this global but oh well
int searchMode = 0;

void gameRecPage() {

}

void searchButtonOnClick(sf::RenderWindow &window) {
    window.close();
}

void changeMode(sf::RenderWindow &window) {
    searchMode = (searchMode + 1) % 2;
}

std::string titlePage() {
    // Window Configs
    unsigned int width = 1024;
    unsigned int height = 768;
    const sf::Color backgroundColor = sf::Color(60, 60, 60);
    const sf::Color darkBackgroundColor = sf::Color(45, 45, 45);
    const sf::Color outlineColor = sf::Color(70, 130, 180);

    auto* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "GameMaxxing");

    // Create objects
    sf::Font titleFont;
    titleFont.openFromFile("../resources/Debrosee-ALPnL.ttf");

    sf::Font searchFont;
    searchFont.openFromFile("../resources/arial.ttf");

    sf::Text title(titleFont, "Game Maxxing", 75);
    title.setPosition(sf::Vector2f(40, 40));
    title.setOutlineThickness(2);
    title.setFillColor(backgroundColor);
    title.setOutlineColor(outlineColor);

    auto searchBox = Textbox(100, 400, 200, 30, searchFont);

    auto button1 = Button(100,300,200,30);
    button1.setOnClick(searchButtonOnClick);
    button1.setColor(backgroundColor, outlineColor);

    auto changeSearchModeButton = Button(100,400,200,30);
    changeSearchModeButton.setOnClick(changeMode);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is < sf::Event::Closed>()) {
                window->close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                // Mouse Events
                sf::Vector2i pos = sf::Mouse::getPosition(*window);
                button1.checkClick(pos, *window);
                searchBox.checkClick(pos);
            }
            else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Keypress Events
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                }
            }
            else if (const auto textEntered = event->getIf<sf::Event::TextEntered>()){
                searchBox.checkKeyPress(*textEntered);
            }
        }

        // Drawing Window
        window->clear(darkBackgroundColor);

        window->draw(title);
        button1.draw(*window);
        searchBox.draw(*window);

        window->display();
    }
    return searchBox.getInput();
}

int main(){
    // Title screen with searchbar
    auto titlePageOutput = titlePage();

    



    gameRecPage(titlePageOutput);

    return 0;
}
