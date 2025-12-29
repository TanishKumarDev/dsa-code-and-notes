/*
    Topic: STL - Algorithms

    This file demonstrates:
    1. Non-modifying algorithms
    2. Modifying algorithms
    3. Sorting algorithms
    4. Binary search family
    5. Numeric algorithms
    6. Min / Max utilities

    Important rule:
    - STL algorithms work on ITERATORS
    - They do NOT know about containers
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for accumulate
using namespace std;

int main()
{

    /*
    ===============================
    Initial Data
    ===============================
    */

    vector<int> v = {5, 2, 8, 1, 3};

    cout << "Initial vector: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    /*
    ===============================
    1. Non-Modifying Algorithms
    ===============================
    */

    // find(): searches for an element
    auto it = find(v.begin(), v.end(), 8);
    if (it != v.end())
    {
        cout << "8 found in vector" << endl;
    }

    // count(): counts occurrences
    cout << "Count of 2: " << count(v.begin(), v.end(), 2) << endl;

    /*
    ===============================
    2. Modifying Algorithms
    ===============================
    */

    // reverse(): reverses elements
    reverse(v.begin(), v.end());

    cout << "\nAfter reverse: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    // replace(): replaces old value with new value
    replace(v.begin(), v.end(), 3, 30);

    cout << "After replace 3 -> 30: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    /*
    ===============================
    3. Sorting Algorithms
    ===============================
    */

    // sort(): sorts the range
    // Requires random access iterators
    sort(v.begin(), v.end());

    cout << "\nAfter sort: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    /*
    ===============================
    4. Binary Search Algorithms
    ===============================
    IMPORTANT:
    - These algorithms REQUIRE sorted data
    ===============================
    */

    // binary_search(): returns true/false
    bool found = binary_search(v.begin(), v.end(), 5);
    cout << "Is 5 present? " << found << endl;

    // lower_bound(): first element >= key
    auto lb = lower_bound(v.begin(), v.end(), 5);
    cout << "lower_bound of 5: " << *lb << endl;

    // upper_bound(): first element > key
    auto ub = upper_bound(v.begin(), v.end(), 5);
    cout << "upper_bound of 5: " << *ub << endl;

    /*
    ===============================
    5. Numeric Algorithms
    ===============================
    */

    // accumulate(): sum of elements
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "\nSum of elements: " << sum << endl;

    /*
    ===============================
    6. Min / Max Algorithms
    ===============================
    */

    // min_element(): iterator to minimum element
    auto mn = min_element(v.begin(), v.end());

    // max_element(): iterator to maximum element
    auto mx = max_element(v.begin(), v.end());

    cout << "Minimum element: " << *mn << endl;
    cout << "Maximum element: " << *mx << endl;

    /*
    ===============================
    7. remove() Algorithm (Important Trap)
    ===============================
    */

    /*
        remove() does NOT erase elements.
        It shifts unwanted elements to the end
        and returns new logical end iterator.
    */

    vector<int> v2 = {1, 2, 3, 2, 4};

    cout << "\nBefore remove: ";
    for (int x : v2)
        cout << x << " ";
    cout << endl;

    auto newEnd = remove(v2.begin(), v2.end(), 2);

    // erase is required to actually remove elements
    v2.erase(newEnd, v2.end());

    cout << "After remove + erase: ";
    for (int x : v2)
        cout << x << " ";
    cout << endl;

    /*
    ===============================
    Complexity Summary
    ===============================
    find            -> O(n)
    sort            -> O(n log n)
    binary_search   -> O(log n)
    lower/upper     -> O(log n)
    accumulate      -> O(n)
    */

    return 0;
}
