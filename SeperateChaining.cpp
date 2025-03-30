#include<bits/stdc++.h>

using namespace std;

class HashTable {
private:
    vector<list<string>> table;
    int hashFunction(const string& word) {
        int hash = 0;
        for (char c : word) hash += c;
        return hash % table.size();
    }

public:
    HashTable(int size) : table(size) {}
    
    void insert(const string& word) {
        table[hashFunction(word)].push_back(word);
    }

    void display() {
        for (int i = 0; i < table.size(); i++) {
            cout << "Bucket " << i << ": ";
            for (const auto& word : table[i]) cout << word << " -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable hashTable(10);
    int choice;
    string word;
    
    while (true) {
        cout << "1. Add\n2. Display\n3. Exit\nYour choice: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Enter word: ";
            cin >> word;
            hashTable.insert(word);
        } else if (choice == 2) {
            hashTable.display();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
