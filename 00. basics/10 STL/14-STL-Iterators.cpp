/*
    Topic: STL - Iterators

    This file demonstrates:
    1. What iterators are
    2. How to use begin() and end()
    3. Iterator traversal
    4. Different iterator types via containers
    5. const_iterator
    6. reverse_iterator
    7. Common iterator rules

    Important:
    - Iterators are the bridge between containers and algorithms
    - Algorithms work ONLY with iterators
*/

#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

int main()
{

    /*
    ===============================
    1. Basic Iterator Usage (vector)
    ===============================
    */

    vector<int> v = {10, 20, 30, 40};

    // iterator declaration
    vector<int>::iterator it;

    cout << "Vector elements using iterator: ";

    // begin() points to first element
    // end() points ONE PAST the last element
    for (it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " "; // dereferencing iterator
    }
    cout << endl;

    /*
    Key points:
    - *it gives value
    - ++it moves iterator forward
    - end() is NOT last element
    */

    /*
    ===============================
    2. const_iterator
    ===============================
    */

    // const_iterator does not allow modification
    vector<int>::const_iterator cit;

    cout << "\nUsing const_iterator: ";
    for (cit = v.cbegin(); cit != v.cend(); ++cit)
    {
        cout << *cit << " ";
        // *cit = 100;  // ERROR: cannot modify using const_iterator
    }
    cout << endl;

    /*
    ===============================
    3. Reverse Iterator
    ===============================
    */

    // reverse_iterator traverses container in reverse order
    vector<int>::reverse_iterator rit;

    cout << "\nVector in reverse order: ";
    for (rit = v.rbegin(); rit != v.rend(); ++rit)
    {
        cout << *rit << " ";
    }
    cout << endl;

    /*
    rbegin() -> last element
    rend()   -> one before first element
    */

    /*
    ===============================
    4. Iterator with list
    ===============================
    */

    // list provides BIDIRECTIONAL iterators
    list<int> l = {1, 2, 3, 4};

    list<int>::iterator lit;

    cout << "\nList elements: ";
    for (lit = l.begin(); lit != l.end(); ++lit)
    {
        cout << *lit << " ";
    }
    cout << endl;

    /*
    Note:
    - list does NOT support random access
    - lit + 1 is INVALID
    */

    /*
    ===============================
    5. Iterator with set
    ===============================
    */

    // set iterators traverse in sorted order
    set<int> s = {40, 10, 30, 20};

    set<int>::iterator sit;

    cout << "\nSet elements (sorted): ";
    for (sit = s.begin(); sit != s.end(); ++sit)
    {
        cout << *sit << " ";
    }
    cout << endl;

    /*
    Important:
    - set iterators are read-only for keys
    - modifying *sit is NOT allowed
    */

    /*
    ===============================
    6. auto with Iterators
    ===============================
    */

    cout << "\nUsing auto keyword: ";
    for (auto it2 = v.begin(); it2 != v.end(); ++it2)
    {
        cout << *it2 << " ";
    }
    cout << endl;

    /*
    auto helps avoid long iterator type names
    */

    /*
    ===============================
    7. Iterator Categories (Conceptual)
    ===============================

    vector      -> Random Access Iterator
    deque       -> Random Access Iterator
    list        -> Bidirectional Iterator
    forward_list-> Forward Iterator
    set/map     -> Bidirectional Iterator
    unordered_* -> Forward Iterator

    Algorithms depend on iterator category.
    Example:
    - sort() needs Random Access Iterator
    - sort(list.begin(), list.end()) is INVALID
    */

    /*
    ===============================
    8. Common Iterator Rules
    ===============================

    - Do not dereference end()
    - Do not use invalidated iterators
    - Prefer iterators over index-based loops
    - Use const_iterator for read-only access
    */

    return 0;
}
