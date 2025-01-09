#include "main.h"

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
        window.draw(teacher);
        logOutButton.draw(window);
        seeReviewsButton.draw(window);
        deleteReviewsButton.draw(window);
        window.display();
    }

    if (logOutButton.is_selected) {
        log();
    }
    else if (seeReviewsButton.is_selected) {
        TEACHER* p = search_teacher(teacher_name);
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
    TEACHER* teacher_to_delete = searchTeacher(root, teacher_name);
    if (teacher_to_delete != nullptr) {
        removeTeacher(root, teacher_name);
        nr_teachers--;
        std::cout << "Teacher deletion successful!\n";
    }
    else {
        std::cout << "Teacher not found\n";
    }
}