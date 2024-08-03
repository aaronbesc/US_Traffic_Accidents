#include "Hash_table.h"
#include <iostream>

using namespace std;

// Constructor
HashTable::HashTable(int buckets) : numBuckets(buckets), size(0) {
    table.resize(numBuckets);
}

// Hash function, it uses the hash<string> object that converts a string into a hash value
// it is then module by the number of buckets to generate the final index value.
int HashTable::hashFunction(const string& key) const {
    hash<string> HASH;
    return HASH(key) % numBuckets;
}

// Resize function and doubles the size of the table. it does not check the LoadFactor
void HashTable::resize() {
    int newNumBuckets = numBuckets * 2;

    //create a new resized table
    vector<Buckets> newTable(newNumBuckets);

    //iterates over the old table and get the new hash values
    for (const auto& accident : table) {
        if (accident.isOccupied && !accident.isDeleted) {
            std::hash<std::string> HASH;
            int index = HASH(accident.accident.ID) % newNumBuckets;

            //probing
            while (newTable[index].isOccupied) {
                index = (index + 1) % newNumBuckets;
            }
            //insertion of the current accidents in the new table
            newTable[index] = accident;
        }
    }

    //update the table and number of buckets
    table = std::move(newTable);
    numBuckets = newNumBuckets;
}

// Insert function, inserts an accident on the table at its calculated hash index
void HashTable::insert(const TrafficAccident& accident) {

    //first, check if the load factor is >= to 0.8 then resize
    if (size >= numBuckets * 0.8) {
        resize();
    }

    // find the index of this new data
    int index = hashFunction(accident.ID);
    int originalIndex = index;

    //probing, if the
    while (table[index].isOccupied && !table[index].isDeleted) {
        index = (index + 1) % numBuckets;

        //debbuging purposes mostly
        if (index == originalIndex) {
            cout << "HashTable is full, cannot insert!" << endl;
            return;
        }
    }

    //insert the accident on the index, and mark that index as occupied and not deleted
    table[index].accident = accident;
    table[index].isOccupied = true;
    table[index].isDeleted = false;

    //update the size
    ++size;
}

// Remove function, removes a specified accident by its ID
void HashTable::remove(const std::string& id) {

    //get the index of the ID
    int index = hashFunction(id);
    int originalIndex = index;

    //Just search on the occupied places
    while (table[index].isOccupied) {

        //if the index is not deleted and is the value desired to remove, then mark it as deleted
        if (!table[index].isDeleted && table[index].accident.ID == id) {
            table[index].isDeleted = true;
            --size;
            return;
        }

        //probing to the next element on the table
        index = (index + 1) % numBuckets;

        //If index is not found, then we don't want an infinite loop
        if (index == originalIndex) {
            cout << "No ID found, no element removed" << endl;
            break;
        }

    }
}

//Display function, to display all the table, no much explanation
void HashTable::display() const {
    for (int i = 0; i < numBuckets; ++i) {
        if (table[i].isOccupied && !table[i].isDeleted) {
            const auto& acc = table[i].accident;
            cout << "ID: " << acc.ID
                 << ", Severity: " << acc.severity
                 << ", Distance: " << acc.distance
                 << ", City: " << acc.city
                 << ", State: " << acc.state
                 << ", Zipcode: " << acc.zipcode << std::endl;
        }
    }
}

// Check if the hash table is empty
bool HashTable::isEmpty() const {
    return size == 0;
}

//searches an accident by its ID and returns tha accident as a TrafficAccident* object
TrafficAccident* HashTable::searchByID(const std::string& id) {

    int index = hashFunction(id);
    int originalIndex = index;

    //Iterating over the table to find a match
    while (table[index].isOccupied) {
        if (!table[index].isDeleted && table[index].accident.ID == id) {
            return &table[index].accident;
        }
        //probing to go to the next value
        index = (index + 1) % numBuckets;

        //again, no infinite loop, I learned this the awful way
        if (index == originalIndex) {
            break;
        }
    }
    //If no accident found return a null pointer
    return nullptr;
}

//searches all the accidents with a specified severity and returns a hash table with all the values
HashTable HashTable::searchBySeverity(int severity) const {
    HashTable result(numBuckets);

    //iterate over the whole table if the accident matches the severity then insert it into this new table
    for (const auto& entry : table) {
        if (entry.isOccupied && !entry.isDeleted && entry.accident.severity == severity) {
            result.insert(entry.accident);
        }
    }
    return result;
}

//searches all the accidents in a specified city and returns a hash table with all the values
HashTable HashTable::searchByCity(const std::string& city) const {
    HashTable result(numBuckets);

    //iterate over the whole table if the accident matches the city then insert it into this new table
    for (const auto& entry : table) {
        if (entry.isOccupied && !entry.isDeleted && entry.accident.city == city) {
            result.insert(entry.accident);
        }
    }
    return result;
}

//searches all the accidents in a specified state and returns a hash table with all the values
HashTable HashTable::searchByState(const std::string& state) const {
    HashTable result(numBuckets);

    //iterate over the whole table if the accident matches the state then insert it into this new table
    for (const auto& entry : table) {
        if (entry.isOccupied && !entry.isDeleted && entry.accident.state == state) {
            result.insert(entry.accident);
        }
    }
    return result;
}

//searches all the accidents in a specified zone by its zipcode and returns a hash table with all the values
HashTable HashTable::searchByZipcode(const std::string& zipcode) const {
    HashTable result(numBuckets);

    //iterate over the whole table if the accident matches the zipcode then insert it into this new table
    for (const auto& entry : table) {
        if (entry.isOccupied && !entry.isDeleted && entry.accident.zipcode == zipcode) {
            result.insert(entry.accident);
        }
    }
    return result;
}

// Get the size of the hash table
int HashTable::getSize() const {
    return size;
}

// Get the number of buckets in the hash table
int HashTable::getBucketCount() const {
    return numBuckets;
}

// Get the size of a specific bucket (just to show that we are using an open addressing, all used indexes should be 1)
int HashTable::getBucketSize(int index) const {
    if (index < 0 || index >= numBuckets) {
        //if the item is out of bounds return -1
        cout << "item out of bounds" << endl;
        return -1;
    }
    if (table[index].isOccupied && !table[index].isDeleted) {
        return 1;
    } else {
        return 0;
    }
}

// Get the load factor of the hash table
float HashTable::getLoadFactor() const {
    return static_cast<float>(size) / numBuckets;
}