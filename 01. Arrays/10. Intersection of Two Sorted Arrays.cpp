#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : Using Hash Set
// Intuition:
// Pehle array ke saare elements ko ek hash set me store kar do.
// Fir second array ko traverse karo.
// Jo element set me mil jaye, usse result me daal do aur set se erase kar do.
// Isse duplicates avoid ho jate hain (intersection me ek hi baar aayega).

// Algo:
// 1. unordered_set banao aur usme array 'a' ke sab values daalo.
// 2. array 'b' ko traverse karo.
// 3. Agar element set me present ho -> result me push karo + set se erase karo.
// 4. Final result return karo.

// TC: O(n + m) average case (unordered_set operations O(1))
// SC: O(n) for the hash set

// Edge cases:
// 1. arrays empty ho sakte hain
// 2. repeated elements intersection me ek hi baar aane chahiye
// 3. order matter nahi karta (set does not preserve order)

vector<int> intersectionWithSet(vector<int>& a, vector<int>& b) {

    unordered_set<int> s(a.begin(), a.end());   // Set to store elements of first array
    vector<int> res;                            // Final intersection array

    // Check each element of array b
    for (int x : b) {

        // Agar x set me hai matlab common element hai
        if (s.count(x)) {
            res.push_back(x);  // Add to result
            s.erase(x);        // Erase to avoid duplicates
        }
    }

    return res;  // Return intersection
}

// 🔵 Approach 2 Better : Using Two Pointers on Sorted Arrays

// Intuition:
// Dono arrays sorted hain. Two pointers i, j ka use karke dono ko saath traverse karte hain.
// Agar arr1[i] < arr2[j], to arr1 wala chhota hai, usse badhao.
// Agar arr1[i] > arr2[j], to arr2 wala chhota hai, usse badhao.
// Agar arr1[i] == arr2[j], matlab common element mil gaya.
// Duplicate avoid karne ke liye result ka last element check karte hain.

// Algo:
// 1. i = 0, j = 0 start karo.
// 2. Jab tak dono pointers array ke andar hain:
//        - arr1[i] < arr2[j]  -> i++
//        - arr1[i] > arr2[j]  -> j++
//        - dono equal -> result me push + i++ + j++
// 3. Final result return.

// TC: O(n + m)
// SC: O(1) extra (except output vector)

// Edge cases:
// 1. Arrays empty ho sakte hain
// 2. Already sorted arrays required (nahi to pehle sort karna padega)
// 3. Duplicate elements intersection me ek hi baar aane chahiye
// 4. If result empty, just return empty vector

vector<int> findIntersection(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size(), m = arr2.size();
    int i = 0, j = 0;
    vector<int> res;    // Stores final intersection

    // Traverse both arrays
    while (i < n && j < m) {

        // Case 1: arr1 ka element chhota hai
        if (arr1[i] < arr2[j]) {
            i++;
        }

        // Case 2: arr2 ka element chhota hai
        else if (arr1[i] > arr2[j]) {
            j++;
        }

        // Case 3: equal elements found (intersection)
        else {

            // Duplicate avoid
            if (res.empty() || res.back() != arr1[i]) {
                res.push_back(arr1[i]);
            }

            i++;
            j++;
        }
    }

    return res;
}

// 🟢 Approach 3 Optimal: 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :

int main()
{
    // Example input arrays
    // Note: Approach 2 requires sorted arrays. Dono arrays sorted rakhe gaye hain.
    vector<int> arr1 = {1, 2, 2, 3, 4, 5};
    vector<int> arr2 = {2, 2, 3, 5, 7};

    // ----------------------------------------------------------
    // Approach 1 : Using Hash Set
    // ----------------------------------------------------------
    vector<int> ans1 = intersectionWithSet(arr1, arr2);

    cout << "Intersection using Hash Set (Brute Force): ";
    for (int x : ans1)
        cout << x << " ";
    cout << endl;


    // ----------------------------------------------------------
    // Approach 2 : Using Two Pointers on Sorted Arrays
    // ----------------------------------------------------------
    vector<int> ans2 = findIntersection(arr1, arr2);

    cout << "Intersection using Two Pointers (Better): ";
    for (int x : ans2)
        cout << x << " ";
    cout << endl;


    return 0;
}
