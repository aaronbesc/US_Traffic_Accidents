#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() : root(nullptr) {}

void RedBlackTree::rotateLeft(Node*& node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node*& node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (node->left != nullptr) {
        node->left->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::fixInsert(Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;
    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(const std::string& id, int severity, double distance, const std::string& city, const std::string& state, const std::string& zipcode) {
    Node* newNode = new Node(id, severity, distance, city, state, zipcode);
    if (root == nullptr) {
        newNode->color = BLACK;
        root = newNode;
    } else {
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr) {
            parent = current;
            if (newNode->ID < current->ID) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        newNode->parent = parent;
        if (newNode->ID < parent->ID) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        fixInsert(newNode);
    }
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* RedBlackTree::search(const std::string& id) {
    return searchTreeHelper(root, id);
}

Node* RedBlackTree::searchTreeHelper(Node* node, const std::string& id) {
    if (node == nullptr || node->ID == id)
        return node;
    if (id < node->ID)
        return searchTreeHelper(node->left, id);
    return searchTreeHelper(node->right, id);
}

void RedBlackTree::inorderHelper(Node* node) {
    if (node == nullptr)
        return;
    inorderHelper(node->left);
    std::cout << "ID: " << node->ID << ", Severity: " << node->severity << ", Distance: " << node->distance
              << ", City: " << node->city << ", State: " << node->state << ", Zipcode: " << node->zipcode << std::endl;
    inorderHelper(node->right);
}

void RedBlackTree::inorder() {
    inorderHelper(root);
}