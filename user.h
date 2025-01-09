#pragma once
#include "teacher.h"
#include <SFML/Graphics.hpp>
#include "textButton.h"
#include <iostream>
#include <string>
using namespace std;

class TEACHER_USER;
class TEACHER;
class REVIEW;
class GUEST_USER
{
public:
    GUEST_USER() {};
    GUEST_USER(string password, string username)
        : password(password), username(username) {
        guest_texture.loadFromFile("guest.jpg");
        guest.setTexture(guest_texture);
        guest.setScale(0.8, 0.8);
    }
    GUEST_USER(const GUEST_USER& other);
    GUEST_USER& operator=(const GUEST_USER& other);
    void start() { menu(); }
    void log();

    static void log_in(sf::Event,GUEST_USER*);
    static void create_account(sf::Event,string);

    static TEACHER* search_teacher(string name);
    static int nr_users;
    virtual ~GUEST_USER() {};
    string username;
protected:
    string password;
    virtual void menu();
private:
    sf::Texture guest_texture;
    sf::Sprite guest;
};
//inca o clasa de manager unde sunt definiti userii
