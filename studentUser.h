#pragma once
#include "teacher.h"
#include <SFML/Graphics.hpp>
#include "TextButton.h"
#include <iostream>
#include <string>
using namespace std;

class STUDENT_USER :virtual public GUEST_USER
{
public:
    STUDENT_USER() {
        nr_user_reviews = 0;
        user_reviews = nullptr;
    }
    STUDENT_USER(string password, string username)
        : GUEST_USER(password, username) {
        nr_user_reviews = 0;
        user_reviews = nullptr;
        student_texture.loadFromFile("student.jpg");
        student.setTexture(student_texture);
        student.setScale(0.8,0.8);
    }
    void search(sf::Event);
    void see_reviews();
    REVIEW* user_reviews;
    int nr_user_reviews;
private:
    sf::Texture student_texture;
    sf::Sprite student;
    void menu() override;
};