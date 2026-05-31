#include <iostream>
#include <string>
#include <cassert>
#include "HashMap.h"

// Test dla Algorytmu 1: Modulo z sumy ASCII
void testAsciiHashing() {
    std::cout << "--- Testing Hashing Mode 1: ASCII Modulo ---\n";
    HashMap map(1);

    map.insert("Apple", "Red");
    map.insert("Banana", "Yellow");
    map.insert("Grape", "Purple");

    std::cout << "Map state (ASCII Modulo):\n";
    map.print();

    HashMap::Location loc = map.find("Banana");
    assert(loc.isFound == true);
    std::cout << "Successfully verified 'Banana' in Mode 1.\n";
    std::cout << "--------------------------------------------\n\n";
}

// Test dla Algorytmu 2: Metoda mnożenia (Złoty Podział)
void testMultiplicationHashing() {
    std::cout << "--- Testing Hashing Mode 2: Multiplication Method ---\n";
    HashMap map(2);

    map.insert("USD", "United States Dollar");
    map.insert("EUR", "Euro");
    map.insert("PLN", "Polish Zloty");
    map.insert("GBP", "British Pound");

    std::cout << "Map state (Multiplication Method):\n";
    map.print();

    HashMap::Location loc = map.find("PLN");
    assert(loc.isFound == true);
    std::cout << "Successfully verified 'PLN' in Mode 2.\n";
    std::cout << "--------------------------------------------\n\n";
}

// Test dla Algorytmu 3: Algorytm DJB2 (Operacje bitowe)
void testDjb2Hashing() {
    std::cout << "--- Testing Hashing Mode 3: DJB2 Algorithm ---\n";
    HashMap map(3);

    map.insert("C++", "Stroustrup");
    map.insert("Python", "Van Rossum");
    map.insert("Java", "Gosling");

    std::cout << "Map state (DJB2):\n";
    map.print();

    HashMap::Location loc = map.find("C++");
    assert(loc.isFound == true);
    std::cout << "Successfully verified 'C++' in Mode 3.\n";
    std::cout << "--------------------------------------------\n\n";
}

// Test automatycznego skalowania (rehashingu) w górę i w dół
void testRehashingBehavior() {
    std::cout << "--- Testing Automatic Rehashing (Load Factor Control) ---\n";
    // Używamy domyślnego algorytmu, ale wrzucamy dużo elementów
    HashMap storage(1);

    std::cout << "Inserting elements to trigger upscale resizing...\n";
    storage.insert("Key1", "Value1");
    storage.insert("Key2", "Value2");
    storage.insert("Key3", "Value3");
    storage.insert("Key4", "Value4");
    storage.insert("Key5", "Value5");

    std::cout << "Map state after upscale:\n";
    storage.print();
    std::cout << "\n";

    std::cout << "Removing elements to trigger downscale resizing...\n";
    storage.remove("Key1");
    storage.remove("Key2");
    storage.remove("Key3");
    storage.remove("Key4");

    std::cout << "Map state after downscale:\n";
    storage.print();
    std::cout << "--------------------------------------------\n\n";
}

int main()
{
    std::cout << "=====================================\n";
    std::cout << "   Comprehensive HashMap Test Suite  \n";
    std::cout << "=====================================\n\n";

    try {
        // Uruchomienie testów dla wszystkich 3 algorytmów haszujących
        testAsciiHashing();
        testMultiplicationHashing();
        testDjb2Hashing();

        // Test mechanizmu resize
        testRehashingBehavior();

        std::cout << "All tests executed and verified successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
    }

    return 0;
}