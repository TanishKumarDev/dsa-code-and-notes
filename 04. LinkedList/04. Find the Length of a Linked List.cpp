#include <bits/stdc++.h>
using namespace std;

// Node class represents a single node in the linked list
class Node {
public:
    int data;     // value of the node
    Node* next;   // pointer to next node

    // Constructor initializes data and sets next = NULL
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// Class containing operations related to linked list
class Solution {
public:

    // Function to find the length of the linked list
    int lengthOfLinkedList(Node* head) {
        int count = 0;          // counter to count nodes
        Node* temp = head;      // start traversal from the head

        // Traverse entire list until temp becomes NULL
        while (temp != nullptr) {
            count++;            // count current node
            temp = temp->next;  // move to next node
        }

        return count;           // return total number of nodes
    }
};

int main() {
    // Create sample linked list: 10 -> 20 -> 30
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

    Solution obj;

    // Calculate and print length
    cout << "Length of Linked List: "
         << obj.lengthOfLinkedList(head) << endl;

    return 0;
}
