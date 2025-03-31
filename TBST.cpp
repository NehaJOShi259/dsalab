#include <iostream>
using namespace std;

// Node structure
class Node {
public:
    int key;
    Node *left, *right;
    bool leftThread, rightThread;

    Node(int val) {
        key = val;
        left = right = nullptr;
        leftThread = rightThread = true;
    }
};

// Threaded Binary Search Tree (TBST) Class
class TBST {
private:
    Node* root;

public:
    TBST() { root = nullptr; }

    // Insert a node
    void insert(int key) {
        Node* newNode = new Node(key);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* curr = root, *parent = nullptr;
        while (curr != nullptr) {
            parent = curr;
            if (key < curr->key) {
                if (curr->leftThread) break;
                curr = curr->left;
            } else if (key > curr->key) {
                if (curr->rightThread) break;
                curr = curr->right;
            } else {
                return; // Duplicate keys not allowed
            }
        }

        if (key < parent->key) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->left = newNode;
            parent->leftThread = false;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            parent->right = newNode;
            parent->rightThread = false;
        }
    }

    // Search a key
    bool search(int key) {
        Node* curr = root;
        while (curr != nullptr) {
            if (key < curr->key) {
                if (curr->leftThread) return false;
                curr = curr->left;
            } else if (key > curr->key) {
                if (curr->rightThread) return false;
                curr = curr->right;
            } else {
                return true;
            }
        }
        return false;
    }

    // In-order traversal
    void inorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node* curr = root;
        while (curr->leftThread == false) curr = curr->left;

        while (curr != nullptr) {
            cout << curr->key << " ";
            if (curr->rightThread)
                curr = curr->right;
            else {
                curr = curr->right;
                while (curr != nullptr && !curr->leftThread)
                    curr = curr->left;
            }
        }
        cout << endl;
    }
};

// Main function
int main() {
    TBST tree;
    int choice, val;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n2. Search\n3. Inorder Traversal\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;

            case 2:
                cout << "Enter value to search: ";
                cin >> val;
                if (tree.search(val))
                    cout << "Element found!\n";
                else
                    cout << "Element not found!\n";
                break;

            case 3:
                cout << "Inorder Traversal: ";
                tree.inorder();
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
