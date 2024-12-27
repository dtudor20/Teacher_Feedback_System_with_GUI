#include "Button.h"

void TextInputBox::handleEvent(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

void TextInputBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}
