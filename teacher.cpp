#include "teacher.h"
//#include "user.h"

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


REVIEW TEACHER::add_review()
{
    if (this == nullptr) {
        cout << "Error: TEACHER object is not initialized." << endl;
        //return nullptr;
    }

    string review_text;
    int stars;
    cout << "Enter your review: ";
    cin.ignore();
    getline(cin, review_text);
    cout << "Enter the number of stars (0-5): ";
    cin >> stars;

    REVIEW* new_reviews = new REVIEW[nr_reviews + 1];
    for (int j = 0; j < nr_reviews; ++j)
    {
        new_reviews[j] = reviews[j];
    }
    new_reviews[nr_reviews] = REVIEW(review_text, stars);

    delete[] reviews;
    reviews = new_reviews;
    nr_reviews++;

    cout << "Review added successfully.\n";
    return reviews[nr_reviews - 1];
}




void TEACHER::get_reviews()
{
    int it = 1;
    for (int index2 = 0; index2 < this->nr_reviews; index2++)
    {
        cout << "Review nr " << it << ":\n";
        cout << this->reviews[index2].rev << endl;
        cout << "Number of stars received is :" << this->reviews[index2].stars << endl << endl;
        it++;
    }
}