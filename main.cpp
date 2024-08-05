#include "RedBlackTree.h"
#include "Hash_table.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cmath>

bool isAlphanumeric(const std::string &str) {
    for (char ch : str) {
        if (!std::isalnum(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

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
    int choice = 0, searchType;
    std::string id, city, state, zipcode;
    int severity;
    double distance;

    while (choice != 6) {
        std::cout << "\nRed Black Tree Menu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Search\n";
        std::cout << "3. Remove by ID\n";
        std::cout << "4. Display\n";
        std::cout << "5. Filter\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter Severity: ";
            std::cin >> severity;
            std::cout << "Enter Distance: ";
            std::cin >> distance;
            std::cout << "Enter City: ";
            std::cin >> city;
            std::cout << "Enter State: ";
            std::cin >> state;
            std::cout << "Enter Zipcode: ";
            std::cin >> zipcode;

            auto start = std::chrono::system_clock::now();
            rbTree.insert(id, severity, distance, city, state, zipcode);
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
        } else if (choice == 2) {
            std::cout << "Do you want to search by:\n";
            std::cout << "1. ID\n";
            std::cout << "2. Severity\n";
            std::cout << "3. City\n";
            std::cout << "4. State\n";
            std::cout << "5. Zipcode\n";
            std::cout << "Enter your choice: ";
            std::cin >> searchType;

            auto start = std::chrono::system_clock::now();
            std::vector<Node*> results;
            if (searchType == 1) {
                std::cout << "Enter ID: ";
                std::cin >> id;
                Node* result = rbTree.search(id);
                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                if (result) {
                    std::cout << "ID: " << result->ID << ", Severity: " << result->severity << ", Distance: " << result->distance
                              << ", City: " << result->city << ", State: " << result->state << ", Zipcode: " << result->zipcode << std::endl;
                } else {
                    std::cout << "ID " << id << " not found in the tree." << std::endl;
                }
                std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
            } else {
                if (searchType == 2) {
                    std::cout << "Enter Severity: ";
                    std::cin >> severity;
                    results = rbTree.searchBySeverity(severity);
                } else if (searchType == 3) {
                    std::cout << "Enter City: ";
                    std::cin >> city;
                    results = rbTree.searchByCity(city);
                } else if (searchType == 4) {
                    std::cout << "Enter State: ";
                    std::cin >> state;
                    results = rbTree.searchByState(state);
                } else if (searchType == 5) {
                    std::cout << "Enter Zipcode: ";
                    std::cin >> zipcode;
                    results = rbTree.searchByZipcode(zipcode);
                } else {
                    std::cout << "Invalid search type, please try again." << std::endl;
                    continue;
                }
                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;

                if (!results.empty()) {
                    for (const auto& node : results) {
                        std::cout << "ID: " << node->ID << ", Severity: " << node->severity << ", Distance: " << node->distance
                                  << ", City: " << node->city << ", State: " << node->state << ", Zipcode: " << node->zipcode << std::endl;
                    }
                } else {
                    std::cout << "No results found." << std::endl;
                }
                std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
            }
        } else if (choice == 3) {
            std::cout << "Enter ID: ";
            std::cin >> id;
            auto start = std::chrono::system_clock::now();
            rbTree.remove(id);
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
        } else if (choice == 4) {
            auto start = std::chrono::system_clock::now();
            rbTree.inorder();
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;
        } else if (choice == 5) {
            RedBlackTree filteredTree = rbTree;
            char continueFiltering = 'y';
            while (continueFiltering == 'y' || continueFiltering == 'Y') {
                std::cout << "\nChoose a filter:\n";
                std::cout << "1. Severity\n";
                std::cout << "2. City\n";
                std::cout << "3. State\n";
                std::cout << "4. Zipcode\n";
                std::cout << "Enter your choice: ";
                std::cin >> searchType;

                auto start = std::chrono::system_clock::now();
                if (searchType == 1) {
                    std::cout << "Enter Severity: ";
                    if (!(std::cin >> severity)) {
                        cout << "Input not valid" << endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTree = RedBlackTree();
                    for (auto& node : rbTree.searchBySeverity(severity)) {
                        filteredTree.insert(node->ID, node->severity, node->distance, node->city, node->state, node->zipcode);
                    }
                } else if (searchType == 2) {
                    std::cout << "Enter City: ";
                    std::cin >> city;
                    if (!isAlphanumeric(city)){
                        cout << "Input not valid" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTree = RedBlackTree();
                    for (auto& node : rbTree.searchByCity(city)) {
                        filteredTree.insert(node->ID, node->severity, node->distance, node->city, node->state, node->zipcode);
                    }
                } else if (searchType == 3) {
                    std::cout << "Enter State: ";
                    std::cin >> state;
                    if (!isAlphanumeric(state)){
                        cout << "Input not valid" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTree = RedBlackTree();
                    for (auto& node : rbTree.searchByState(state)) {
                        filteredTree.insert(node->ID, node->severity, node->distance, node->city, node->state, node->zipcode);
                    }
                } else if (searchType == 4) {
                    std::cout << "Enter Zipcode: ";
                    std::cin >> zipcode;
                    if (!isAlphanumeric(zipcode)){
                        cout << "Input not valid" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTree = RedBlackTree();
                    for (auto& node : rbTree.searchByZipcode(zipcode)) {
                        filteredTree.insert(node->ID, node->severity, node->distance, node->city, node->state, node->zipcode);
                    }
                } else {
                    std::cout << "Invalid search type, please try again." << std::endl;
                    continue;
                }
                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                std::cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << std::endl;

                std::cout << "Do you want to apply another filter? (y/n): ";
                std::cin >> continueFiltering;
            }
            filteredTree.inorder();
        } else if (choice == 6) {
            std::cout << "Exiting Red Black Tree Menu." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}



void menuHashTable(HashTable& hashTable) {
    int choice = 0, searchType;
    string id, city, state, zipcode;
    int severity;
    double distance;

    while (choice != 6){
        cout << "\nHash Table Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove by ID\n";
        cout << "4. Display\n";
        cout << "5. Filter\n";
        cout << "6. Exit\n";
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

            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            hashTable.insert(TrafficAccident(id, severity, distance, city, state, zipcode));
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;

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
                TrafficAccident* accident = hashTable.searchByID(id);
                if (accident) {
                    std::cout << "ID: " << accident->ID << ", Severity: " << accident->severity << ", Distance: " << accident->distance
                              << ", City: " << accident->city << ", State: " << accident->state << ", Zipcode: " << accident->zipcode << std::endl;
                } else {
                    std::cout << "ID " << id << " not found in the hash table." << std::endl;
                }
            } else if (searchType == 2) {
                cout << "Enter Severity: ";
                cin >> severity;

                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                HashTable results = hashTable.searchBySeverity(severity);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                results.display();
                cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;

            } else if (searchType == 3) {
                cout << "Enter City: ";
                cin >> city;

                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                HashTable results = hashTable.searchByCity(city);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                results.display();
                cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;

            } else if (searchType == 4) {


                cout << "Enter State: ";
                cin >> state;

                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                HashTable results = hashTable.searchByState(state);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                results.display();
                cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;

            } else if (searchType == 5) {
                cout << "Enter Zipcode: ";
                cin >> zipcode;
                chrono::time_point<chrono::system_clock> start, end;
                start = chrono::system_clock::now();
                HashTable results = hashTable.searchByZipcode(zipcode);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                results.display();
                cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;
            } else {
                cout << "Invalid search type, please try again." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter ID: ";
            cin >> id;

            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            hashTable.remove(id);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;

        } else if (choice == 4) {
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            hashTable.display();
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << "\nElapsed Time: " << elapsed_seconds.count() << "s" << endl;
        } else if (choice == 5) {
            HashTable filteredTable = hashTable;
            char continueFiltering = 'y';
            while (continueFiltering == 'y' || continueFiltering == 'Y') {
                std::cout <<"\nChoose a filter:\n";
                cout << "1. Severity\n";
                cout << "2. City\n";
                cout << "3. State\n";
                cout << "4. Zipcode\n";
                cout << "Enter your choice: ";
                cin >> searchType;

                if (searchType == 1) {
                    cout << "Enter Severity: ";
                    if (!(std::cin >> severity)) {
                        cout << "Input not valid" << endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTable = filteredTable.searchBySeverity(severity);
                } else if (searchType == 2) {
                    cout << "Enter City: ";
                    cin >> city;
                    if (!isAlphanumeric(city)) {
                        std::cout << "Input not valid" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTable = filteredTable.searchByCity(city);
                } else if (searchType == 3) {
                    cout << "Enter State: ";
                    cin >> state;
                    if (!isAlphanumeric(state)) {
                        std::cout << "Input not valid" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTable = filteredTable.searchByState(state);
                } else if (searchType == 4) {
                    cout << "Enter Zipcode: ";
                    cin >> zipcode;
                    if (!isAlphanumeric(zipcode)) {
                        std::cout << "Input not valid" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    filteredTable = filteredTable.searchByZipcode(zipcode);
                } else {
                    cout << "Invalid search type, please try again." << endl;
                }

                cout << "Do you want to apply another filter? (y/n): ";
                cin >> continueFiltering;
            }

            filteredTable.display();

        } else if (choice == 6) {
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
