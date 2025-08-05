#include <iostream>
#include <SFML/Graphics.hpp>

#include "DatasetHLTB.h"
#include "Heap.h"
#include "RedBlackTree.h"
#include "../SFMLObjects/Button.h"
#include "../SFMLObjects/GameCard.h"
#include "../SFMLObjects/Textbox.h"

const sf::Color backgroundColor = sf::Color(60, 60, 60);
const sf::Color darkBackgroundColor = sf::Color(45, 45, 45);
const sf::Color outlineColor = sf::Color(235, 204, 52);

// Kinda wish I didn't have to make this global but oh well
int searchMode = 0;
bool closing = false;

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

    auto* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "GameMaxxing");

    // Create objects
    //background
    sf::Texture bgTex;
    if (!bgTex.loadFromFile("../resources/bg4.jpg")) {
        std::cerr << "Failed to load background\n";
    }
    sf::Sprite bgSprite(bgTex);
    bgSprite.setScale(
    sf::Vector2f(
      float(width)  / bgTex.getSize().x,
      float(height) / bgTex.getSize().y
        )
    );

    sf::Font titleFont;
    titleFont.openFromFile("../resources/OpenSans.ttf");

    sf::Font searchFont;
    searchFont.openFromFile("../resources/OpenSans.ttf");

    sf::Text title(titleFont, "Game Maxxing", 75);
    title.setOrigin(title.getLocalBounds().getCenter());
    title.setOutlineThickness(2);
    title.setFillColor(backgroundColor);
    title.setOutlineColor(outlineColor);
    title.setPosition(sf::Vector2f(width / 2, 100));

    std::vector<std::string> algorithmNames = {"Heap Backend", "Red Black Tree Backend"};
    sf::Text modeLabel(titleFont, algorithmNames[searchMode], 75);
    modeLabel.setCharacterSize(25);
    modeLabel.setOrigin(modeLabel.getLocalBounds().getCenter());
    modeLabel.setOutlineThickness(1);
    modeLabel.setFillColor(backgroundColor);
    modeLabel.setOutlineColor(outlineColor);
    modeLabel.setPosition(sf::Vector2f(width / 2, 530));

    sf::Text search(titleFont, "Search", 40);
    search.setOrigin(search.getLocalBounds().getCenter());
    search.setOutlineThickness(2);
    search.setFillColor(backgroundColor);
    search.setOutlineColor(outlineColor);
    search.setPosition(sf::Vector2f(width / 2, 330));

    auto searchBox = Textbox(300, 200, 400, 45, searchFont);

    auto button1 = Button(320,300,360,60);
    button1.setOnClick(searchButtonOnClick);
    button1.setColor(backgroundColor, outlineColor);

    auto changeSearchModeButton = Button(320,500,360,60);
    changeSearchModeButton.setOnClick(changeMode);
    changeSearchModeButton.setColor(backgroundColor, outlineColor);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is < sf::Event::Closed>()) {
                window->close();
                closing = true;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                // Mouse Events
                sf::Vector2i pos = sf::Mouse::getPosition(*window);
                button1.checkClick(pos, *window);
                searchBox.checkClick(pos);
                changeSearchModeButton.checkClick(pos, *window);
                // Update model label text
                modeLabel.setString(algorithmNames[searchMode]);
                modeLabel.setPosition(sf::Vector2f(width / 2, 530));
            }
            else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Keypress Events
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                    closing = true;
                }
            }
            else if (const auto textEntered = event->getIf<sf::Event::TextEntered>()){
                searchBox.checkKeyPress(*textEntered);
            }
        }

        // Drawing Window
        window->clear();
        window->draw(bgSprite);
        window->draw(title);
        button1.draw(*window);
        searchBox.draw(*window);
        button1.draw(*window);
        changeSearchModeButton.draw(*window);
        window->draw(title);
        window->draw(modeLabel);
        window->draw(search);

        window->display();
    }
    return searchBox.getInput();
}
void goBackButtonClick(sf::RenderWindow &window) {
    window.close();
}

void noResultsPage() {
    // Window Configs
    unsigned int width = 1024;
    unsigned int height = 768;

    auto* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "GameMaxxing");

    // Create objects
    sf::Font titleFont;
    titleFont.openFromFile("../resources/OpenSans.ttf");

    sf::Text mainText(titleFont);
    mainText.setCharacterSize(60);
    mainText.setString("Game Not Found\nTry searching for a different game");
    mainText.setOrigin(mainText.getLocalBounds().getCenter());
    mainText.setPosition(sf::Vector2f(width / 2, height / 2));
    mainText.setFillColor(darkBackgroundColor);
    mainText.setOutlineColor(outlineColor);
    mainText.setOutlineThickness(2);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is < sf::Event::Closed>()) {
                window->close();
                closing = true;
            }
            else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Keypress Events
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                    closing = true;
                }
            }
        }

        // Drawing Window
        window->clear(darkBackgroundColor);

        window->draw(mainText);

        window->display();
    }
}

void gameRecPage(std::string targetGame, Heap gameHeap, RedBlackTree gameTree) {
    // Window Configs
    unsigned int width = 1650;
    unsigned int height = 768;

    auto* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "GameMaxxing");

    // Create objects
    //background
    sf::Texture bgTex;
    if (!bgTex.loadFromFile("../resources/bg4.jpg")) {
        std::cerr << "Failed to load background\n";
    }
    sf::Sprite bgSprite(bgTex);
    bgSprite.setScale(
    sf::Vector2f(
      float(width)  / bgTex.getSize().x,
      float(height) / bgTex.getSize().y
        )
    );
    sf::Font titleFont;
    titleFont.openFromFile("../resources/OpenSans.ttf");

    sf::Font searchFont;
    searchFont.openFromFile("../resources/arial.ttf");

    sf::Text title(titleFont, targetGame, 75);
    title.setOrigin(title.getLocalBounds().getCenter());
    title.setPosition(sf::Vector2f(width / 2, 50));
    title.setOutlineThickness(2);
    title.setFillColor(backgroundColor);
    title.setOutlineColor(outlineColor);

    GameCard card1(30,130,500,600,titleFont,searchFont);
    card1.setColors(backgroundColor,darkBackgroundColor,outlineColor);

    GameCard card2(560,130,500,600,titleFont,searchFont);
    card2.setColors(backgroundColor,darkBackgroundColor,outlineColor);

    GameCard card3(1090,130,500,600,titleFont,searchFont);
    card3.setColors(backgroundColor,darkBackgroundColor,outlineColor);

    Button goBack(25,25,75,75);
    goBack.setColor(darkBackgroundColor, outlineColor);
    goBack.setOnClick(goBackButtonClick);

    // Only used if red black tree is being used
    std::vector<weightedGame> gamesToBeInserted;
    int insertedCount = 3;

    if (searchMode == 0) {
        weightedGame gameToInsert = gameHeap.getMax();
        card1.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
        gameToInsert = gameHeap.getMax();
        card2.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
        gameToInsert = gameHeap.getMax();
        card3.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
    }
    else if (searchMode == 1) {
        gamesToBeInserted = gameTree.getTopK(30);
        card1.setText(gamesToBeInserted[0].game.gameName, gamesToBeInserted[0].game.desc);
        card2.setText(gamesToBeInserted[1].game.gameName, gamesToBeInserted[1].game.desc);
        card3.setText(gamesToBeInserted[2].game.gameName, gamesToBeInserted[2].game.desc);
    }

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is < sf::Event::Closed>()) {
                window->close();
                closing = true;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                // Mouse Events
                sf::Vector2i pos = sf::Mouse::getPosition(*window);
                if (searchMode == 0) {
                    if (card1.checkClick(sf::Vector2f(pos))) {
                        weightedGame gameToInsert = gameHeap.getMax();
                        card1.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
                    }
                    else if (card2.checkClick(sf::Vector2f(pos))) {
                        weightedGame gameToInsert = gameHeap.getMax();
                        card2.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
                    }
                    else if (card3.checkClick(sf::Vector2f(pos))) {
                        weightedGame gameToInsert = gameHeap.getMax();
                        card3.setText(gameToInsert.game.gameName, gameToInsert.game.desc);
                    }
                    else {
                        goBack.checkClick(pos, *window);
                    }
                }
                else if (searchMode == 1 && insertedCount < gamesToBeInserted.size() - 1) {
                    if (card1.checkClick(sf::Vector2f(pos))) {
                        card1.setText(gamesToBeInserted[insertedCount].game.gameName, gamesToBeInserted[insertedCount].game.desc);
                        insertedCount++;
                    }
                    else if (card2.checkClick(sf::Vector2f(pos))) {
                        card2.setText(gamesToBeInserted[insertedCount].game.gameName, gamesToBeInserted[insertedCount].game.desc);
                        insertedCount++;
                    }
                    else if (card3.checkClick(sf::Vector2f(pos))) {
                        card3.setText(gamesToBeInserted[insertedCount].game.gameName, gamesToBeInserted[insertedCount].game.desc);
                        insertedCount++;
                    }
                }
            }
            else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Keypress Events
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                    closing = true;
                }
            }
            else if (const auto textEntered = event->getIf<sf::Event::TextEntered>()){

            }
        }

        // Drawing Window
        window->clear();
        window->draw(bgSprite);
        window->draw(title);
        card1.draw(*window);
        card2.draw(*window);
        card3.draw(*window);
        goBack.draw(*window);

        window->display();
    }
}



int main(){
    while (!closing) {
        // Title screen with searchbar
        std::string titlePageOutput = titlePage();

        // Get data from dataset
        DatasetHLTB mainDataset("../resources/dataset/hltb_data.csv");

        Game targetGame;
        bool gameFound = false;

        for (auto game : mainDataset.getDataset()) {
            if (game.gameName == titlePageOutput) {
                targetGame = game;
                gameFound = true;
            }
        }

        if (gameFound && !targetGame.gameName.empty()) {
            Heap gameHeap;
            RedBlackTree gameTree;

            if (searchMode == 0) {
                for (auto g : mainDataset.getDataset()) {
                    gameHeap.insert(weightedGame(g, targetGame.reccLevel(g) * 1000));
                }
            } else if(searchMode == 1) {
                for (auto g : mainDataset.getDataset()) {
                    gameTree.insert(weightedGame(g, targetGame.reccLevel(g) * 1000));
                }
            }

            gameRecPage(titlePageOutput, gameHeap, gameTree);
        }
        else if (!closing){
            noResultsPage();
        }
    }
    return 0;
}
