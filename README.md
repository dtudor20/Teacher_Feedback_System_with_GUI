# Teaching Platform User Management System

This project is a user management system for a teaching platform. It includes different types of users such as guest users, student users, teacher users, and admin users. The project is built using C++20 standards and the SFML library for graphics, and it is managed using CMake with the Ninja generator.

## Classes

- **GUEST_USER**: Base class for all users. Provides basic functionalities like logging in and creating accounts.
- **STUDENT_USER**: Inherits from GUEST_USER. Allows students to search and see reviews.
- **TEACHER_USER**: Inherits from GUEST_USER. Allows teachers to manage their profiles and reviews.
- **ADMIN_USER**: Inherits from STUDENT_USER and TEACHER_USER. Provides administrative functionalities.
- **REVIEW**: Represents a review with a text and star rating.

## Dependencies

- SFML (Simple and Fast Multimedia Library)
- CMake
- Ninja

## Building the Project

1. Ensure you have CMake and Ninja installed on your system.
2. Clone the repository.
3. Navigate to the project directory.
4. Run the following commands to build the project:
5. Or just use the exe file!!!

    
