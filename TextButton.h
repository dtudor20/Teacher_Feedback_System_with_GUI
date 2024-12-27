#pragma once
#include <SFML/Graphics.hpp>
class TEXTINPUTBOX {
public:
    TEXTINPUTBOX(float x, float y, float width, float height, const std::string& label) {
        box.setSize(sf::Vector2f(width, height));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);

        if (!font.loadFromFile("roboto.ttf")) {
            // Handle error
        }

        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setPosition(x + 5, y + 5);

        labelText.setFont(font);
        labelText.setFillColor(sf::Color::White);
        labelText.setCharacterSize(24);
        labelText.setString(label);
        labelText.setPosition(x, y - 30); // Position the label above the box
    }
    void handleEvent(const sf::Event event,const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    std::string input;
    bool is_selected = false;
private:
    sf::Text text;
    sf::Text labelText;
    sf::Font font;
    sf::RectangleShape box;
};