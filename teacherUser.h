#pragma once
#include "teacher.h"
#include <SFML/Graphics.hpp>
#include "textButton.h"
#include <iostream>
#include <string>
using namespace std;

class TEACHER_USER : virtual public GUEST_USER
{
public:
    TEACHER_USER() {};
    TEACHER_USER(string password, string username)
        : GUEST_USER(password, username) {
        teacher_image.loadFromFile("teacher.jpg");
        teacher.setTexture(teacher_image);
    }
    void delete_teacher();
    string teacher_name;
private:
    sf::Texture teacher_image;
    sf::Sprite teacher;
    void menu() override;
};