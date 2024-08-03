#include <string>
#include <vector>
#include "TrafficAccident.h"

using namespace std;

//struct containing the data for each bucket in the hash table
struct Buckets {
    TrafficAccident accident;
    bool isOccupied;
    bool isDeleted;

    Buckets() : isOccupied(false), isDeleted(false) {}
};

class HashTable {
private:

    std::vector<Buckets> table;
    int numBuckets;
    int size;

    int hashFunction(const std::string& key) const;

public:
    HashTable(int buckets = 101);
    void resize();
    void insert(const TrafficAccident& accident);
    void remove(const std::string& id);
    void display() const;
    bool isEmpty() const;
    TrafficAccident* searchByID(const std::string& id);
    HashTable searchBySeverity(int severity) const;
    HashTable searchByCity(const std::string& city) const;
    HashTable searchByState(const std::string& state) const;
    HashTable searchByZipcode(const std::string& zipcode) const;
    int getSize() const;
    int getBucketCount() const;
    int getBucketSize(int index) const;
    float getLoadFactor() const;
};