#include "RedBlackTree.h"
#include <vector>
#include <functional>

// Constructor initializes the root to nullptr
RedBlackTree::RedBlackTree() : root(nullptr) {}

// Rotate the subtree left around the given node
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

// Rotate the subtree right around the given node
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

// Fix the red-black tree properties after insertion
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

// Transplant the subtree rooted at node u with the subtree rooted at node v
void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

// Fix the red-black tree properties after deletion
void RedBlackTree::fixDelete(Node*& node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

// Insert a new node with the given data into the red-black tree
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

// Find the node with the minimum value in the subtree rooted at the given node
Node* RedBlackTree::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Search for a node with the given ID in the red-black tree
Node* RedBlackTree::search(const std::string& id) {
    return searchTreeHelper(root, id);
}

// Helper function to search for a node with the given ID in the subtree rooted at the given node
Node* RedBlackTree::searchTreeHelper(Node* node, const std::string& id) {
    if (node == nullptr || node->ID == id)
        return node;
    if (id < node->ID)
        return searchTreeHelper(node->left, id);
    return searchTreeHelper(node->right, id);
}

// Helper function to perform inorder traversal of the red-black tree and print node data
void RedBlackTree::inorderHelper(Node* node) {
    if (node == nullptr)
        return;
    inorderHelper(node->left);
    std::cout << "ID: " << node->ID << ", Severity: " << node->severity << ", Distance: " << node->distance
              << ", City: " << node->city << ", State: " << node->state << ", Zipcode: " << node->zipcode << std::endl;
    inorderHelper(node->right);
}

// Perform inorder traversal of the red-black tree and print node data
void RedBlackTree::inorder() {
    inorderHelper(root);
}

// Find nodes that match the given criteria
std::vector<Node*> RedBlackTree::find(int severity, const std::string& city, const std::string& state, const std::string& zipcode) {
    std::vector<Node*> result;
    findHelper(root, severity, city, state, zipcode, result);
    return result;
}

// Helper function to find nodes that match the given criteria in the subtree rooted at the given node
void RedBlackTree::findHelper(Node* node, int severity, const std::string& city, const std::string& state, const std::string& zipcode, std::vector<Node*>& result) {
    if (node == nullptr)
        return;

    if ((severity == 0 || node->severity == severity) &&
        (city.empty() || node->city == city) &&
        (state.empty() || node->state == state) &&
        (zipcode.empty() || node->zipcode == zipcode)) {
        result.push_back(node);
    }

    findHelper(node->left, severity, city, state, zipcode, result);
    findHelper(node->right, severity, city, state, zipcode, result);
}

// Remove a node with the given ID from the red-black tree
void RedBlackTree::remove(const std::string& id) {
    Node* nodeToDelete = search(id);
    if (nodeToDelete == nullptr) {
        std::cout << "Node with ID " << id << " not found in the tree." << std::endl;
        return;
    }

    Node* y = nodeToDelete;
    Node* x = nullptr;
    Node* xParent = nullptr;
    Color originalColor = y->color;

    if (nodeToDelete->left == nullptr) {
        x = nodeToDelete->right;
        transplant(nodeToDelete, nodeToDelete->right);
    } else if (nodeToDelete->right == nullptr) {
        x = nodeToDelete->left;
        transplant(nodeToDelete, nodeToDelete->left);
    } else {
        y = minimum(nodeToDelete->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == nodeToDelete) {
            if (x != nullptr) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = nodeToDelete->right;
            if (y->right != nullptr) y->right->parent = y;
        }
        transplant(nodeToDelete, y);
        y->left = nodeToDelete->left;
        if (y->left != nullptr) y->left->parent = y;
        y->color = nodeToDelete->color;
    }

    delete nodeToDelete;

    if (originalColor == BLACK) {
        fixDelete(x);
    }
}

// Check if the red-black tree is empty
bool RedBlackTree::isEmpty() const {
    return root == nullptr;
}

// Get the number of nodes in the red-black tree
int RedBlackTree::getSize() const {
    int count = 0;
    std::function<void(Node*)> countNodes = [&](Node* node) {
        if (node == nullptr) return;
        count++;
        countNodes(node->left);
        countNodes(node->right);
    };
    countNodes(root);
    return count;
}

// Search for nodes with the given severity in the red-black tree
std::vector<Node*> RedBlackTree::searchBySeverity(int severity) const {
    return const_cast<RedBlackTree*>(this)->find(severity, "", "", "");
}

// Search for nodes with the given city in the red-black tree
std::vector<Node*> RedBlackTree::searchByCity(const std::string& city) const {
    return const_cast<RedBlackTree*>(this)->find(0, city, "", "");
}

// Search for nodes with the given state in the red-black tree
std::vector<Node*> RedBlackTree::searchByState(const std::string& state) const {
    return const_cast<RedBlackTree*>(this)->find(0, "", state, "");
}

// Search for nodes with the given zipcode in the red-black tree
std::vector<Node*> RedBlackTree::searchByZipcode(const std::string& zipcode) const {
    return const_cast<RedBlackTree*>(this)->find(0, "", "", zipcode);
}

// Get all nodes in the red-black tree
std::vector<Node*> RedBlackTree::getAllNodes() const {
    std::vector<Node*> nodes;
    inorderTraversal(root, nodes);
    return nodes;
}

// Helper function to perform inorder traversal and collect nodes in the given vector
void RedBlackTree::inorderTraversal(Node* node, std::vector<Node*>& nodes) const {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left, nodes);
    nodes.push_back(node);
    inorderTraversal(node->right, nodes);
}

// Filter nodes by severity from the given vector of nodes
std::vector<Node*> RedBlackTree::filterBySeverity(const std::vector<Node*>& nodes, int severity) const {
    std::vector<Node*> filtered;
    for (const auto& node : nodes) {
        if (node->severity == severity) {
            filtered.push_back(node);
        }
    }
    return filtered;
}

// Filter nodes by city from the given vector of nodes
std::vector<Node*> RedBlackTree::filterByCity(const std::vector<Node*>& nodes, const std::string& city) const {
    std::vector<Node*> filtered;
    for (const auto& node : nodes) {
        if (node->city == city) {
            filtered.push_back(node);
        }
    }
    return filtered;
}

// Filter nodes by state from the given vector of nodes
std::vector<Node*> RedBlackTree::filterByState(const std::vector<Node*>& nodes, const std::string& state) const {
    std::vector<Node*> filtered;
    for (const auto& node : nodes) {
        if (node->state == state) {
            filtered.push_back(node);
        }
    }
    return filtered;
}

// Filter nodes by zipcode from the given vector of nodes
std::vector<Node*> RedBlackTree::filterByZipcode(const std::vector<Node*>& nodes, const std::string& zipcode) const {
    std::vector<Node*> filtered;
    for (const auto& node : nodes) {
        if (node->zipcode == zipcode) {
            filtered.push_back(node);
        }
    }
    return filtered;
}
