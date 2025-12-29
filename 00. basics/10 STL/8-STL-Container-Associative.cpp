/*
    Topic: STL - Associative Containers
    
    Containers covered:
    1. set
    2. multiset
    3. map
    4. multimap

    Key properties of associative containers:
    - Automatically sorted
    - Implemented using self-balancing BST (Red-Black Tree)
    - Operations like insert, erase, find run in O(log n)
*/

#include <iostream>
#include <set>
#include <map>

using namespace std;

int main()
{

    /*
    ===============================
    1. std::set
    ===============================
    */

    // set stores UNIQUE elements
    // Elements are stored in sorted order
    set<int> s;

    s.insert(10);
    s.insert(5);
    s.insert(20);
    s.insert(10); // duplicate, ignored

    cout << "set elements: ";
    for (int x : s)
    {
        cout << x << " ";
    }
    cout << endl;

    // find() returns iterator to element or end()
    if (s.find(5) != s.end())
    {
        cout << "5 found in set" << endl;
    }

    // erase element
    s.erase(10);

    cout << "set after erase: ";
    for (int x : s)
    {
        cout << x << " ";
    }
    cout << endl;

    /*
    ===============================
    2. std::multiset
    ===============================
    */

    // multiset allows DUPLICATE elements
    // Still maintains sorted order
    multiset<int> ms;

    ms.insert(10);
    ms.insert(10);
    ms.insert(5);
    ms.insert(20);

    cout << "\nmultiset elements: ";
    for (int x : ms)
    {
        cout << x << " ";
    }
    cout << endl;

    // count() returns number of occurrences
    cout << "count of 10: " << ms.count(10) << endl;

    /*
    ===============================
    3. std::map
    ===============================
    */

    // map stores key-value pairs
    // Keys are UNIQUE and sorted
    map<int, string> mp;

    mp[3] = "Three";
    mp[1] = "One";
    mp[2] = "Two";

    cout << "\nmap elements (key -> value):" << endl;
    for (auto p : mp)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    Important behavior:
    - mp[key] creates the key if it does not exist
    */
    mp[4]; // key 4 inserted with empty value

    cout << "map size after mp[4]: " << mp.size() << endl;

    // safer lookup using find()
    if (mp.find(2) != mp.end())
    {
        cout << "Key 2 exists in map" << endl;
    }

    // erase by key
    mp.erase(1);

    cout << "map after erase:" << endl;
    for (auto p : mp)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    ===============================
    4. std::multimap
    ===============================
    */

    // multimap allows DUPLICATE keys
    multimap<int, string> mm;

    mm.insert({1, "A"});
    mm.insert({1, "B"});
    mm.insert({2, "C"});

    cout << "\nmultimap elements:" << endl;
    for (auto p : mm)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    /*
    Accessing all values of a key using equal_range
    */
    auto range = mm.equal_range(1);

    cout << "Values for key 1:" << endl;
    for (auto it = range.first; it != range.second; ++it)
    {
        cout << it->second << endl;
    }

    /*
    ===============================
    Common Complexity (All Associative Containers)
    ===============================
    insert  -> O(log n)
    erase   -> O(log n)
    find    -> O(log n)
    */

    return 0;
}
