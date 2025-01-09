#include "TextButton.h"

void TEXTINPUTBOX::handleEvent(const sf::Event event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            is_selected = !is_selected;
        }
    }
    if (event.type == sf::Event::TextEntered && is_selected) {
        if (event.text.unicode == '\b') {
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
        }
        
        text.setString(input);
        if (input.size() % 45==0 && !input.empty())
        {
            input.push_back('\n');
        }
    }
}

void TEXTINPUTBOX::draw(sf::RenderWindow& window) {
    if (is_selected)
    {
        box.setFillColor(sf::Color::Yellow);
    }
    else
    {
        box.setFillColor(sf::Color::White);
    }
    window.draw(labelText);
    window.draw(box);
    window.draw(text);
}
