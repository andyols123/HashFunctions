#include "HashMap.h"
#include <iostream>
#include <cmath>

HashMap::HashMap(int chosenHashAlgorithm)
    : bucketCount(2), elementCount(0), hashingMode(chosenHashAlgorithm), lastCalculatedBucket(0)
{
    if (hashingMode < 1 || hashingMode > 3) hashingMode = 1;
    buckets = new DynamicArray<Data>[bucketCount];
}

HashMap::~HashMap() {
    delete[] buckets;
}

// 1. Modulo operation on ASCII sum
int HashMap::hashAscii(const std::string& x) {
    int asciiSum = 0;
    for (char c : x) {
        asciiSum += static_cast<int>(c);
    }
    return asciiSum % bucketCount;
}

// 2. Multiplication method (using the fractional part of the Golden Ratio)
int HashMap::hashMultiplication(const std::string& x) {
    int asciiSum = 0;
    for (char c : x) {
        asciiSum += static_cast<int>(c);
    }
    const double A = 0.6180339887; // Golden Ratio fractional part
    double val = asciiSum * A;
    double fractionalPart = val - std::floor(val);
    return static_cast<int>(std::floor(bucketCount * fractionalPart));
}

// 3. DJB2 Algorithm
int HashMap::hashDjb2(const std::string& x) {
    unsigned long hash = 5381;
    for (char c : x) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return static_cast<int>(hash % bucketCount);
}

int HashMap::executeHashing(const std::string& x) {
    if (hashingMode == 1) return hashAscii(x);
    if (hashingMode == 2) return hashMultiplication(x);
    return hashDjb2(x);
}

void HashMap::insert(const std::string& key, const std::string& value) {
    // Check if the key already exists to prevent duplicates
    Location loc = find(key);
    if (loc.isFound) {
        buckets[loc.bucketIndex][loc.elementIndex].value = value;
        return;
    }

    elementCount++;
    resizeIfNeeded();

    lastCalculatedBucket = executeHashing(key);
    Data newData = { key, value };
    buckets[lastCalculatedBucket].addEnd(newData);
}

HashMap::Location HashMap::find(const std::string& searchKey) {
    lastCalculatedBucket = executeHashing(searchKey);
    for (int i = 0; i < buckets[lastCalculatedBucket].getSize(); i++) {
        if (buckets[lastCalculatedBucket][i].key == searchKey) {
            return { lastCalculatedBucket, i, true };
        }
    }
    return { -1, -1, false };
}

void HashMap::remove(const std::string& searchKey) {
    Location loc = find(searchKey);
    if (!loc.isFound) {
        std::cout << "Cannot remove element: Key not found.\n";
        return;
    }

    elementCount--;
    buckets[loc.bucketIndex].removeAtIndex(loc.elementIndex);

    resizeIfNeeded();
}

void HashMap::resizeIfNeeded() {
    double loadFactor = static_cast<double>(elementCount) / static_cast<double>(bucketCount);

    // Keep the load factor within bounds [0.5, 2.0]
    if (loadFactor >= 0.5 && loadFactor <= 2.0) {
        return;
    }

    int oldBucketCount = bucketCount;
    if (loadFactor > 2.0) {
        bucketCount *= 2;
    }
    else if (loadFactor < 0.5) {
        bucketCount /= 2;
        if (bucketCount < 2) bucketCount = 2;
    }

    if (bucketCount == oldBucketCount) return;

    DynamicArray<Data>* newBuckets = new DynamicArray<Data>[bucketCount];

    // Rehash all existing elements into the new bucket array
    for (int i = 0; i < oldBucketCount; i++) {
        for (int j = 0; j < buckets[i].getSize(); j++) {
            int newIndex = executeHashing(buckets[i][j].key);
            newBuckets[newIndex].addEnd(buckets[i][j]);
        }
    }

    delete[] buckets;
    buckets = newBuckets;
}

void HashMap::print() const {
    for (int i = 0; i < bucketCount; i++) {
        std::cout << "Bucket " << i << ": ";
        for (int j = 0; j < buckets[i].getSize(); j++) {
            std::cout << "[" << buckets[i][j].key << " -> " << buckets[i][j].value << "] ";
        }
        std::cout << "\n";
    }
}