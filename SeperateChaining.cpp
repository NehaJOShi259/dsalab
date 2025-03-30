#include<bits/stdc++.h>

using namespace std;

class HashTable {
private:
    vector<list<string>> table;

    int hashFunction(const string& word) {
        int hash = 0;
        for (char c : word) {
            hash += c;
        }
        return hash % table.size();
    }

public:
    HashTable(int size) : table(size) {}

    void insert(const string& word) {
        table[hashFunction(word)].push_back(word);
    }

    void display() {
        for (int i = 0; i < table.size(); ++i) {
            cout << "Bucket " << i << ": ";
            for (const string& word : table[i]) {
                cout << word << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

int main() {
    HashTable hashTable(10);
    int choice;
    string key;

    while (true) {
        cout << "1. Add\n2. Display\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter element: ";
            cin >> key;
            hashTable.insert(key);
        } else if (choice == 2) {
            hashTable.display();
        } else {
            break;
        }
    }
    return 0;
}
