#pragma once
#include <iostream>
#include <string>
#include "teacher.h"
using namespace std;

class REVIEW
{
public:
    friend class TEACHER;
    friend class STUDENT_USER;
    friend class ADMIN_USER;
    REVIEW() : rev(""), stars(0) {}
    REVIEW(string rev, int stars) : rev(rev)
    {
        while (stars < 0 || stars > 5)
        {
            cout << "Pick a number between 0 and 5\n";
            cin >> stars;
        }
        this->stars = stars;
    }
    REVIEW(const REVIEW& other) : rev(other.rev), stars(other.stars) {}
    REVIEW& operator=(const REVIEW& other) {
        if (this == &other) return *this; 
        this->rev = other.rev;
        this->stars = other.stars;
        return *this;
    }
private:
    string rev;
    int stars;
};
