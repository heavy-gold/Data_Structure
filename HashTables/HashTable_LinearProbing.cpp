#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "common/common_utils.h"

using namespace std;

/// @brief structure that holds name and address of a person
struct node
{
    string name;    // represent key in hash table
    string address; // represent value in hash table
};

/// @brief Hash table to store name and address as a key-value
struct HashTable
{
private:
    int BUCKET; // BUCKET size that contains fixed number of elements
    int NumOfElementInserted;   // to track number of element inserted
    vector<node> hashPair;  // vector that holds node hashPair.
    int HashFunction(string key);  // Hash function that counts hash code.
    void InsertElementToHashTable(int hashCode, string name, string address);
    void DeleteElementFromHashTable(int hashCode);  // Private function that just delete the element
    int GetIntegerOfEmptyIndex(int hashCode); // Function to get empty index from provided hash value.

public :    
    HashTable(int hashBucket)
    {
        this->BUCKET = hashBucket;
        hashPair.resize(BUCKET);
        NumOfElementInserted = 0;
    }

    bool insert(string key, string value);
    bool search(string key);
    bool remove(string key);
    void display();
    int searchAndGetIndex(string key);
};

/// @brief HashFunction that generates a hash value provided key.
/// @param key String
/// @return integer indicating hash code of passed key.
int HashTable::HashFunction(string key)
{
    int strLen = 0;
    strLen = key.length();
    return strLen%BUCKET;
}

bool HashTable::insert(string name, string address)
{
    int hashCode;
    int indexToInsertElement;
    if(NumOfElementInserted == BUCKET)
    {
        cout << "[ERROR] : No space available to insert an element in hash table\n.";
        return false;
    }

    // check if user already exist in the has table or not
    indexToInsertElement = searchAndGetIndex(name);
    if(indexToInsertElement != -1)
    {
        InsertElementToHashTable(indexToInsertElement, name, address);
        cout << "[INFO] : Address for name : " << name << " updated in the hash table.";
        return true;
    }

    // calculate hash code where an element can be inserted.
    hashCode = HashFunction(name);

    indexToInsertElement = GetIntegerOfEmptyIndex(hashCode);

    if(indexToInsertElement != -1)
    {
        InsertElementToHashTable(indexToInsertElement, name, address);
        cout << "[INFO] : Name : " << name << " is added in the hash table.";
        return true;
    }
    else
    {
        // The below code should not work. But if we are here, means we have a bug in our algorithm.
        cout << "[ERROR] : No element is inserted and algorithm seems to have a bug\n";
        return false;
    }
}

bool HashTable::remove(string name)
{
    // To store index at which provided name exists in the hash table.
    int nameIndex;
    nameIndex = searchAndGetIndex(name);


    if(nameIndex < 0 || nameIndex >= BUCKET)
    {
        cout << "[INFO] : Index value: " << nameIndex << " out of bound. Failed to remove user";
        return false;
    }
    else
    {
        // delete element.
        DeleteElementFromHashTable(nameIndex);
        if(HashFunction(name) == nameIndex)
        {
            cout << "[INFO] : Data for '" << name << "' is deleted from hash table without any conflict.\n";
        }
        else
        {
            cout << "[INFO] : Data for: '" << name << "' is deleted from hash table with conflict - solved.\n";
        }
        return true;
    }
}

void HashTable::display()
{
    for(int loopCount = 0; loopCount < BUCKET; loopCount++)
    {
        cout << "[Bucket : " << loopCount << "] ";
        if(hashPair[loopCount].name.empty())
        {
            cout << " --> [EMPTY]\n";
        }
        else
        {
            cout << " Name --> " << hashPair[loopCount].name << "; Address --> " << hashPair[loopCount].address << endl;
        }
    }
}

bool HashTable::search(string name)
{
    if(searchAndGetIndex(name) == -1)
    {
        return false;
    }
    return true;
}

int HashTable::searchAndGetIndex(string name)
{
    int loopCount;
    int hashCode = HashFunction(name);

    loopCount = hashCode;
    do
    {
        if(hashPair[loopCount].name == name)
        {
            cout << "[INFO] : Name '" << name << "' exists in the hash table.\n";
            return loopCount; 
        }
        loopCount = (loopCount + 1)%BUCKET;
    } while (loopCount != hashCode);

    // Once we are out from the loop, it simply means no such name exist in the hash table.
    cout << "[INFO] : Name '" << name << "' does not exist in the hash table\n";
    return -1;
}

int HashTable::GetIntegerOfEmptyIndex(int hashValue)
{
    int emptyHashIndex = hashValue;
    do
    {
        if(hashPair[emptyHashIndex].name.empty())
        {
            return emptyHashIndex; 
        }
        emptyHashIndex = (emptyHashIndex + 1)%BUCKET;
    } while (emptyHashIndex != hashValue);

    // Indicating no empty index present.
    return -1;
}

void HashTable::InsertElementToHashTable(int hashCode, string name, string address)
{
    hashPair[hashCode].name = name;
    hashPair[hashCode].address = address;
    NumOfElementInserted = NumOfElementInserted + 1;
}

void HashTable::DeleteElementFromHashTable(int hashCode)
{
    hashPair[hashCode].name.clear();
    hashPair[hashCode].address.clear();
    NumOfElementInserted = NumOfElementInserted - 1;
}

int main()
{
    int choice;
    int bucketSize = -1;
    string userName;
    string address;
    using namespace utils;

    cout << "\n Hash Table demo with linear probing conflict resolve algorithm";
    cout << "\n Enter BUCKET size for hash table. Should be between 5 to 5000.\n";
    getIntegerInput(bucketSize);
    
    if(bucketSize < 5 || bucketSize > 5000)
    {
        cout << "Failed to init Hash table. Size must be in the range of [5,5000]";
        return -1;
    }

    HashTable demoHashTable = HashTable(bucketSize);

    while(1)
    {
        cout << "\n\nHash Table Operations\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n";
        getIntegerInput(choice);

        switch (choice)
        {
        case 1:
            cout << "Enter name : \n";
            getline(cin, userName);
            cout << "Enter address : \n";
            getline(cin, address);
            demoHashTable.insert(userName, address);
            break;

        case 2:
            cout << "Enter name to delete data : \n";
            getline(cin, userName);
            if(demoHashTable.remove(userName))
            {
                cout << "Data deleted successfully.\n";
            }
            else
            {
                cout << "Data not found.\n";
            }
            break;
                
        case 3:
            cout << "Enter name to look into table\n";
            getline(cin, userName);
            if(demoHashTable.search(userName))
            {
                cout << "Data found.\n";
            }
            else
            {
                cout << "Data not found.\n";
            }
            break;
        
        case 4:
            demoHashTable.display();
            break;

        case 5:
            cout << "Exiting from Hash Table Demo.\n";
            return 0;

        default:
            cout << "Please select valid option.\n";
            break;
        }
    }
}
