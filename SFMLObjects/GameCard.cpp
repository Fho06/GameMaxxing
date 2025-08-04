
#include "GameCard.h"

GameCard::GameCard(float x, float y, float width, float height, sf::Font &titleFont, sf::Font &mainTextFont): gameName(titleFont),
    gameLink(mainTextFont){
    mainBody.setSize(sf::Vector2f(width, height));
    mainBody.setPosition(sf::Vector2f(x, y));
    mainBody.setFillColor(sf::Color::White);
    mainBody.setOutlineColor(sf::Color::Black);
    mainBody.setOutlineThickness(2);

    gameName.setPosition(sf::Vector2f(x + 10, y + 10));
    gameName.setFillColor(sf::Color::White);
    gameName.setOutlineColor(sf::Color::Black);
    gameName.setOutlineThickness(2);

    gameLink.setPosition(sf::Vector2f(x + 10, y + 200));
    gameLink.setFillColor(sf::Color::Black);
    gameLink.setOutlineColor(sf::Color::Black);
    gameLink.setOutlineThickness(2);
    gameLink.setCharacterSize(10);

    refreshButton.setPosition(sf::Vector2f(x + 10, y + 500));
    refreshButton.setSize(sf::Vector2f(width / 5 * 4, height / 5));
    refreshButton.setFillColor(sf::Color::White);
    refreshButton.setOutlineColor(sf::Color::Black);
    refreshButton.setOutlineThickness(2);
}

void GameCard::draw(sf::RenderWindow &window) {
    window.draw(mainBody);
    window.draw(refreshButton);
    window.draw(gameName);
    window.draw(gameLink);
}

void GameCard::setColors(sf::Color color1, sf::Color color2, sf::Color color3) {
    mainBody.setFillColor(color1);

    gameLink.setFillColor(color2);
    gameName.setFillColor(color2);
    refreshButton.setFillColor(color2);

    mainBody.setOutlineColor(color3);
    gameName.setOutlineColor(color3);
    gameLink.setOutlineColor(color3);
    refreshButton.setOutlineColor(color3);
}

void GameCard::setText(std::string title, std::string link) {
    gameName.setString(title);
    std::string description = "";
    for (auto c : link) {
        des
    }
    gameLink.setString();
}

bool GameCard::checkClick(sf::Vector2f mousePos) {
    return refreshButton.getGlobalBounds().contains(mousePos);
}
