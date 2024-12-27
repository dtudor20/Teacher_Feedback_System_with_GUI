#include "Button.h"
#include <iostream>
BUTTON::BUTTON(float x, float y, float width, float height, const std::string& label)
{
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setPosition(x, y);
    buttonShape.setFillColor(sf::Color::Blue);

    if (!font.loadFromFile("roboto.ttf")) {
        // Handle error
    }

    buttonText.setFont(font);
    buttonText.setString(label);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        x + (width - buttonText.getLocalBounds().width) / 2,
        y + (height - buttonText.getLocalBounds().height) / 2
    );
}

void BUTTON::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            is_selected = !is_selected;
            std::cout << "Apasat";
        }
    }
}

void BUTTON::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}
