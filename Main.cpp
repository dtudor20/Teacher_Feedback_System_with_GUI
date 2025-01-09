#include "Main.h"

using namespace std;
int nr_teachers = 0;
sf::RenderWindow window(sf::VideoMode(800, 800), "TeacherFeedbackSystem");

int main()
{
    GUEST_USER guest("guest", "guest");
    ADMIN_USER* admin=new ADMIN_USER("admin", "admin");

    insertUser(userTrie, admin);
    guest.start();
    return 0;
}
