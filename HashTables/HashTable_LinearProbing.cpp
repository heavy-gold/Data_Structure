#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
    int loopCount;
    if(NumOfElementInserted == BUCKET)
    {
        cout << "[ERROR] : No space available to insert an element in hash table\n.";
        return false;
    }

    // calculate hash code.
    hashCode = HashFunction(name);

    // check if HashTable has element not inserted.
    if(hashPair[hashCode].name.empty())
    {
        // insert element.
        InsertElementToHashTable(hashCode, name, address);
        cout << "[INFO] : Name: " << name << " is inserted to hash table without any conflict.\n";
        return true;
    }

    // If element is already inserted, a conflict occurred in hash Table
    do
    {
        if(hashPair[loopCount].name.empty())
        {
            InsertElementToHashTable(loopCount, name, address);
            cout << "[INFO] : Name: " << name << " is inserted to hash table with conflict - solved.\n";
            return true;
        }
        loopCount = (loopCount+1)%BUCKET;
    } while (loopCount != hashCode);

    // The below code should not work. But if we are here, means we have a bug in our algorithm.
    cout << "[ERROR] : No element is inserted and algorithm seems to have a bug\n";
    return false;
}

bool HashTable::remove(string name)
{
    // To store index at which provided name exists in the hash table.
    int nameIndex;

    nameIndex = searchAndGetIndex(name);
    if(nameIndex == -1)
    {
        cout << "[INFO] : Failed to delete provided user from hash table\n";
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
            cout << " Name --> " << hashPair[loopCount].name << " Address --> " << hashPair[loopCount].address << endl;
        }
    }
}

bool HashTable::search(string name)
{
    int loopCount;
    int hashCode = HashFunction(name);

    loopCount = hashCode;
    do
    {
        if(hashPair[loopCount].name == name)
        {
            cout << "[INFO] : Name '" << name << "' exists in the hash table.\n";
            return true; 
        }
    } while (loopCount != hashCode);

    // Once we are out from the loop, it simply means no such name exist in the hash table.
    cout << "[INFO] : Name '" << name << "' does not exist in the hash table\n";
    return false;
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
    } while (loopCount != hashCode);

    // Once we are out from the loop, it simply means no such name exist in the hash table.
    cout << "[INFO] : Name '" << name << "' does not exist in the hash table\n";
    return -1;
}

void HashTable::InsertElementToHashTable(int hashCode, string name, string address)
{
    hashPair[hashCode].name = name;
    hashPair[hashCode].address = address;
    NumOfElementInserted++;
}

void HashTable::DeleteElementFromHashTable(int hashCode)
{
    hashPair[hashCode].name.clear();
    hashPair[hashCode].address.clear();
    NumOfElementInserted--;
}

bool getIntegerInput(int& value)
{
    if(cin >> value)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

int main()
{
    int choice;
    int bucketSize = -1;
    string userName;
    string address;

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