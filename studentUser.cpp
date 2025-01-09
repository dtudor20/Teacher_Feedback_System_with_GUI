#include "main.h"

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
        window.draw(student);
        logOutButton.draw(window);
        searchTeacherButton.draw(window);
        seeReviewsButton.draw(window);
        window.display();
    }

    if (logOutButton.is_selected) {
        log();
    }
    else if (searchTeacherButton.is_selected) {
        this->search(event);
    }
    else if (seeReviewsButton.is_selected) {
        see_reviews();
    }

}

void STUDENT_USER::see_reviews()
{
    sf::Event event;
    BUTTON nextButton(100, 400, 600, 50, "Next");

    int it = 1;
    for (int index2 = 0; index2 < nr_user_reviews; index2++) {
        cout << nr_user_reviews;
        while (true) {
            while (window.pollEvent(event)) {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
                nextButton.handleEvent(event, window);
            }
            if (nextButton.is_selected)
            {
                nextButton.is_selected = false;
                //it++;
                break;
            }

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

void STUDENT_USER::search(sf::Event event)
{
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
            REVIEW* new_user_reviews = new REVIEW[nr_user_reviews + 1];
            if (user_reviews != nullptr) {
                for (int index1 = 0; index1 < nr_user_reviews; index1++) {
                    new_user_reviews[index1] = user_reviews[index1];
                }
                delete[] user_reviews;
            }
            user_reviews = new_user_reviews;
            user_reviews[nr_user_reviews] = p->add_review();
            this->nr_user_reviews++;
        }
    }
    else {
        sf::Font font;
        if (!font.loadFromFile("roboto.ttf")) {
            // Handle error
        }

        sf::Text noTeacherText;
        noTeacherText.setFont(font);
        noTeacherText.setString("Teacher not found");
        noTeacherText.setCharacterSize(24);
        noTeacherText.setFillColor(sf::Color::White);
        noTeacherText.setPosition(100, 50);

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
            window.draw(noTeacherText);
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
            this->nr_user_reviews++;
        }
    }
    menu();
}