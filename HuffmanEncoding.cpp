#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// A simple node for the Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Compare function for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // Smallest frequency comes first
    }
};

// Make Huffman codes
void makeCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = code;
    makeCodes(root->left, code + "0", codes);
    makeCodes(root->right, code + "1", codes);
}

// Read the Huffman code and turn it back into text
void decode(Node* root, string encoded) {
    Node* cur = root;
    for (char bit : encoded) {
        if (bit == '0') cur = cur->left;
        else cur = cur->right;
        
        if (!cur->left && !cur->right) {
            cout << cur->ch;
            cur = root; // Go back to start
        }
    }
    cout << endl;
}

// Huffman encoding function
void huffman(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& f : freq) pq.push(new Node(f.first, f.second));

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();
    unordered_map<char, string> codes;
    makeCodes(root, "", codes);

    string encoded = "";
    for (char ch : text) encoded += codes[ch];

    cout << "\nHuffman Codes:\n";
    for (auto& c : codes) cout << c.first << ": " << c.second << endl;

    cout << "\nEncoded String:\n" << encoded << endl;

    cout << "\nDecoded String:\n";
    decode(root, encoded);
}

int main() {
    string text;
    int choice;

    while (true) {
        cout << "\nMENU:\n";
        cout << "1. Enter text\n";
        cout << "2. Encode and Decode\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore leftover newline in input buffer

        if (choice == 1) {
            cout << "Enter text: ";
            getline(cin, text);
        } 
        else if (choice == 2) {
            if (text.empty()) {
                cout << "No text entered! Please enter text first.\n";
            } else {
                huffman(text);
            }
        } 
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
