#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "common/common_utils.h"

using namespace std;

struct node
{
    string name;
    string address;
};

struct HashTable
{
private:
    int BUCKET;
    const float TableCutoff = 0.9;
    int numberOfElementInserted = 0;
    vector<node> hashPair;
    int HashFunction(string name);
    bool InsertElementToHashTable(int hashIndex, string name, string address);
    bool DeleteElementFromHashTable(int hashIndex);
    int getEmptyHashIndexFromHashValue(int hashVal);
    int getIndexOfInsertedElement(string name);
    bool ValidateTableOccupancy();
    bool ValidateIndexValue(int);
    int getNextIndexUsingHashAndCollisionCount(int, int);

public:
    HashTable(int tableSize)
    {
        BUCKET = tableSize;
        hashPair.resize(BUCKET);
    }

    bool insert(string name, string address);
    bool remove(string name);
    bool search(string name);
    void display();
};

int HashTable::HashFunction(string name)
{
    int nameLength = name.length();
    return (nameLength%BUCKET);
}

int HashTable::getNextIndexUsingHashAndCollisionCount(int hashVal, int collisionCount)
{
    return (int64_t)(hashVal + pow(collisionCount,2))%BUCKET;
}

int HashTable::getEmptyHashIndexFromHashValue(int hashVal)
{
    int emptyHashIndex = hashVal;
    int numOfCollision = 0;

    if(emptyHashIndex < 0 || emptyHashIndex > BUCKET)
    {
        cout << "[ERR]: Hash value" << hashVal << " is out of range." << endl;
        return -1;
    }

    while(1)
    {
        if(hashPair[emptyHashIndex].name.empty())
        {
            return emptyHashIndex;
        }
        else
        {
            numOfCollision = numOfCollision + 1;
            emptyHashIndex = getNextIndexUsingHashAndCollisionCount(emptyHashIndex, numOfCollision);
        }
    };
}

bool HashTable::ValidateTableOccupancy()
{
    if(numberOfElementInserted >= BUCKET*TableCutoff)
    {
        cout << "[INFO]: HashTable is almost full." << endl;
        return false;
    }
    return true;
}

bool HashTable::ValidateIndexValue(int indexValue)
{
    if(indexValue < 0 || indexValue >= BUCKET)
        return false;
    return true;
}

int HashTable::getIndexOfInsertedElement(string name)
{
    int indexOfInserted = -1;
    int hashVal = HashFunction(name);
    int numOfCollision = 0;

    if(!ValidateIndexValue(hashVal))
    {
        cout << "[ERR]: Calculated index value " << hashVal << " is out of range." << endl;
        return -1;
    }

    indexOfInserted = hashVal;
    do
    {
        if(hashPair[indexOfInserted].name == name)
        {
            return indexOfInserted;
        }
        numOfCollision = numOfCollision + 1;
        indexOfInserted = getNextIndexUsingHashAndCollisionCount(hashVal, numOfCollision);

    } while(!hashPair[indexOfInserted].name.empty());

    cout << "[INFO]: " << name <<": No such name found in hash table." << endl;
    return -1;
}

bool HashTable::insert(string name, string address)
{
    int hashValue = -1;
    int emptyIndex = -1;

    if(!ValidateTableOccupancy())
    {
        cout << "[ERR]: Cannot insert node to table" << endl;
        return false;
    }

    // get hash value
    hashValue = HashFunction(name);

    // get empty hash index using hash value
    emptyIndex = getEmptyHashIndexFromHashValue(hashValue);

    if(emptyIndex != -1)
    {
        return InsertElementToHashTable(emptyIndex, name, address);
    }
    else
    {
        cout << "[ERR]: Invalid empty index received. Failed to insert element : " << name << endl;
        return false;
    }
}

bool HashTable::remove(string name)
{
    int hashIndex = -1;
    hashIndex = getIndexOfInsertedElement(name);
    if(hashIndex == -1)
    {
        cout << "[ERR]: Cannot delete node from table. No such element found as name : " << name << endl;
        return false;
    }
    return DeleteElementFromHashTable(hashIndex);
}

bool HashTable::search(string name)
{
    if(getIndexOfInsertedElement(name))
        return true;
    return false;
}

void HashTable::display()
{
    cout << "[Info]: Hashtable has data as following ..." << endl;
    for(int iCount = 0; iCount < BUCKET; iCount++)
    {
        cout << "[" << iCount << "] : Name --> " << hashPair[iCount].name << "; Address --> " << hashPair[iCount].address << endl; 
    }
    return;
}

bool HashTable::InsertElementToHashTable(int hashIndex, string name, string address)
{
    if(!ValidateIndexValue(hashIndex))
    {
        cout << "[ERR]: Provided index is out of bound. Index value is : " << hashIndex << endl;
        return false;
    }

    hashPair[hashIndex].name = name;
    hashPair[hashIndex].address = address;
    numberOfElementInserted = numberOfElementInserted + 1;
    return true;
}

bool HashTable::DeleteElementFromHashTable(int hashIndex)
{
    if(!ValidateIndexValue(hashIndex))
    {
        cout << "[ERR]: Provided index is out of bound. Cannot perform delete operation. Index value is : " << hashIndex << endl;
        return false;
    }

    hashPair[hashIndex].name.clear();
    hashPair[hashIndex].address.clear();
    numberOfElementInserted = numberOfElementInserted - 1;
    return true;
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