#include "Main.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(800, 1000), "SFML Window");

int main()
{
    GUEST_USER guest("guest", "guest");
    ADMIN_USER admin("admin", "admin");
    guest.start();
    return 0;
}
