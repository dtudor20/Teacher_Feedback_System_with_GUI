#pragma once
#include "teacher.h"
#include <SFML/Graphics.hpp>
#include "textButton.h"
#include <iostream>
#include <string>
using namespace std;

class ADMIN_USER : public STUDENT_USER, public TEACHER_USER
{
public:
    ADMIN_USER() {};
    ADMIN_USER(string password, string username) : GUEST_USER(password, username) {
        admin_texture.loadFromFile("admin.png");
        admin.setTexture(admin_texture);
        admin.setScale(3.6, 3.6);
    };
private:
    void menu() override;
    sf::Texture admin_texture;
    sf::Sprite admin;
};