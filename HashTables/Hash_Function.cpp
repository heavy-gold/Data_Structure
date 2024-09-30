#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node
{
    string name;
    string address;
    struct node *next;
};

struct HashTable
{
    int BUCKET;
    vector<node*> userData;

    HashTable(int bucketSize)
    {
        this->BUCKET = bucketSize;
        userData.resize(this->BUCKET);
    }

    int hashFunction(string key);
    bool IsKeyExistInHashTable(string key);
    void insert(string key, string value);
    void remove(string key);
    void display();
};

int HashTable::hashFunction(string key)
{
    int strLen = 0;
    strLen = key.length();
    return strLen%BUCKET;
}

bool HashTable::IsKeyExistInHashTable(string key)
{
    int hashCode = hashFunction(key);
    struct node *tablePtr = userData[hashCode];
    
    while(tablePtr!= nullptr)
    {
        if(tablePtr->name == key)
            return true;
        
        tablePtr = tablePtr->next;
    }

    return false;
}

/// @brief Function to insert/update user.
/// @param userName 
/// @param userAddress 
void HashTable::insert(string userName, string userAddress)
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
            return;
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
    }
    return;
}

void HashTable::remove(string userName)
{
    int hashCode = hashFunction(userName);
    struct node *tablePtr = userData[hashCode];
    struct node *prevNode = userData[hashCode];
    struct node *nodeToDel = nullptr;

    // check for null linked list
    if(tablePtr == nullptr)
    {
        cout << "[Info] : " << userName << " does not exists in table" << endl;
        return;
    }

    // if node that needed to be deleted is list head
    if(tablePtr->name == userName)
    {
        nodeToDel = tablePtr;
        userData[hashCode] = tablePtr->next;
        delete nodeToDel;
        cout << "[Info] : " << userName << " deleted from table" << endl;
        return;
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
            return;
        }
        prevNode = tablePtr;
        tablePtr = tablePtr->next;
    }
    cout << "[Info] : " << userName << " does not exists in table" << endl;
}

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