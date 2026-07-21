#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* child[2];
    int count;

    TrieNode() {
        child[0] = nullptr;
        child[1] = nullptr;
        count = 0;
    }
};

class BinaryTrie {
private:
    TrieNode* root;

public:
    BinaryTrie() {
        root = new TrieNode();
    }

    void insert(int num) {
    TrieNode* current = root;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            if (current->child[bit] == nullptr) {
                current->child[bit] = new TrieNode();
            }
            current = current->child[bit];
            current->count++;
        }
    }

    bool search(int num) {
    TrieNode* current = root;

    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;

        if (current->child[bit] == nullptr) {
            return false;
        }

        current = current->child[bit];

        if (current->count == 0) {
            return false;
        }
    }

    return true;
    }

    void remove(int num) {
    if (!search(num))
        return;

    TrieNode* current = root;

    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        current = current->child[bit];
        current->count--;
    }
    }

    int kthSmallest(int k) {
    TrieNode* current = root;
    int answer = 0;

    for (int i = 31; i >= 0; i--) {
        int leftCount = 0;

        if (current->child[0] != nullptr)
            leftCount = current->child[0]->count;

        if (k <= leftCount) {
            current = current->child[0];
        } else {
            k -= leftCount;
            current = current->child[1];
            answer |= (1 << i);
        }
    }

    return answer;
    }

    int totalElements() {
    int left = (root->child[0] != nullptr) ? root->child[0]->count : 0;
    int right = (root->child[1] != nullptr) ? root->child[1]->count : 0;
    return left + right;
    }

    int kthLargest(int k) {
        return kthSmallest(totalElements() - k + 1);
    }
};

int main() {
    BinaryTrie trie;
    int choice, num, k;

    while (true) {
        cout << "\n===== Binary Trie Menu =====\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "4. Kth Smallest\n";
        cout << "5. Kth Largest\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number: ";
                cin >> num;
                trie.insert(num);
                cout << "Inserted successfully.\n";
                break;

            case 2:
                cout << "Enter number: ";
                cin >> num;
                cout << (trie.search(num) ? "Found\n" : "Not Found\n");
                break;

            case 3:
                cout << "Enter number: ";
                cin >> num;
                trie.remove(num);
                cout << "Removed successfully.\n";
                break;

            case 4:
                cout << "Enter k: ";
                cin >> k;
                cout << k << "th Smallest = " << trie.kthSmallest(k) << endl;
                break;

            case 5:
                cout << "Enter k: ";
                cin >> k;
                cout << k << "th Largest = " << trie.kthLargest(k) << endl;
                break;

            case 6:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}