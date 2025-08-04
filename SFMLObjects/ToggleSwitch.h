
#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"


class ToggleSwitch {
private:
    sf::Text text1;
    sf::Text text2;
    sf::CircleShape circle1;
    sf::CircleShape circle2;
    sf::CircleShape circle3;
    sf::RectangleShape rect1;
    int state = 0;
public:

};



#endif //TOGGLESWITCH_H
