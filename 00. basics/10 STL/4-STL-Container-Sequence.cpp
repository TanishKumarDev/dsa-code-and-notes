/*
    Topic: STL - Sequence Containers

    Containers covered:
    1. array
    2. vector
    3. deque
    4. list
    5. forward_list

    Purpose:
    - Demonstrate basic usage of each sequence container
    - Show common operations
    - Explain behavior via comments
*/

#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

using namespace std;

int main()
{

    /*
    ===============================
    1. std::array (Fixed Size)
    ===============================
    */

    // std::array is a wrapper over C-style array
    // Size must be known at compile time
    array<int, 5> arr = {10, 20, 30, 40, 50};

    cout << "array elements: ";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Random access is allowed
    cout << "First element: " << arr.front() << endl;
    cout << "Last element: " << arr.back() << endl;

    /*
    ===============================
    2. std::vector (Dynamic Array)
    ===============================
    */

    // vector grows dynamically
    vector<int> v;

    // push_back adds element at the end
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "\nvector elements: ";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    // Random access is fast (O(1))
    cout << "v[1] = " << v[1] << endl;

    // pop_back removes last element
    v.pop_back();

    cout << "After pop_back: ";
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    /*
    ===============================
    3. std::deque (Double Ended Queue)
    ===============================
    */

    // deque allows fast insertion/removal at both ends
    deque<int> dq;

    dq.push_back(20);  // insert at back
    dq.push_front(10); // insert at front
    dq.push_back(30);

    cout << "\ndeque elements: ";
    for (int x : dq)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Front element: " << dq.front() << endl;
    cout << "Back element: " << dq.back() << endl;

    // Removing elements
    dq.pop_front();
    dq.pop_back();

    cout << "After pop_front & pop_back: ";
    for (int x : dq)
    {
        cout << x << " ";
    }
    cout << endl;

    /*
    ===============================
    4. std::list (Doubly Linked List)
    ===============================
    */

    // list allows fast insert/delete anywhere
    // No random access (no index access)
    list<int> l;

    l.push_back(20);
    l.push_front(10);
    l.push_back(30);

    cout << "\nlist elements: ";
    for (int x : l)
    {
        cout << x << " ";
    }
    cout << endl;

    // Inserting in middle using iterator
    auto it = l.begin();
    ++it; // move iterator to second position
    l.insert(it, 15);

    cout << "After inserting 15: ";
    for (int x : l)
    {
        cout << x << " ";
    }
    cout << endl;

    // Removing an element
    l.remove(20);

    cout << "After removing 20: ";
    for (int x : l)
    {
        cout << x << " ";
    }
    cout << endl;

    /*
    ===============================
    5. std::forward_list (Singly Linked List)
    ===============================
    */

    // forward_list supports only forward traversal
    // More memory efficient than list
    forward_list<int> fl;

    // Only push_front is available
    fl.push_front(30);
    fl.push_front(20);
    fl.push_front(10);

    cout << "\nforward_list elements: ";
    for (int x : fl)
    {
        cout << x << " ";
    }
    cout << endl;

    // Insert after a position
    auto fit = fl.begin();
    fl.insert_after(fit, 15);

    cout << "After insert_after: ";
    for (int x : fl)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
