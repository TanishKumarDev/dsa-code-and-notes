#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : 

// Intuition:
// 1 to N tak har number check karo ki array me present hai ya nahi.
// Agar koi number missing mila -> wahi answer hai.

// Algo:
// 1. i = 1 to N iterate karo.
// 2. Har i ke liye array ko linear scan karo.
// 3. Agar i array me mil jaye -> next i par jao.
// 4. Agar i nahi milta -> missing number i hai.

// TC: O(N^2)  // Har number ke liye poora array traverse hota hai
// SC: O(1)

// Edge cases:
// 1. Missing number at beginning
// 2. Missing number at end
// 3. N = 1 case

int brute(vector<int>& arr, int N) {
    for (int i = 1; i <= N; i++) {

        bool found = false;    // Flag to check number present or not

        // Linear search
        for (int x : arr) {
            if (x == i) {
                found = true;
                break;
            }
        }

        // If number not found -> this is missing number
        if (!found) return i;
    }

    return -1;   // Ideally never reached
}

// 🔵 Approach 2 Better : Hashing

// Intuition:
// A simple boolean hash array banate hain size N+1 ka.
// Jo element array me mile, uska hash 1 kar dete hain.
// Fir hash check karke jiska 0 hai -> woh missing number hai.

// Algo:
// 1. Hash array of size N+1 initialise with 0.
// 2. Array ke elements ke index par hash[x] = 1 karo.
// 3. 1..N iterate karke jiska hash 0 ho -> woh missing number.

// TC: O(N)
// SC: O(N)

// Edge cases:
// 1. Missing number = 1
// 2. Missing number = N
// 3. All elements present except one

int hashing(vector<int>& arr, int N) {

    vector<int> hash(N+1, 0);   // initially all 0

    // Mark presence
    for (int x : arr)
        hash[x] = 1;

    // Identify missing
    for (int i = 1; i <= N; i++) {
        if (hash[i] == 0)
            return i;
    }

    return -1;  // Ideally not reached
}

// 🟢 Approach 3 Optimal: Summation

// Intuition:
// 1 + 2 + 3 + ... + N ka sum formula se nikal sakte hain.
// Fir array ka actual sum nikal kar difference le lo.
// Difference = missing number.

// Algo:
// expectedSum = N*(N+1)/2
// actualSum = sum(arr)
// answer = expectedSum - actualSum

// TC: O(N)
// SC: O(1)

// Edge cases:
// 1. Large N -> long long use karna zaroori hai
// 2. Missing at any position

int summation(vector<int>& arr, int N) {

    long long expected = (long long)N * (N + 1) / 2;

    long long actual = 0;
    for (int x : arr)
        actual += x;

    return expected - actual;
}

// 🟢 Approach 4 Optimal : XOR 

// Intuition:
// XOR ki properties:
// x ^ x = 0
// x ^ 0 = x
// XOR order-independent hota hai.

// 1..N tak XOR kar do -> xor1
// Array ke elements ka XOR kar do -> xor2
// Missing number = xor1 ^ xor2

// Algo:
// 1. xor1 = XOR of 1..N
// 2. xor2 = XOR of all array elements
// 3. XOR of both = missing number

// TC: O(N)
// SC: O(1)

// Edge cases:
// 1. Missing number = 1
// 2. Missing number = N
// 3. Works even when array shuffled

class Solution {
public:
    int missingNumber(vector<int>& arr) {

        int N = arr.size() + 1;   // Since one number missing

        int xor1 = 0, xor2 = 0;

        // XOR 1..N and arr together in one loop
        for (int i = 1; i <= N; i++) {

            xor1 ^= i;   // XOR of all numbers 1..N

            // arr indexing check
            if (i - 1 < (int)arr.size())
                xor2 ^= arr[i - 1];   // XOR of all array elements
        }

        return xor1 ^ xor2;
    }
};


int main() 
{
    // Sample Input
    // Array of size N-1 containing numbers from 1 to N with one missing
    vector<int> arr = {1, 2, 4, 5}; 
    int N = 5;   // Total numbers should be 1..N

    // ----------------------------------------------
    // Approach 1 : Brute Force
    // ----------------------------------------------
    int ans1 = brute(arr, N);
    cout << "Missing Number using Brute Force: " << ans1 << endl;


    // ----------------------------------------------
    // Approach 2 : Hashing
    // ----------------------------------------------
    int ans2 = hashing(arr, N);
    cout << "Missing Number using Hashing: " << ans2 << endl;


    // ----------------------------------------------
    // Approach 3 : Summation
    // ----------------------------------------------
    int ans3 = summation(arr, N);
    cout << "Missing Number using Summation: " << ans3 << endl;


    // ----------------------------------------------
    // Approach 4 : XOR
    // ----------------------------------------------
    Solution s;
    int ans4 = s.missingNumber(arr);
    cout << "Missing Number using XOR: " << ans4 << endl;


    return 0;
}

/*
# DRY RUN SECTION

We assume input array is of size N-1 (since one number is missing)
So if array size = n, actual N = n+1.


# Example 1

arr = [1, 2, 4, 5]
N = 5
Missing number = 3 (middle missing)

## Approach 1: Brute Force

Check i from 1..5

| i | Scan arr | Found? | Return?  |
| - | -------- | ------ | -------- |
| 1 | 1,2,4,5  | Yes    | continue |
| 2 | 1,2,4,5  | Yes    | continue |
| 3 | 1,2,4,5  | No     | return 3 |

Output = 3

---

## Approach 2: Hashing

hash = [0,0,0,0,0,0]
Index meaning: hash[i] tells if i exists.

Mark presence from arr:

arr = 1 → hash[1]=1
arr = 2 → hash[2]=1
arr = 4 → hash[4]=1
arr = 5 → hash[5]=1

Final hash = [0,1,1,0,1,1]

Check 1..5:

1 → present
2 → present
3 → NOT present → return 3

Output = 3

---

## Approach 3: Summation

expected = 5 * 6 / 2 = 15
actual = 1 + 2 + 4 + 5 = 12

missing = expected − actual = 15 − 12 = 3

Output = 3

---

## Approach 4: XOR

xor1 = XOR of 1..5
1 ^ 2 = 3
3 ^ 3 = 0
0 ^ 4 = 4
4 ^ 5 = 1
So xor1 = 1

xor2 = XOR of arr
1 ^ 2 = 3
3 ^ 4 = 7
7 ^ 5 = 2
So xor2 = 2

missing = xor1 ^ xor2 = 1 ^ 2 = 3

Output = 3

---

---

# Example 2

arr = [2, 3, 4, 5]
N = 5
Missing number = 1 (missing at beginning)

## Brute:

Check i=1
Scan: 2,3,4,5 → not found → return 1

Output = 1

## Hash:

Mark 2,3,4,5 → hash = [0,0,1,1,1,1]
Check 1..5 → hash[1] = 0 → return 1

Output = 1

## Summation:

expected = 15
actual = 2+3+4+5 = 14
missing = 15 − 14 = 1
Output = 1

## XOR:

xor1 = XOR 1..5 = 1
xor2 = 2^3^4^5 = 4
missing = 1 ^ 4 = 5?
Wait check carefully:

2 ^ 3 = 1
1 ^ 4 = 5
5 ^ 5 = 0

So xor2 = 0

missing = xor1 ^ xor2 = 1 ^ 0 = 1

Output = 1

---

---

# Example 3

arr = [1, 2, 3, 4]
N = 5
Missing number = 5 (missing at end)

## Brute:

i=1 found
i=2 found
i=3 found
i=4 found
i=5 → not found → return 5

## Hash:

hash after marking = [0,1,1,1,1,0]
Check 1..5 → hash[5] = 0 → return 5

## Summation:

expected = 15
actual = 1+2+3+4 = 10
missing = 15 − 10 = 5

## XOR:

xor1 (1..5) = 1
xor2 = 1^2^3^4 = 4
missing = xor1 ^ xor2
1 ^ 4 = 5

---

---

# Example 4: Edge Case

arr = [2]
N = 2
Missing number = 1

### Brute

Check i=1 → not found → return 1

### Hash

hash[2] = 1
hash = [0,0,1]
Check i=1 → hash[1]=0 → return 1

### Summation

expected = 3
actual = 2
missing = 1

### XOR

xor1 = 1^2 → 3
xor2 = 2
missing = 3^2 = 1

---

---

# Example 5: Edge Case

arr = [1]
N = 2
Missing = 2

All approaches → return 2

---
 
*/