#include <bits/stdc++.h>
using namespace std;

// Node structure for singly linked list
struct Node {
    int data;
    Node* next;

    // constructor initializes node with value and next = NULL
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class Solution {
public:
    // Function to delete the tail (last node) of linked list
    Node* deleteTail(Node* head) {

        // Case 1: Empty list
        if (head == NULL) return NULL;

        // Case 2: Only one node in list
        if (head->next == NULL) {
            delete head;     // free memory
            return NULL;     // returning empty list
        }

        // Case 3: General case: Traverse to second last node
        Node* curr = head;
        while (curr->next->next != NULL) {
            curr = curr->next;   // move forward
        }

        // curr now points to second last node
        delete curr->next;       // delete last node
        curr->next = NULL;       // mark new tail

        return head;             // return updated list
    }
};

// Utility function to print linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Driver code
int main() {
    // Creating linked list: 1 -> 2 -> 3
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    Solution obj;

    cout << "Original List: ";
    printList(head);

    // Perform delete tail
    head = obj.deleteTail(head);

    cout << "After Deleting Tail: ";
    printList(head);

    return 0;
}
