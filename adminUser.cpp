#include "main.h"

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
    else if (searchTeacherButton.is_selected) {//
        this->search(event);
    }
    else if (seeReviewsButton.is_selected) {
        this->see_reviews();
    }
    else if (deleteTeacherButton.is_selected) {
        TEXTINPUTBOX nameBox(100, 100, 600, 50, "Input the name of the teacher you wish to delete");
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
            nr_teachers--;
            std::cout << "Teacher deletion successful!\n";
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
    }
}