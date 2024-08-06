#include <iostream>
#include <string>
#include <vector>

enum Color { RED, BLACK };

struct Node {
    std::string ID;
    int severity;
    double distance;
    std::string city;
    std::string state;
    std::string zipcode;
    Color color;
    Node *left, *right, *parent;

    Node(const std::string& id, int sev, double dist, const std::string& cty, const std::string& st, const std::string& zip)
            : ID(id), severity(sev), distance(dist), city(cty), state(st), zipcode(zip), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void fixInsert(Node*& node);
    void fixDelete(Node*& node);
    Node* searchTreeHelper(Node* node, const std::string& id);
    void inorderHelper(Node* node);
    void findHelper(Node* node, int severity, const std::string& city, const std::string& state, const std::string& zipcode, std::vector<Node*>& result);
    void transplant(Node* u, Node* v);
    void inorderTraversal(Node* node, std::vector<Node*>& nodes) const;

public:
    RedBlackTree();
    void insert(const std::string& id, int severity, double distance, const std::string& city, const std::string& state, const std::string& zipcode);
    void remove(const std::string& id);
    Node* search(const std::string& id);
    Node* minimum(Node* node);
    void inorder();
    std::vector<Node*> find(int severity, const std::string& city, const std::string& state, const std::string& zipcode);

    bool isEmpty() const;
    int getSize() const;
    std::vector<Node*> searchBySeverity(int severity) const;
    std::vector<Node*> searchByCity(const std::string& city) const;
    std::vector<Node*> searchByState(const std::string& state) const;
    std::vector<Node*> searchByZipcode(const std::string& zipcode) const;
    std::vector<Node*> getAllNodes() const;
    std::vector<Node*> filterBySeverity(const std::vector<Node*>& nodes, int severity) const;
    std::vector<Node*> filterByCity(const std::vector<Node*>& nodes, const std::string& city) const;
    std::vector<Node*> filterByState(const std::vector<Node*>& nodes, const std::string& state) const;
    std::vector<Node*> filterByZipcode(const std::vector<Node*>& nodes, const std::string& zipcode) const;
};
