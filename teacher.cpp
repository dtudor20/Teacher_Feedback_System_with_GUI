#include "teacher.h"
#include "Button.h"
#include "TextButton.h"
extern sf::RenderWindow window;

// Copy constructor
TEACHER::TEACHER(const TEACHER& other) : name(other.name), nr_reviews(other.nr_reviews) {
    if (other.reviews) {
        reviews = new REVIEW[nr_reviews];
        for (int i = 0; i < nr_reviews; ++i) {
            reviews[i] = other.reviews[i];
        }
    }
    else {
        reviews = nullptr;
    }
}

// Copy assignment operator
TEACHER& TEACHER::operator=(const TEACHER& other) {
    if (this == &other) {
        return *this;
    }

    delete[] reviews;

    name = other.name;
    nr_reviews = other.nr_reviews;

    if (other.reviews) {
        reviews = new REVIEW[nr_reviews];
        for (int i = 0; i < nr_reviews; ++i) {
            reviews[i] = other.reviews[i];
        }
    }
    else {
        reviews = nullptr;
    }

    return *this;
}

REVIEW TEACHER::add_review() {
    if (this == nullptr) {
        std::cout << "Error: TEACHER object is not initialized." << std::endl;
        //return nullptr;
    }

    sf::Event event;
    TEXTINPUTBOX reviewBox(100, 100, 600, 250, "Enter your review");
    TEXTINPUTBOX starsBox(100, 400, 600, 50, "Enter the number of stars (0-5)");
    BUTTON nextButton(100, 500, 600, 50, "Next");

    while (true) {
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            reviewBox.handleEvent(event, window);
            starsBox.handleEvent(event, window);
            nextButton.handleEvent(event, window);
        }
        
        if (nextButton.is_selected && !starsBox.input.empty() && std::stoi(starsBox.input) >= 0 && std::stoi(starsBox.input) <= 5)
            break;
        if (starsBox.is_selected)
        {
            reviewBox.is_selected = false; nextButton.is_selected = false;
        }
        if (reviewBox.is_selected)
        {
            starsBox.is_selected = false; nextButton.is_selected = false;
        }
        window.clear(sf::Color::Black);
        reviewBox.draw(window);
        starsBox.draw(window);
        nextButton.draw(window);
        window.display();
    }

    std::string review_text = reviewBox.input;
    int stars = std::stoi(starsBox.input);

    REVIEW* new_reviews = new REVIEW[nr_reviews + 1];
    for (int j = 0; j < nr_reviews; ++j) {
        new_reviews[j] = reviews[j];
    }
    new_reviews[nr_reviews] = REVIEW(review_text, stars);

    delete[] reviews;
    reviews = new_reviews;
    nr_reviews++;

    std::cout << "Review added successfully.\n";
    return reviews[nr_reviews - 1];
}

void TEACHER::get_reviews() {
    sf::Event event;
    BUTTON nextButton(100, 500, 600, 50, "Next");

    int it = 1;
    for (int index2 = 0; index2 < this->nr_reviews; index2++) {
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
            reviewText.setString("Review nr " + std::to_string(it) + ":\n" + this->reviews[index2].rev + "\nNumber of stars received is :" + std::to_string(this->reviews[index2].stars));
            reviewText.setCharacterSize(24);
            reviewText.setFillColor(sf::Color::White);
            reviewText.setPosition(100, 100);

            window.draw(reviewText);
            nextButton.draw(window);
            window.display();
        }
        it++;
    }
}
