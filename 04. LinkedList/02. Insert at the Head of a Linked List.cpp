#include <bits/stdc++.h>
using namespace std;

// ===============================================
// Node represents a single element of a Linked List
// Each node contains:
//    1. data  -> value stored
//    2. next  -> pointer to next node
// ===============================================
class Node {
public:
    int data;      // stores the value of the node
    Node* next;    // stores the address of the next node

    // Constructor: creates a node with given data + next pointer
    Node(int data1, Node* next1) {
        data = data1;   // assign value
        next = next1;   // assign next pointer
    }

    // Constructor: creates a node with given data and next = NULL
    Node(int data1) {
        data = data1;       // assign value
        next = nullptr;     // next pointer is null initially
    }
};

// ===============================================
// Solution class holds linked list operations
// ===============================================
class Solution {
public:

    // -------------------------------------------
    // insertAtHead:
    // Inserts a new node before the current head
    // Steps:
    //  1. Create a new node
    //  2. Set newNode->next = head
    //  3. Return newNode as the updated head
    // Time Complexity: O(1)
    // -------------------------------------------
    Node* insertAtHead(Node* head, int newData) {
        Node* newNode = new Node(newData, head); // newNode->next = head
        return newNode; // return new node as new head
    }

    // -------------------------------------------
    // printList:
    // Prints linked list from head to NULL
    // -------------------------------------------
    void printList(Node* head) {
        Node* temp = head;  // start from head
        while (temp != nullptr) {   // iterate until end of list
            cout << temp->data << " "; // print current node value
            temp = temp->next;         // move to next node
        }
        cout << endl;
    }
};

int main() {
    Solution sol;

    // -------------------------------------------
    // Creating initial Linked List: 2 -> 3
    // Step 1: Create node with value 2
    // Step 2: Create node with value 3 and link it
    // -------------------------------------------
    Node* head = new Node(2);
    head->next = new Node(3);

    cout << "Original List: ";
    sol.printList(head);

    // -------------------------------------------
    // Insert 1 at head
    // Updated List: 1 -> 2 -> 3
    // -------------------------------------------
    head = sol.insertAtHead(head, 1);

    cout << "After Insertion at Head: ";
    sol.printList(head);

    return 0;
}
