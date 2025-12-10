#include <bits/stdc++.h>
using namespace std;

// Node structure for singly linked list
struct Node {
    int data;
    Node* next;

    // Constructor initializes node with value and next = NULL
    Node(int val) : data(val), next(NULL) {}
};

class Solution {
public:
    // Function to search for a value in the linked list
    bool searchValue(Node* head, int key) {
        Node* current = head;  // start traversal from head

        // Traverse until end of the list
        while (current != NULL) {
            // Check if current node contains the key
            if (current->data == key) {
                return true;  // value found
            }
            current = current->next;  // move to next node
        }

        // After complete traversal, value not found
        return false;
    }
};

// Driver code
int main() {
    // Creating linked list: 10 -> 20 -> 30
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

    Solution obj;

    // Search for a value
    int val = 20;
    bool found = obj.searchValue(head, val);

    if (found) cout << "Found\n";
    else cout << "Not Found\n";

    return 0;
}
