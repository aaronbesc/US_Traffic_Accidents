#include "RedBlackTree.h"
#include "Hash_table.h"
#include <iostream>
#include <sstream>

// Utility function to split a string by a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void readCSVTree(const std::string& filename, RedBlackTree& rbTree) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        if (isHeader) {
            isHeader = false; // Skip the header
            continue;
        }

        auto tokens = split(line, ',');

        // Check for empty or improperly formatted lines
        if (tokens.size() != 6) {
            std::cerr << "Unexpected format at line " << lineNumber << ": " << line << std::endl;
            continue;
        }

        // Ensure essential fields are not empty
        if (tokens[0].empty() || tokens[1].empty() || tokens[2].empty() || tokens[3].empty() || tokens[4].empty() || tokens[5].empty()) {
            std::cerr << "Skipping line " << lineNumber << " due to empty fields: " << line << std::endl;
            continue;
        }

        try {
            std::string id = tokens[0]; // ID is a string
            int severity = std::stoi(tokens[1]);
            double distance = std::stod(tokens[2]);
            std::string city = tokens[3];
            std::string state = tokens[4];
            std::string zipcode = tokens[5];

            // Insert data into the Red-Black Tree
            rbTree.insert(id, severity, distance, city, state, zipcode);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data encountered at line " << lineNumber << ": " << line << "\nError: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Data out of range at line " << lineNumber << ": " << line << "\nError: " << e.what() << std::endl;
        }
    }

    file.close();
}

void readCSVHashTable(const std::string& filename, HashTable& hashTable) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    string line;
    bool isHeader = true;
    while (std::getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        auto tokens = split(line, ',');

        if (tokens.size() >= 6) {
            try {
                TrafficAccident accident(tokens[0], std::stoi(tokens[1]), std::stod(tokens[2]), tokens[3], tokens[4], tokens[5]);
                hashTable.insert(accident);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << " in line: " << line << endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << " in line: " << line << endl;
            }
        }
    }
    file.close();
}

void menuRedBlackTree(RedBlackTree& rbTree) {
    int choice = 0;
    string id, city, state, zipcode;
    int severity;
    double distance;

    while (choice != 5) {
        cout << "\nRed Black Tree Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Search by ID\n";
        cout << "3. Remove by ID\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Severity: ";
            cin >> severity;
            cout << "Enter Distance: ";
            cin >> distance;
            cout << "Enter City: ";
            cin >> city;
            cout << "Enter State: ";
            cin >> state;
            cout << "Enter Zipcode: ";
            cin >> zipcode;
            rbTree.insert(id, severity, distance, city, state, zipcode);
        } else if (choice == 2) {
            cout << "Enter ID: ";
            cin >> id;
            if (rbTree.search(id)) {
                cout << "ID " << id << " found in the tree." << endl;
            } else {
                cout << "ID " << id << " not found in the tree." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter ID: ";
            cin >> id;
            //rbTree.remove(id);
        } else if (choice == 4) {
            rbTree.inorder();
        } else if (choice == 5) {
            cout << "Exiting Red Black Tree Menu." << endl;
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

void menuHashTable(HashTable& hashTable) {
    int choice = 0, searchType;
    string id, city, state, zipcode;
    int severity;
    double distance;

    while (choice != 5){
        cout << "\nHash Table Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove by ID\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Severity: ";
            cin >> severity;
            cout << "Enter Distance: ";
            cin >> distance;
            cout << "Enter City: ";
            cin >> city;
            cout << "Enter State: ";
            cin >> state;
            cout << "Enter Zipcode: ";
            cin >> zipcode;
            hashTable.insert(TrafficAccident(id, severity, distance, city, state, zipcode));
        } else if (choice == 2) {
            cout << "Do you want to search by:\n";
            cout << "1. ID\n";
            cout << "2. Severity\n";
            cout << "3. City\n";
            cout << "4. State\n";
            cout << "5. Zipcode\n";
            cout << "Enter your choice: ";
            cin >> searchType;

            if (searchType == 1) {
                cout << "Enter ID: ";
                cin >> id;
                if (hashTable.searchByID(id)) {
                    cout << "ID " << id << " found in the hash table." << endl;
                } else {
                    cout << "ID " << id << " not found in the hash table." << endl;
                }
            } else if (searchType == 2) {
                cout << "Enter Severity: ";
                cin >> severity;
                HashTable results = hashTable.searchBySeverity(severity);
                results.display();
            } else if (searchType == 3) {
                cout << "Enter City: ";
                cin >> city;
                HashTable results = hashTable.searchByCity(city);
                results.display();
            } else if (searchType == 4) {
                cout << "Enter State: ";
                cin >> state;
                HashTable results = hashTable.searchByState(state);
                results.display();
            } else if (searchType == 5) {
                cout << "Enter Zipcode: ";
                cin >> zipcode;
                HashTable results = hashTable.searchByZipcode(zipcode);
                results.display();
            } else {
                cout << "Invalid search type, please try again." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter ID: ";
            cin >> id;
            hashTable.remove(id);
        } else if (choice == 4) {
            hashTable.display();
        } else if (choice == 5) {
            cout <<"Exiting Hash Table Menu." << endl;
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

int main() {
    HashTable hashTable;
    RedBlackTree rbTree;

    // Read from CSV and populate the hash table and red-black tree
    readCSVHashTable("../Database/US_Accidents_MarchCORRECTED.csv", hashTable);
    readCSVTree("../Database/US_Accidents_MarchCORRECTED.csv", rbTree);

    int choice;

    cout << "Welcome to the US Traffic accidents (2016-2023) Database" << endl;
    cout << "Two data structures are used to store a database containing 100,000 accidents,(Red-Black Tree, Hash Table)." << endl;

    cout << "Which data structure do you want to use?" << endl;
    cout << "1. Red Black Tree" << endl;
    cout << "2. Hash Table" << endl;
    cout << "Enter your choice: " ;
    cin >> choice;

    if (choice == 1) {
        menuRedBlackTree(rbTree);
    } else if (choice == 2) {
        menuHashTable(hashTable);
    } else {
        cout << "Invalid choice, exiting." << endl;
    }

    return 0;
}