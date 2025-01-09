// user.cpp
#include "main.h"
int GUEST_USER::nr_users = 2;

GUEST_USER::GUEST_USER(const GUEST_USER& other) : username(other.username), password(other.password) {}

GUEST_USER& GUEST_USER::operator=(const GUEST_USER& other) {
    if (this == &other) return *this;
    username = other.username;
    password = other.password;
    return *this;
}

void GUEST_USER::log() {
    if (username == "guest") {
        sf::Event event;
        TEXTINPUTBOX usernameBox(100, 100, 600, 50, "Type in your username");
        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                usernameBox.handleEvent(event, window);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
            window.clear(sf::Color::Black);
            usernameBox.draw(window);
            window.display();
        }

        std::string usern = usernameBox.input;
        GUEST_USER* found = searchUser(userTrie, usern);


        if (found != nullptr) {
            log_in(event, found);
        }
        else {
            create_account(event,usern);
        }
    }
    else {
        GUEST_USER user("guest", "guest");
        user.menu();
    }
}

void GUEST_USER::log_in(sf::Event event,GUEST_USER* found)
{
    TEXTINPUTBOX passwordBox(100, 100, 600, 50, "Type in your password");
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            passwordBox.handleEvent(event, window);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            break;
        window.clear(sf::Color::Black);
        passwordBox.draw(window);
        window.display();
    }

    std::string pass = passwordBox.input;
    GUEST_USER* user = static_cast<GUEST_USER*>(userTrie->user);
    while (pass != found->password) {
        TEXTINPUTBOX retryPasswordBox(100, 200, 600, 50, "Wrong password. Try again or press 0 to exit");
        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                retryPasswordBox.handleEvent(event, window);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
            window.clear(sf::Color::Black);
            retryPasswordBox.draw(window);
            window.display();
        }

        pass = retryPasswordBox.input;
        if (pass == "0") {
            return;
        }
    }
    std::cout << "Correct password! Now you are logged in\n";
    found->menu();
    return;
}

void GUEST_USER::create_account(sf::Event event,string usern)
{
    sf::Font font;
    if (!font.loadFromFile("roboto.ttf")) {
        // Handle error
    }

    sf::Text noAccountText;
    noAccountText.setFont(font);
    noAccountText.setString("No account found");
    noAccountText.setCharacterSize(24);
    noAccountText.setFillColor(sf::Color::White);
    noAccountText.setPosition(100, 50);

    BUTTON createAccountButton(100, 100, 600, 50, "Create an account");
    BUTTON skipButton(100, 200, 600, 50, "Skip");
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            createAccountButton.handleEvent(event, window);
            skipButton.handleEvent(event, window);
        }
        if (createAccountButton.is_selected || skipButton.is_selected)
            break;
        window.clear(sf::Color::Black);
        window.draw(noAccountText);
        createAccountButton.draw(window);
        skipButton.draw(window);
        window.display();
    }
    if (skipButton.is_selected)
    {
        GUEST_USER user("guest", "guest");
        user.menu();
    }
    int type = 0;
    GUEST_USER* newUser;
    if (createAccountButton.is_selected) {
        TEXTINPUTBOX passwordBox(100, 100, 600, 50, "Enter the account password");
        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                passwordBox.handleEvent(event, window);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
            window.clear(sf::Color::Black);
            passwordBox.draw(window);
            window.display();
        }

        std::string passn = passwordBox.input;

        sf::Font font;
        if (!font.loadFromFile("roboto.ttf")) {
            // Handle error
        }

        sf::Text questionText;
        questionText.setFont(font);
        questionText.setString("Are you a teacher or a student?");
        questionText.setCharacterSize(24);
        questionText.setFillColor(sf::Color::White);
        questionText.setPosition(100, 50);

        BUTTON teacherButton(100, 100, 600, 50, "Teacher");
        BUTTON studentButton(100, 200, 600, 50, "Student");

        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                teacherButton.handleEvent(event, window);
                studentButton.handleEvent(event, window);
            }
            if (teacherButton.is_selected) {
                type = 1;
                break;
            }
            if (studentButton.is_selected) {
                type = 2;
                break;
            }
            window.clear(sf::Color::Black);
            window.draw(questionText);
            teacherButton.draw(window);
            studentButton.draw(window);
            window.display();
        }

        if (type == 1) {
            newUser = new TEACHER_USER(passn, usern);
            // Cast newUser to TEACHER_USER to access teacher_name
            TEACHER_USER* teacherUser = dynamic_cast<TEACHER_USER*>(newUser);
            TEXTINPUTBOX teacher_name(100, 100, 600, 50, "Enter your real name students will search you by:");
            while (true) {
                while (window.pollEvent(event)) {
                    // Close window: exit
                    if (event.type == sf::Event::Closed)
                        window.close();
                    teacher_name.handleEvent(event, window);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !teacher_name.input.empty())
                        break;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    break;
                window.clear(sf::Color::Black);
                teacher_name.draw(window);
                window.display();
            }
            teacherUser->teacher_name = teacher_name.input;
        }
        else if (type == 2) {
            newUser = new STUDENT_USER(passn, usern);
        }
        insertUser(userTrie, newUser);
        GUEST_USER::nr_users++;
        newUser->menu();

    }
}


TEACHER* GUEST_USER::search_teacher(std::string name) {
    return searchTeacher(root, name);
}

void GUEST_USER::menu() {
    BUTTON logInButton(100, 100, 600, 50, "Log in");
    BUTTON searchTeacherButton(100, 200, 600, 50, "Search a teacher");
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            logInButton.handleEvent(event, window);
            searchTeacherButton.handleEvent(event, window);
        }
        if (logInButton.is_selected || searchTeacherButton.is_selected)
            break;
        window.clear(sf::Color::Black);
        window.draw(guest);
        logInButton.draw(window);
        searchTeacherButton.draw(window);
        window.display();
    }

    if (logInButton.is_selected) {
        log();
    }
    else if (searchTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 100, 600, 50, "Type in the name of the teacher");
        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                nameBox.handleEvent(event, window);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
            window.clear(sf::Color::Black);
            nameBox.draw(window);
            window.display();
        }

        std::string name = nameBox.input;
        TEACHER* p = search_teacher(name);
        if (p != nullptr) {
            BUTTON seeReviewsButton(100, 400, 600, 50, "See the teacher's reviews");
            BUTTON skipButton(100, 500, 600, 50, "Skip");
            while (true) {
                while (window.pollEvent(event)) {
                    // Close window: exit
                    if (event.type == sf::Event::Closed)
                        window.close();
                    seeReviewsButton.handleEvent(event, window);
                    skipButton.handleEvent(event, window);
                }
                if (seeReviewsButton.is_selected || skipButton.is_selected)
                    break;
                window.clear(sf::Color::Black);
                seeReviewsButton.draw(window);
                skipButton.draw(window);
                window.display();
            }

            if (seeReviewsButton.is_selected) {
                p->get_reviews();
            }
            else {
                menu();
            }
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
    }
}
