// File: linkedlist_operations.cpp
#include <bits/stdc++.h>
using namespace std;

// ===============================
// Node class represents a single
// node of the Linked List
// ===============================
class Node {
public:
    int data;     // value stored in node
    Node* next;   // pointer to next node

    // Constructor: initializes node with data; next = NULL
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// ===============================
// Function: Print Linked List
// Starting from head, traverse and print
// ===============================
void printList(Node* head) {
    Node* temp = head; // start from head
    while (temp != nullptr) { 
        cout << temp->data << " "; // print current node
        temp = temp->next;         // move to next node
    }
    cout << "\n";
}

// ===============================
// Insert at Beginning
// Time Complexity: O(1)
// ===============================
Node* insertAtBegin(Node* head, int value) {
    // Create a new node with the given value
    Node* newNode = new Node(value);

    // New node points to current head
    newNode->next = head;

    // Return new node as the new head
    return newNode;
}

// ===============================
// Insert at End
// Time Complexity: O(n)
// ===============================
Node* insertAtEnd(Node* head, int value) {
    // Create a new node with value
    Node* newNode = new Node(value);

    // Case 1: If list is empty, new node becomes head
    if (head == nullptr) return newNode;

    // Case 2: Traverse to the last node
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next; // move to next node
    }

    // Last node now points to new node
    temp->next = newNode;
    return head;
}

// ===============================
// Delete a Node by Value
// Deletes first occurrence of 'value'
// Time Complexity: O(n)
// ===============================
Node* deleteValue(Node* head, int value) {
    // Case 1: List is empty
    if (!head) return head;

    // Case 2: Value found at head
    if (head->data == value) {
        Node* temp = head;    // hold old head
        head = head->next;    // move head
        delete temp;          // free memory
        return head;
    }

    // Case 3: Search value in remaining list
    Node* curr = head;
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }

    // If found, delete the node
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = curr->next->next; // link skip deleted node
        delete temp;                   // free memory
    }

    return head;
}

// ===============================
// Main Program
// Demonstrates Linked List operations
// ===============================
int main() {

    // Manually create nodes 10, 20, 30
    Node* n1 = new Node(10);
    Node* n2 = new Node(20);
    Node* n3 = new Node(30);

    // Link nodes: n1 -> n2 -> n3 -> NULL
    n1->next = n2;
    n2->next = n3;
    n3->next = nullptr;

    // Head points to first node
    Node* head = n1;

    cout << "Initial Linked List: ";
    printList(head);

    // Insert at beginning
    head = insertAtBegin(head, 5);
    cout << "After insertAtBegin(5): ";
    printList(head);

    // Insert at end
    head = insertAtEnd(head, 100);
    cout << "After insertAtEnd(100): ";
    printList(head);

    // Delete a value
    head = deleteValue(head, 20);
    cout << "After deleteValue(20): ";
    printList(head);

    return 0;
}

// | Operation           | Time Complexity                                |
// | ------------------- | ---------------------------------------------- |
// | Traversal           | O(n)                                           |
// | Insert at Beginning | O(1)                                           |
// | Insert at End       | O(n)                                           |
// | Delete by Value     | O(n)                                           |
// | Space Used per Node | Data + Pointer (8 or 12 bytes based on system) |
