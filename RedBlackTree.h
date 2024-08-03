#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

enum Color { RED, BLACK };

struct Node {
    std::string ID; // Unique identifier for the accident (changed to string)
    int severity; // Severity of the accident
    double distance; // Distance related to the accident
    std::string city; // City where the accident occurred
    std::string state; // State where the accident occurred
    std::string zipcode; // Zipcode where the accident occurred
    Color color;
    Node *left, *right, *parent;

    Node(const std::string& id, int sev, double dist, const std::string& c, const std::string& st, const std::string& zip)
            : ID(id), severity(sev), distance(dist), city(c), state(st), zipcode(zip), color(RED),
              left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void fixInsert(Node*&);
    void inorderHelper(Node*);
    Node* searchTreeHelper(Node* node, const std::string& id);
    Node* minimum(Node* node);

public:
    RedBlackTree();
    void insert(const std::string& id, int severity, double distance, const std::string& city, const std::string& state, const std::string& zipcode);
    void inorder();
    Node* search(const std::string& id);
};