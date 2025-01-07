#pragma once
#include "user.h"
#include "review.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class USER;
class REVIEW;

class TEACHER
{
public:
	friend class GUEST_USER;
	friend class TEACHER_USER;
	friend class STUDENT_USER;
	friend class ADMIN_USER;
	TEACHER() : name(""), reviews(nullptr), nr_reviews(0) {}
	TEACHER(string name) : name(name),reviews(nullptr), nr_reviews(0) {}
	
	void get_reviews();
	REVIEW add_review();
	TEACHER(const TEACHER& other); // Copy constructor
	TEACHER& operator=(const TEACHER& other); // Copy assignment operator
	~TEACHER() {
		delete[] reviews;
	}
	string name;
	double average_stars=0.0;

private:
	REVIEW* reviews;
	int nr_reviews;
	
};
