/*
    Topic: STL - Unordered Containers

    Containers covered:
    1. unordered_set
    2. unordered_multiset
    3. unordered_map
    4. unordered_multimap

    Key properties:
    - Implemented using hash tables
    - No sorted order
    - Average case O(1) operations
    - Worst case O(n) due to collisions
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main()
{

    /*
    ===============================
    1. std::unordered_set
    ===============================
    */

    // unordered_set stores UNIQUE values
    // Order of elements is NOT guaranteed
    unordered_set<int> us;

    us.insert(10);
    us.insert(5);
    us.insert(20);
    us.insert(10); // duplicate, ignored

    cout << "unordered_set elements: ";
    for (int x : us)
    {
        cout << x << " ";
    }
    cout << endl;

    // find() returns iterator to element or end()
    if (us.find(5) != us.end())
    {
        cout << "5 found in unordered_set" << endl;
    }

    // erase element
    us.erase(10);

    cout << "unordered_set after erase: ";
    for (int x : us)
    {
        cout << x << " ";
    }
    cout << endl;

    /*
    ===============================
    2. std::unordered_multiset
    ===============================
    */

    // unordered_multiset allows DUPLICATE values
    unordered_multiset<int> ums;

    ums.insert(10);
    ums.insert(10);
    ums.insert(5);
    ums.insert(20);

    cout << "\nunordered_multiset elements: ";
    for (int x : ums)
    {
        cout << x << " ";
    }
    cout << endl;

    // count() gives frequency of key
    cout << "count of 10: " << ums.count(10) << endl;

    /*
    ===============================
    3. std::unordered_map
    ===============================
    */

    // unordered_map stores key-value pairs
    // Keys are UNIQUE
    // No ordering of keys
    unordered_map<int, string> ump;

    ump[1] = "One";
    ump[3] = "Three";
    ump[2] = "Two";

    cout << "\nunordered_map elements:" << endl;
    for (auto p : ump)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    Important behavior:
    - operator[] inserts key if it does not exist
    */
    ump[4]; // creates key 4 with empty string value

    cout << "unordered_map size after ump[4]: " << ump.size() << endl;

    // Safer lookup using find()
    if (ump.find(2) != ump.end())
    {
        cout << "Key 2 exists in unordered_map" << endl;
    }

    // erase by key
    ump.erase(1);

    cout << "unordered_map after erase:" << endl;
    for (auto p : ump)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    ===============================
    4. std::unordered_multimap
    ===============================
    */

    // unordered_multimap allows DUPLICATE keys
    unordered_multimap<int, string> umm;

    umm.insert({1, "A"});
    umm.insert({1, "B"});
    umm.insert({2, "C"});

    cout << "\nunordered_multimap elements:" << endl;
    for (auto p : umm)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    Accessing all values for a given key
    using equal_range()
    */
    auto range = umm.equal_range(1);

    cout << "Values for key 1:" << endl;
    for (auto it = range.first; it != range.second; ++it)
    {
        cout << it->second << endl;
    }

    /*
    ===============================
    Complexity Summary (Average Case)
    ===============================
    insert  -> O(1)
    erase   -> O(1)
    find    -> O(1)

    Worst Case:
    All operations -> O(n) due to hash collisions
    */

    return 0;
}
