#include "trieTree.h"
#include "user.h"
using namespace std;
struct TrieNode* root = getNode();
TrieNode* userTrie = getNode();
// Returns new trie node (initialized to NULLs)
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;
    pNode->user = nullptr;
    pNode->teacher = nullptr;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts user into trie
// If the username is prefix of trie node, just
// marks leaf node
void insertUser(struct TrieNode* root, GUEST_USER* user)
{
    struct TrieNode* pCrawl = root;
    string key = user->username;

    for (std::string::size_type i = 0; i < key.length(); i++) {
        int index = key[i];
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf and store user
    pCrawl->isEndOfWord = true;
    pCrawl->user = user;
}

// If not present, inserts teacher into trie
// If the username is prefix of trie node, just
// marks leaf node
void insertTeacher(struct TrieNode* root, TEACHER* teacher)
{
    struct TrieNode* pCrawl = root;
    string key = teacher->name;

    for (std::string::size_type i = 0; i < key.length(); i++) {

        int index = key[i];
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf and store teacher
    pCrawl->isEndOfWord = true;
    pCrawl->teacher = teacher;
}

// Returns pointer to GUEST_USER if username presents in trie, else nullptr
GUEST_USER* searchUser(struct TrieNode* root, const std::string& username)
{
    struct TrieNode* pCrawl = root;
    for (std::string::size_type i = 0; i < username.length(); i++) {
        int index = username[i];
        if (!pCrawl->children[index])
            return nullptr;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->user != nullptr) {
        return pCrawl->user;
    }
    else {
        return nullptr;
    }
}

// Returns pointer to TEACHER if username presents in trie, else nullptr
TEACHER* searchTeacher(struct TrieNode* root, const std::string& username)
{
    struct TrieNode* pCrawl = root;

    for (std::string::size_type i = 0; i < username.length(); i++) {

        int index = username[i];
        if (!pCrawl || !pCrawl->children[index])
            return nullptr;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->teacher != nullptr) {
        return pCrawl->teacher;
    }
    else {
        return nullptr;
    }
}


// Returns true if root has no children, else false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Recursive function to delete a username from given Trie
TrieNode* removeUser(TrieNode* root, const std::string& username, int depth)
{
    // If tree is empty
    if (!root)
        return NULL;

    // If last character of username is being processed
    if (depth == username.size()) {

        // This node is no more end of word after
        // removal of given username
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
            delete root->user;
            root->user = nullptr;
        }

        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the child
    // obtained using ASCII value
    int index = username[depth];
    root->children[index] =
        removeUser(root->children[index], username, depth + 1);

    // If root does not have any child (its only child got 
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }

    return root;
}

// Recursive function to delete a username from given Trie
TrieNode* removeTeacher(TrieNode* root, const std::string& username, int depth)
{
    // If tree is empty
    if (!root)
        return NULL;

    // If last character of username is being processed
    if (depth == username.size()) {

        // This node is no more end of word after
        // removal of given username
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
            delete root->teacher;
            root->teacher = nullptr;
        }

        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete root;
            return NULL;
        }

        return root;
    }

    // If not last character, recur for the child
    // obtained using ASCII value
    int index = username[depth];
    root->children[index] = removeTeacher(root->children[index], username, depth + 1);

    // If root does not have any child (its only child got 
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete root;
        return NULL;
    }

    return root;
}

