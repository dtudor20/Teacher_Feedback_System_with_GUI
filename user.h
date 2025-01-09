#pragma once
#include "teacher.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

class TEACHER;
class REVIEW;
class GUEST_USER
{
public:
    GUEST_USER() {};
    GUEST_USER(string password, string username)
        : password(password), username(username) {
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
};

class TEACHER_USER : virtual public GUEST_USER
{
public:
    TEACHER_USER() {};
    TEACHER_USER(string password, string username)
        : GUEST_USER(password, username) {
    }
    void delete_teacher();
    string teacher_name;
private:
    void menu() override;
};

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
    }
    void search(sf::Event);
    void see_reviews();
    REVIEW* user_reviews;
    int nr_user_reviews;
private:
    void menu() override; 
};

class ADMIN_USER : public STUDENT_USER, public TEACHER_USER
{
public:
    ADMIN_USER() {};
    ADMIN_USER(string password, string username) : GUEST_USER(password, username) {};
private:
    void menu() override;
};
//inca o clasa de manager unde sunt definiti userii
