#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class HashTableType {
    LINEAR_PROBING,
    QUADRATIC_PROBING,
    DOUBLE_HASHING
};

template<typename T>
class HashTableTester {
private:
    static void printTestResult(const std::string& testName, bool passed, std::string type) {
        std::cout << "\n[" << type << "] " << testName << ": "  << (passed ? "PASSED ✓" : "FAILED ✗") << std::endl;
        std::cout << std::string(50, '-') << std::endl;
    }

    static void printTestHeader(const std::string& testName, std::string type) {
        std::cout << "\n=== " << type << ": " << testName << " ===" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    static void printSubTestResult(const std::string& testName, bool result) {
        std::cout << std::setw(40) << std::left << testName << ": " << (result ? "PASSED ✓" : "FAILED ✗") << std::endl;
    }

    static std::string generateRandomString(int length) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);
        
        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) {
            result += alphanum[dis(gen)];
        }
        return result;
    }
    // ... (keep the existing helper functions like generateRandomString)

public:
    static void testBasicOperations(T& ht, std::string type) {
        printTestHeader("Basic Operations Test", type);
        bool passed = true;
        
        // Test 1: Initial insertion
        bool insertResult = ht.insert("John", "123 Main St");
        printSubTestResult("Initial insert", insertResult);
        passed &= insertResult;
        
        // Test 2: Search after insertion
        bool searchResult = ht.search("John");
        printSubTestResult("Search after insert", searchResult);
        passed &= searchResult;
        
        // Test 3: Update existing entry
        bool updateResult = ht.insert("John", "456 Oak St");
        printSubTestResult("Update existing entry", updateResult);
        passed &= updateResult;
        
        // Test 4: Delete entry
        bool deleteResult = ht.remove("John");
        printSubTestResult("Delete entry", deleteResult);
        passed &= deleteResult;
        
        // Test 5: Verify deletion
        bool searchAfterDelete = !ht.search("John");
        printSubTestResult("Verify deletion (should not find)", searchAfterDelete);
        passed &= searchAfterDelete;

        printTestResult("Basic Operations Test", passed, type);
    }

    static void testCollisionHandling(T& ht, std::string type) {
        printTestHeader("Collision Handling Test", type);
        bool passed = true;

        // Test 1: First insertion
        bool insert1 = ht.insert("AAA", "Address 1");
        printSubTestResult("Insert first entry 'AAA'", insert1);
        passed &= insert1;

        // Test 2: Second insertion (potential collision)
        bool insert2 = ht.insert("BBB", "Address 2");
        printSubTestResult("Insert second entry 'BBB'", insert2);
        passed &= insert2;

        // Test 3: Third insertion (potential collision)
        bool insert3 = ht.insert("CCC", "Address 3");
        printSubTestResult("Insert third entry 'CCC'", insert3);
        passed &= insert3;

        // Test 4-6: Verify all entries are findable
        bool search1 = ht.search("AAA");
        printSubTestResult("Search first entry 'AAA'", search1);
        passed &= search1;

        bool search2 = ht.search("BBB");
        printSubTestResult("Search second entry 'BBB'", search2);
        passed &= search2;

        bool search3 = ht.search("CCC");
        printSubTestResult("Search third entry 'CCC'", search3);
        passed &= search3;

        printTestResult("Collision Handling Test", passed, type);
    }

    static void testDeletionAndReinsert(T& ht, std::string type) {
        printTestHeader("Deletion and Reinsert Test", type);
        bool passed = true;

        // Test 1: Initial insertion
        bool insert1 = ht.insert("Test1", "Address 1");
        printSubTestResult("Initial insert 'Test1'", insert1);
        passed &= insert1;

        // Test 2: Verify insertion
        bool search1 = ht.search("Test1");
        printSubTestResult("Verify 'Test1' was inserted", search1);
        passed &= search1;

        // Test 3: Delete entry
        bool remove = ht.remove("Test1");
        printSubTestResult("Delete 'Test1'", remove);
        passed &= remove;

        // Test 4: Verify deletion
        bool searchAfterDelete = !ht.search("Test1");
        printSubTestResult("Verify 'Test1' was deleted", searchAfterDelete);
        passed &= searchAfterDelete;

        // Test 5: Insert new entry in potentially same slot
        bool insert2 = ht.insert("Test2", "Address 2");
        printSubTestResult("Insert new entry 'Test2'", insert2);
        passed &= insert2;

        // Test 6: Verify new entry
        bool search2 = ht.search("Test2");
        printSubTestResult("Verify 'Test2' was inserted", search2);
        passed &= search2;

        printTestResult("Deletion and Reinsert Test", passed, type);
    }

    static void testTableFull(T& ht, std::string type) {
        printTestHeader("Table Full Test", type);
        bool passed = true;

        // Fill the table
        std::vector<std::string> insertedKeys;
        for (int i = 0; i < 10; ++i) {
            std::string key = "Key" + std::to_string(i);
            bool insertResult = ht.insert(key, "Value" + std::to_string(i));
            printSubTestResult("Insert " + key, insertResult);
            passed &= insertResult;
            if (insertResult) {
                insertedKeys.push_back(key);
            }
        }

        // Try to insert when full
        bool shouldFail = ht.insert("Overflow", "Address");
        printSubTestResult("Attempt insert when full (should fail)", !shouldFail);
        passed &= !shouldFail;

        // Verify all inserted keys are still findable
        for (const auto& key : insertedKeys) {
            bool searchResult = ht.search(key);
            printSubTestResult("Verify " + key + " still exists", searchResult);
            passed &= searchResult;
        }

        printTestResult("Table Full Test", passed, type);
    }

    static void testEdgeCases(T& ht, std::string type) {
        printTestHeader("Edge Cases Test", type);
        bool passed = true;

        // Test 1: Empty string
        bool insertEmpty = ht.insert("", "Empty key address");
        printSubTestResult("Insert empty string key", insertEmpty);
        passed &= insertEmpty;

        bool searchEmpty = ht.search("");
        printSubTestResult("Search empty string key", searchEmpty);
        passed &= searchEmpty;

        // Test 2: Very long string
        std::string longString(1000, 'a');
        bool insertLong = ht.insert(longString, "Long string address");
        printSubTestResult("Insert 1000-char string key", insertLong);
        passed &= insertLong;

        bool searchLong = ht.search(longString);
        printSubTestResult("Search 1000-char string key", searchLong);
        passed &= searchLong;

        // Test 3: Special characters
        bool insertSpecial = ht.insert("!@#$%^&*()", "Special chars address");
        printSubTestResult("Insert special characters key", insertSpecial);
        passed &= insertSpecial;

        bool searchSpecial = ht.search("!@#$%^&*()");
        printSubTestResult("Search special characters key", searchSpecial);
        passed &= searchSpecial;

        // Test 4: Multiple deletes
        bool deleteEmpty = ht.remove("");
        printSubTestResult("Delete empty string key", deleteEmpty);
        passed &= deleteEmpty;

        bool deleteLong = ht.remove(longString);
        printSubTestResult("Delete long string key", deleteLong);
        passed &= deleteLong;

        bool deleteSpecial = ht.remove("!@#$%^&*()");
        printSubTestResult("Delete special characters key", deleteSpecial);
        passed &= deleteSpecial;

        printTestResult("Edge Cases Test", passed, type);
    }

    static void runPerformanceTest(T& ht, std::string type, 
                                 const std::vector<std::string>& testKeys) {
        printTestHeader("Performance Test", type);
        
        auto start = std::chrono::high_resolution_clock::now();
        int successfulOps = 0;

        // Insertions
        std::cout << "\nPerforming insertions..." << std::endl;
        for (size_t i = 0; i < testKeys.size(); ++i) {
            if (ht.insert(testKeys[i], "Value" + std::to_string(i))) {
                successfulOps++;
            }
        }
        printSubTestResult("Insertions completed", true);
        std::cout << "Successful insertions: " << successfulOps << "/" 
                 << testKeys.size() << std::endl;

        // Searches
        std::cout << "\nPerforming searches..." << std::endl;
        successfulOps = 0;
        for (const auto& key : testKeys) {
            if (ht.search(key)) {
                successfulOps++;
            }
        }
        printSubTestResult("Searches completed", true);
        std::cout << "Successful searches: " << successfulOps << "/" 
                 << testKeys.size() << std::endl;

        // Deletions
        std::cout << "\nPerforming deletions..." << std::endl;
        successfulOps = 0;
        for (size_t i = 0; i < testKeys.size()/2; ++i) {
            if (ht.remove(testKeys[i])) {
                successfulOps++;
            }
        }
        printSubTestResult("Deletions completed", true);
        std::cout << "Successful deletions: " << successfulOps << "/" 
                 << testKeys.size()/2 << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "\nTotal execution time: " << duration.count() << "ms" << std::endl;
    }

    static void runAllTests(T& hashTables, std::string type) 
    {
        std::cout << "\n=== Starting Comparative Hash Table Tests ===\n" << std::endl;

        // Run functional tests for each implementation
        std::cout << "\nTesting " << type << " Implementation" << "\n" << std::string(50, '=') << std::endl;
        testBasicOperations(hashTables, type);
        testCollisionHandling(hashTables, type);
        testDeletionAndReinsert(hashTables, type);
        testTableFull(hashTables, type);
        testEdgeCases(hashTables, type);
        
        // Generate test data for performance test
        std::vector<std::string> testKeys;
        for (int j = 0; j < 1000; ++j) {
            testKeys.push_back(generateRandomString(10));
        }
        
        runPerformanceTest(hashTables, type, testKeys);
        
        std::cout << "\n=== All tests completed ===\n" << std::endl;
    }
};

// Example usage:
/*
int testMain() {
    // Create instances of different hash table implementations
    HashTable* linearProbingHT = new HashTable(1000);
    HashTable* quadraticProbingHT = new HashTable(1000);
    HashTable* doubleHashingHT = new HashTable(1000);

    // Create vectors of hash tables and their types
    std::vector<HashTable*> hashTables = {
        linearProbingHT,
        quadraticProbingHT,
        doubleHashingHT
    };

    std::vector<HashTableType> types = {
        HashTableType::LINEAR_PROBING,
        HashTableType::QUADRATIC_PROBING,
        HashTableType::DOUBLE_HASHING
    };

    // Run tests
    HashTableTester<HashTable>::runAllTests(hashTables, types);

    // Cleanup
    for (auto ht : hashTables) {
        delete ht;
    }

    return 0;
}*/