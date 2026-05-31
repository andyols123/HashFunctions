#pragma once
#include <string>
#include "DynamicArray.h"

class HashMap
{
public:
    struct Data
    {
        std::string key;
        std::string value;
    };

    struct Location
    {
        int bucketIndex;
        int elementIndex;
        bool isFound;
    };

    HashMap(int chosenHashAlgorithm = 1);
    ~HashMap();

    void insert(const std::string& key, const std::string& value);
    Location find(const std::string& searchKey);
    void remove(const std::string& searchKey);
    void print() const;

private:
    DynamicArray<Data>* buckets;
    int lastCalculatedBucket;
    int bucketCount;    // total number of buckets (m)
    int elementCount;   // total number of elements in the map (n)
    int hashingMode;

    int hashAscii(const std::string& x);
    int hashMultiplication(const std::string& x);
    int hashDjb2(const std::string& x);
    int executeHashing(const std::string& x);

    void resizeIfNeeded();
};