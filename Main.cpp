#include "Main.h"
using namespace std;

int main()
{
    GUEST_USER guest("guest", "guest");
    //guest.start();

    // Create a window with a title and size
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    TextInputBox textBox(100, 100, 600, 50);
    sf::Mouse mouse;
    bool text_box_selected = false;
    // Main loop that continues until the window is closed
    while (window.isOpen())
    {
        // Process events
        sf::Vector2i location = mouse.getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Call handleEvent to process text input events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (textBox.box.getGlobalBounds().contains(static_cast<sf::Vector2f>(location)))
                {
                    cout << "Left click inside text box" << endl;
                    text_box_selected=!text_box_selected;
                }
            }
            if(text_box_selected)
            textBox.handleEvent(event);
        }

        //cout << location.x << " " << location.y;
        window.clear(sf::Color::Black);
        textBox.draw(window); // Draw the text box
        //cout << textBox.input;
        window.display();
    }

    return 0;
}
