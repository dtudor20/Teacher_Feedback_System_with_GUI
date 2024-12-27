// user.cpp
#include "main.h"
#include "TextButton.h"
int nr_teachers = 0;
int GUEST_USER::nr_users = 2;
TrieNode* userTrie = getNode();

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
            TEXTINPUTBOX passwordBox(100, 200, 600, 50, "Type in your password");
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
        else {
            BUTTON createAccountButton(100, 300, 600, 50, "Create an account");
            BUTTON skipButton(100, 400, 600, 50, "Skip");
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
                createAccountButton.draw(window);
                skipButton.draw(window);
                window.display();
            }

            if (createAccountButton.is_selected) {
                TEXTINPUTBOX passwordBox(100, 500, 600, 50, "Enter the account password");
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
                questionText.setPosition(100, 300);

                BUTTON teacherButton(100, 400, 600, 50, "Teacher");
                BUTTON studentButton(100, 500, 600, 50, "Student");
                int type = 0;
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

                GUEST_USER* newUser;
                if (type == 1) {
                    newUser = new TEACHER_USER(passn, usern);
                }
                else if (type == 2) {
                    newUser = new STUDENT_USER(passn, usern);
                }
                insertUser(userTrie, newUser);
                GUEST_USER::nr_users++;
                newUser->menu();
            }


        }
    }
    else {
        GUEST_USER user("guest", "guest");
        user.menu();
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
        logInButton.draw(window);
        searchTeacherButton.draw(window);
        window.display();
    }

    if (logInButton.is_selected) {
        log();
    }
    else if (searchTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 300, 600, 50, "Type in the name of the teacher");
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

void TEACHER_USER::menu() {
    BUTTON logOutButton(100, 100, 600, 50, "Log out");
    BUTTON seeReviewsButton(100, 200, 600, 50, "See my reviews");
    BUTTON deleteReviewsButton(100, 300, 600, 50, "Delete your reviews");
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            logOutButton.handleEvent(event, window);
            seeReviewsButton.handleEvent(event, window);
            deleteReviewsButton.handleEvent(event, window);
        }
        if (logOutButton.is_selected || seeReviewsButton.is_selected || deleteReviewsButton.is_selected)
            break;
        window.clear(sf::Color::Black);
        logOutButton.draw(window);
        seeReviewsButton.draw(window);
        deleteReviewsButton.draw(window);
        window.display();
    }

    if (logOutButton.is_selected) {
        log();
    }
    else if (seeReviewsButton.is_selected) {
        TEACHER* p = search_teacher(username);
        if (p != nullptr) {
            p->get_reviews();
        }
        else {
            std::cout << "No reviews found\n";
        }
        menu();
    }
    else if (deleteReviewsButton.is_selected) {
        delete_teacher();
        menu();
    }
}

void TEACHER_USER::delete_teacher() {
    removeTeacher(root, username);
    nr_teachers--;
    std::cout << "Teacher deletion successful!\n";
}

void STUDENT_USER::menu() {
    BUTTON logOutButton(100, 100, 600, 50, "Log out");
    BUTTON searchTeacherButton(100, 200, 600, 50, "Search a teacher");
    BUTTON seeReviewsButton(100, 300, 600, 50, "See your reviews");
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            logOutButton.handleEvent(event, window);
            searchTeacherButton.handleEvent(event, window);
            seeReviewsButton.handleEvent(event, window);
        }
        if (logOutButton.is_selected || searchTeacherButton.is_selected || seeReviewsButton.is_selected)
            break;
        window.clear(sf::Color::Black);
        logOutButton.draw(window);
        searchTeacherButton.draw(window);
        seeReviewsButton.draw(window);
        window.display();
    }

    if (logOutButton.is_selected) {
        log();
    }
    else if (searchTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 400, 600, 50, "Type in the name of the teacher");
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
            BUTTON seeReviewsButton(100, 100, 600, 50, "See the teacher's reviews");
            BUTTON addReviewButton(100, 200, 600, 50, "Add another review");
            BUTTON skipButton(100, 700, 300, 50, "Skip");
            while (true) {
                while (window.pollEvent(event)) {
                    // Close window: exit
                    if (event.type == sf::Event::Closed)
                        window.close();
                    seeReviewsButton.handleEvent(event, window);
                    addReviewButton.handleEvent(event, window);
                    skipButton.handleEvent(event, window);
                }
                if (seeReviewsButton.is_selected || addReviewButton.is_selected || skipButton.is_selected)
                    break;
                window.clear(sf::Color::Black);
                seeReviewsButton.draw(window);
                addReviewButton.draw(window);
                skipButton.draw(window);
                window.display();
            }

            if (seeReviewsButton.is_selected) {
                p->get_reviews();
            }
            else if (addReviewButton.is_selected) {
                p->add_review();
            }
        }
        else {
            BUTTON addTeacherButton(100, 100, 600, 50, "Add the teacher");
            BUTTON skipButton(100, 200, 600, 50, "Skip");
            while (true) {
                while (window.pollEvent(event)) {
                    // Close window: exit
                    if (event.type == sf::Event::Closed)
                        window.close();
                    addTeacherButton.handleEvent(event, window);
                    skipButton.handleEvent(event, window);
                }
                if (addTeacherButton.is_selected || skipButton.is_selected)
                    break;
                window.clear(sf::Color::Black);
                addTeacherButton.draw(window);
                skipButton.draw(window);
                window.display();
            }

            if (addTeacherButton.is_selected) {
                TEACHER* new_teacher = new TEACHER(name);
                insertTeacher(root, new_teacher);
                nr_teachers++;

                // Ensure new_user_reviews is allocated with the correct size
                REVIEW* new_user_reviews = new REVIEW[nr_user_reviews + 1];
                if (user_reviews != nullptr) {
                    for (int index1 = 0; index1 < nr_user_reviews; index1++) {
                        new_user_reviews[index1] = user_reviews[index1];
                    }
                    delete[] user_reviews;
                }
                user_reviews = new_user_reviews;
                user_reviews[nr_user_reviews] = new_teacher->add_review();
                nr_user_reviews++;
            }
        }
        menu();
    }
    else if (seeReviewsButton.is_selected) {
        sf::Event event;
        BUTTON nextButton(100, 400, 600, 50, "Next");

        int it = 1;
        for (int index2 = 0; index2 < nr_user_reviews; index2++) {
            while (true) {
                while (window.pollEvent(event)) {
                    // Close window: exit
                    if (event.type == sf::Event::Closed)
                        window.close();
                    nextButton.handleEvent(event, window);
                }
                if (nextButton.is_selected)
                    break;
                window.clear(sf::Color::Black);

                sf::Font font;
                if (!font.loadFromFile("roboto.ttf")) {
                    // Handle error
                }

                sf::Text reviewText;
                reviewText.setFont(font);
                reviewText.setString("Review nr " + std::to_string(it) + ":\n" + user_reviews[index2].rev + "\nNumber of stars given is :" + std::to_string(user_reviews[index2].stars));
                reviewText.setCharacterSize(24);
                reviewText.setFillColor(sf::Color::White);
                reviewText.setPosition(100, 100);

                window.draw(reviewText);
                nextButton.draw(window);
                window.display();
            }
            it++;
        }
        menu();
    }

}


void ADMIN_USER::menu() {
    BUTTON logOutButton(100, 100, 600, 50, "Log out");
    BUTTON searchTeacherButton(100, 200, 600, 50, "Search a teacher");
    BUTTON seeReviewsButton(100, 300, 600, 50, "See my reviews");
    BUTTON deleteTeacherButton(100, 400, 600, 50, "Delete a teacher");
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            logOutButton.handleEvent(event, window);
            searchTeacherButton.handleEvent(event, window);
            seeReviewsButton.handleEvent(event, window);
            deleteTeacherButton.handleEvent(event, window);
        }
        if (logOutButton.is_selected || searchTeacherButton.is_selected || seeReviewsButton.is_selected || deleteTeacherButton.is_selected)
            break;
        window.clear(sf::Color::Black);
        logOutButton.draw(window);
        searchTeacherButton.draw(window);
        seeReviewsButton.draw(window);
        deleteTeacherButton.draw(window);
        window.display();
    }

    if (logOutButton.is_selected) {
        GUEST_USER::log();
    }
    else if (searchTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 500, 600, 50, "Type in the name of the teacher");
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
            BUTTON seeReviewsButton(100, 600, 600, 50, "See the teacher's reviews");
            BUTTON skipButton(100, 700, 600, 50, "Skip");
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
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
    }
    else if (seeReviewsButton.is_selected) {
        std::cout << "The reviews you wrote are the following:\n";
        int it = 1;
        for (int index2 = 0; index2 < nr_user_reviews; index2++) {
            std::cout << "Review nr " << it << ":\n";
            std::cout << user_reviews[index2].rev << std::endl;
            std::cout << "Number of stars given is :" << user_reviews[index2].stars << std::endl;
            it++;
        }
        menu();
    }
    else if (deleteTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 500, 600, 50, "Input the name of the teacher you wish to delete");
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
        TEACHER* teacher_to_delete = search_teacher(name);
        if (teacher_to_delete != nullptr) {
            removeTeacher(root, name);
            std::cout << "Teacher deletion successful!\n";
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
    }
}
