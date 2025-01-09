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
    ADMIN_USER(string password, string username) : GUEST_USER(password, username) {};
private:
    void menu() override;
};