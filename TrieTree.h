#pragma once
#include <iostream>
#include <string>
#include "user.h"
#include "teacher.h"
const int ALPHABET_SIZE = 128; // Adjust size for ASCII characters

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    GUEST_USER* user; // Pointer to GUEST_USER object
    TEACHER* teacher; // Pointer to TEACHER object
};

TrieNode* getNode();
void insertUser(TrieNode* root, GUEST_USER* user);
void insertTeacher(TrieNode* root, TEACHER* teacher);
GUEST_USER* searchUser(TrieNode* root, const std::string& username);
TEACHER* searchTeacher(TrieNode* root, const std::string& username);
TrieNode* removeUser(TrieNode* root, const std::string& username, int depth = 0);
TrieNode* removeTeacher(TrieNode* root, const std::string& username, int depth = 0);
bool isEmpty(TrieNode* root);
extern struct TrieNode* root;
extern struct TrieNode* userTrie;