#pragma once
#include <SFML/Graphics.hpp>
class TextInputBox {
public:
    TextInputBox(float x, float y, float width, float height) {
        box.setSize(sf::Vector2f(width, height));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);

        if (!font.loadFromFile("roboto.ttf")) {
            
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setPosition(x + 5, y + 5);
    }
    void handleEvent(sf::Event event);
    void draw(sf::RenderWindow& window);
    std::string input;
    sf::RectangleShape box;
private:
    sf::Text text;
    sf::Font font;
};