/*
Program that implements Hash table data structure.
To avoid collision it uses separate chaining method.
*/

#include <iostream>
#include <vector>
#include <string>
#include "common/common_utils.h"

using namespace std;

/// @brief Structure to store name and address.
/// It also has a self referential node so that can be used as a linked list.
struct node
{
    string name;    // represent key in hash table
    string address; // represent value in hash table
    struct node *next;
};

/// @brief Structure that implements HashTable with separate chaining collision avoidance.
struct HashTable
{
private:
    int BUCKET;
    vector<node*> userData;
    int hashFunction(string key);

public:
    HashTable(int bucketSize)
    {
        this->BUCKET = bucketSize;
        userData.resize(this->BUCKET);
    }
    bool insert(string key, string value);
    bool remove(string key);
    bool search(string key);
    void display();
};

/// @brief HashFunction that generates a hash value provided key.
/// @param key String
/// @return integer indicating hash code of passed key.
int HashTable::hashFunction(string key)
{
    int strLen = 0;
    strLen = key.length();
    return strLen%BUCKET;
}

/// @brief Function to insert/update user.
/// @param userName 
/// @param userAddress 
bool HashTable::insert(string userName, string userAddress)
{
    int hashCode = hashFunction(userName);
    bool isNameExist = false;
    struct node *tablePtr = userData[hashCode];

    while(tablePtr != nullptr)
    {
        if(tablePtr->name == userName)
        {
            isNameExist = true;
            tablePtr->address = userAddress;
            cout << "[Warning] : User name has updated " << endl;
            return true;
        }
        tablePtr = tablePtr->next;
    }

    if(!isNameExist)
    {
        struct node *newNode = new struct node;
        newNode->name = userName;
        newNode->address = userAddress;
        newNode->next = userData[hashCode];
        userData[hashCode] = newNode;
        cout << "[Info] : User name has been added " << endl;
        return true;
    }
    return false;
}

/// @brief To remove userName from hashTable.
/// @param userName user name that was used to insert user.
bool HashTable::remove(string userName)
{
    int hashCode = hashFunction(userName);
    struct node *tablePtr = userData[hashCode];
    struct node *prevNode = userData[hashCode];
    struct node *nodeToDel = nullptr;

    // check for null linked list
    if(tablePtr == nullptr)
    {
        cout << "[Info] : " << userName << " does not exists in table" << endl;
        return false;
    }

    // if node that needed to be deleted is list head
    if(tablePtr->name == userName)
    {
        nodeToDel = tablePtr;
        userData[hashCode] = tablePtr->next;
        delete nodeToDel;
        cout << "[Info] : " << userName << " deleted from table" << endl;
        return true;
    }

    tablePtr = prevNode->next;
    // Traverse through list to find and delete node.
    while(tablePtr != nullptr)
    {
        if(tablePtr->name == userName)
        {
            nodeToDel = tablePtr;
            prevNode->next = tablePtr->next;
            delete nodeToDel;
            cout << "[Info] : " << userName << " deleted from table" << endl;
            return true;
        }
        prevNode = tablePtr;
        tablePtr = tablePtr->next;
    }
    cout << "[Info] : " << userName << " does not exists in table" << endl;
    return false;
}

/// @brief To display HashTable.
void HashTable::display()
{
    for(int currentBucket = 0; currentBucket < BUCKET; currentBucket++)
    {
        struct node* tablePtr = userData[currentBucket];
        cout << "Bucket : " << currentBucket << " ";
        while(tablePtr != nullptr)
        {
            cout << "--> Name: " << tablePtr->name << "; Address: " << tablePtr->address << " ";
            tablePtr = tablePtr->next;
        }
        cout << endl;
    }
}

bool HashTable::search(string key)
{
    int hashCode = hashFunction(key);
    struct node *tablePtr = userData[hashCode];

    // check for null linked list
    if(tablePtr == nullptr)
    {
        cout << "[Info] : " << key << " does not exists in table" << endl;
        return false;
    }

    // Traverse through list to find and delete node.
    while(tablePtr != nullptr)
    {
        if(tablePtr->name == key)
        {
            return true;
        }
        tablePtr = tablePtr->next;
    }
    return false;
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

/*
/// @brief To test hash table created as above.
/// @return 
int main()
{
    int userChoice = 0;
    int bucketSize = 0;
    string tempUserName;
    string tempUserAddr;
    string tempBuff;

    cout << "Initializing hash table. Enter bucket size between 10 to 100" << endl;
    cin >> bucketSize;
    if(bucketSize < 10 || bucketSize > 100)
    {
        cout << " Invalid bucket size. Must be in the range of [10,100]" << endl;
        return 0;
    }

    // Init Hash table
    HashTable hashTable(bucketSize);

    while(1)
    {

        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Remove\n";
        cout << "4. Exit from programm\n";
        cin >> userChoice;
        cin.sync();

        switch (userChoice)
        {
        case 1:
            cout << "Enter Name :";
            getline(cin, tempUserName);
            cout << "Enter Address:";
            getline(cin, tempUserAddr);
            hashTable.insert(tempUserName, tempUserAddr);
            break;
        case 2:
            cout << "[Begin]" << endl;
            hashTable.display();
            cout << "[End]" << endl;
            break;
        case 3:
            cout << "Enter Name to delete data : ";
            getline(cin, tempUserName);
            hashTable.remove(tempUserName);
            break;
        case 4:
            cout << "Exiting from programm " << endl;
            return 0;

        default:
            cout << "Invalid choice. Please choose a valid option." << endl;
            break;
        }
    }
}
*/