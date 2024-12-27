// user.cpp
#include "user.h"
#include "TrieTree.h"

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
        std::cout << "Type in your username:\n";
        std::string usern;
        std::cin.ignore();
        std::getline(std::cin, usern);
        GUEST_USER *found = searchUser(userTrie, usern);
        if (found!=nullptr) {
            std::cout << "Account found! Type in your password:\n";
            std::string pass;
            std::getline(std::cin, pass);
            GUEST_USER* user = static_cast<GUEST_USER*>(userTrie->user);
            while (pass != found->password) {
                std::cout << "Wrong password. Try again or press 0 to exit\n";
                std::getline(std::cin, pass);
                if (pass == "0") {
                    return;
                }
            }
            std::cout << "Correct password! Now you are logged in\n";
            found->menu();
            return;
        }
        else {
            std::cout << "Account doesn't exist. Choose 1 to create an account or 0 to skip\n";
            int choice3;
            std::cin >> choice3;
            if (choice3 == 1) {
                std::cout << "Enter the account password:\n";
                std::string passn;
                std::cin >> passn;
                std::cout << "Are you a teacher or a student?\nChoose 1 for teacher or 2 for student\n";
                int type;
                std::cin >> type;
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
    std::cout << "Choose 1 to log in.\nChoose 2 to search a teacher\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        log();
        break;
    case 2:
        std::cout << "Type in the name of the teacher\n";
        std::cin.ignore();
        std::string name;
        std::getline(std::cin, name);
        TEACHER* p = search_teacher(name);
        if (p != nullptr) {
            std::cout << "Teacher found! Choose 1 to see the teacher's reviews or 0 to skip\n";
            int choice2;
            std::cin >> choice2;
            if (choice2 == 1) {
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
        break;
    }
}

void TEACHER_USER::menu() {
    std::cout << "Choose 1 to log out.\nChoose 2 to see my reviews\nChoose 3 to delete your reviews\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        log();
        break;
    case 2: {
        TEACHER* p = search_teacher(username);
        if (p != nullptr) {
            p->get_reviews();
        }
        else {
            std::cout << "No reviews found\n";
        }
        menu();
        break;
    }
    case 3:
        delete_teacher();
        menu();
        break;
    }
}

void TEACHER_USER::delete_teacher() {
    removeTeacher(root, username);
    nr_teachers--;
    std::cout << "Teacher deletion successful!\n";
}

void STUDENT_USER::menu() {
    std::cout << "Choose 1 to log out.\nChoose 2 to search a teacher\nChoose 3 to see your reviews\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        log();
        break;
    case 2: {
        std::cout << "Type in the name of the teacher\n";
        std::cin.ignore();
        std::string name;
        std::getline(std::cin, name);
        TEACHER* p = search_teacher(name);
        if (p != nullptr) {
            std::cout << "Teacher found! Choose 1 to see the teacher's reviews or 2 to add another review or 0 to skip\n";
            int choice2;
            std::cin >> choice2;
            if (choice2 == 1) {
                p->get_reviews();
            }
            else if (choice2 == 2) {
                p->add_review();
            }
        }
        else {
            std::cout << "Teacher not found. Choose 1 to add the teacher or 0 to skip\n";
            int choice2;
            std::cin >> choice2;
            if (choice2 == 1) {
                TEACHER* new_teacher=new TEACHER(name);
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
        break;
    }
    case 3: {
        std::cout << "The reviews you wrote are the following:\n";
        int it = 1;
        for (int index2 = 0; index2 < nr_user_reviews; index2++) {
            std::cout << "Review nr " << it << ":\n";
            std::cout << user_reviews[index2].rev << std::endl;
            std::cout << "Number of stars given is :" << user_reviews[index2].stars << std::endl;
            it++;
        }
        menu();
        break;
    }
    }
}

void ADMIN_USER::menu() {
    std::cout << "Choose 1 to log out.\n";
    std::cout << "Choose 2 to search a teacher.\n";
    std::cout << "Choose 3 to see my reviews.\n";
    std::cout << "Choose 4 to delete a teacher.\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        GUEST_USER::log();
        break;
    case 2: {
        std::cout << "Type in the name of the teacher\n";
        std::cin.ignore();
        std::string name;
        std::getline(std::cin, name);
        TEACHER* p = search_teacher(name);
        if (p != nullptr) {
            std::cout << "Teacher found! Choose 1 to see the teacher's reviews or 0 to skip\n";
            int choice2;
            std::cin >> choice2;
            if (choice2 == 1) {
                p->get_reviews();
            }
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
        break;
    }
    case 3: {
        std::cout << "The reviews you wrote are the following:\n";
        int it = 1;
        for (int index2 = 0; index2 < nr_user_reviews; index2++) {
            std::cout << "Review nr " << it << ":\n";
            std::cout << user_reviews[index2].rev << std::endl;
            std::cout << "Number of stars given is :" << user_reviews[index2].stars << std::endl;
            it++;
        }
        menu();
        break;
    }
    case 4: {
        std::cout << "Input the name of the teacher you wish to delete\n";
        std::cin.ignore();
        std::string name;
        std::getline(std::cin, name);
        TEACHER* teacher_to_delete = search_teacher(name);
        if (teacher_to_delete != nullptr) {
            removeTeacher(root, name);
            std::cout << "Teacher deletion successful!\n";
        }
        else {
            std::cout << "Teacher not found\n";
        }
        menu();
        break;
    }
    default:
        std::cout << "Invalid choice. Please try again.\n";
        menu();
        break;
    }
}
