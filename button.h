#pragma once
#include <SFML/Graphics.hpp>
class BUTTON {
public:
    BUTTON(float x, float y, float width, float height, const std::string& label);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool is_selected=false;
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
    
};
