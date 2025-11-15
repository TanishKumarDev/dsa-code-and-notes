#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force :  Using Set
// Intuition:
// Set automatically unique elements rakhta hai aur sorted order me store karta hai.
// Dono arrays ke saare elements ko set me daal do. Duplicate hat jayenge.
// Fir set ko vector me convert karke return kar do.

// Algo:
// 1. Empty set declare karo.
// 2. Pehle array ke saare elements insert karo.
// 3. Dusre array ke saare elements insert karo.
// 4. Set ke elements ko vector me copy karke return kar do.

// TC: O((n + m) * log(n + m))  // Set insertion logN time leta hai
// SC: O(n + m)                // Set me sab unique elements store hote hain

// Edge cases:
// 1. Arrays empty ho sakte hain
// 2. Arrays already sorted ho ya unsorted, koi farak nahi padta
// 3. Duplicates automatically handle ho jate hain

vector<int> unionWithSet(vector<int>& a, vector<int>& b) {
    set<int> s;              // Set for unique + sorted elements

    // Insert all elements of first array
    for (int x : a)
        s.insert(x);
         // Insert all elements of second array
    for (int x : b)
        s.insert(x);

    // Convert set to vector for final output
    return vector<int>(s.begin(), s.end());
}


// 🔵 Approach 2 Better : Using Two Pointers on Sorted Arrays
// Intuition:
// Two sorted arrays ko ek saath traverse karo using two pointers.
// Jo element chhota hoga, usse union list me add kar do (agar duplicate na ho).
// Isse sorted union milta hai aur repeated elements avoid ho jate hain.

// Algo:
// 1. i aur j pointers start se begin karenge.
// 2. Jab tak dono arrays me elements bache hain:
//        - Jo element chhota ho, use push karo (if not duplicate), pointer move karo.
//        - Agar arr1[i] == arr2[j], ek hi baar push karo, aur dono pointers move karo.
// 3. Baad me jo bhi elements bache ho unhe push kar do (duplicate avoid karte hue).
// 4. Final vector return.

// TC: O(n + m) -> dono arrays ek hi pass me process hote hain.
// SC: O(n + m) -> worst case union me sab elements aa sakte hain.
// Edge cases:
// 1. arrays empty ho sakte hain
// 2. repeated elements already inside array
// 3. starting me unionArr empty hai so handle carefully

vector<int> findUnion(vector<int>& arr1, vector<int>& arr2) {

    int n = arr1.size(), m = arr2.size();
    int i = 0, j = 0;       // Two pointers for both arrays

    vector<int> unionArr;  // Final answer array

    // Step 1: Process both arrays until one ends
    while (i < n && j < m) {

        // Case 1: arr1[i] <= arr2[j]
        if (arr1[i] <= arr2[j]) {

            // Duplicate avoid: only add if vector empty OR last element different ho
            if (unionArr.empty() || unionArr.back() != arr1[i])
                unionArr.push_back(arr1[i]);

            i++; // Move pointer of arr1
        }

        // Case 2: arr2[j] < arr1[i]
        else {

            if (unionArr.empty() || unionArr.back() != arr2[j])
                unionArr.push_back(arr2[j]);

            j++; // Move pointer of arr2
        }
    }

    // Step 2: Agar arr1 me elements bache ho
    while (i < n) {

        // Last element check to avoid duplicate
        if (unionArr.back() != arr1[i])
            unionArr.push_back(arr1[i]);

        i++;
    }

    // Step 3: Agar arr2 me elements bache ho
    while (j < m) {

        if (unionArr.back() != arr2[j])
            unionArr.push_back(arr2[j]);

        j++;
    }

    return unionArr;  // Final union vector
}

// 🟢 Approach 3 Optimal: 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :

int main()
{
    // Sample input arrays
    // Note: Approach 2 requires sorted arrays, so both arrays are sorted
    vector<int> arr1 = {1, 2, 2, 3, 4};
    vector<int> arr2 = {2, 3, 5, 6};

    // Calling Approach 1 (Using Set)
    vector<int> ans1 = unionWithSet(arr1, arr2);

    // Printing result of Approach 1
    cout << "Union using Set (Brute Force): ";
    for (int x : ans1)
        cout << x << " ";
    cout << endl;


    // Calling Approach 2 (Two Pointer Method)
    vector<int> ans2 = findUnion(arr1, arr2);

    // Printing result of Approach 2
    cout << "Union using Two Pointers (Better): ";
    for (int x : ans2)
        cout << x << " ";
    cout << endl;

    return 0;
}
