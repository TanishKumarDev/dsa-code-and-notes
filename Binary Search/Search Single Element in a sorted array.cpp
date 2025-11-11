#include <bits/stdc++.h>
using namespace std;

// Problem : Search Single Element in a sorted array  
// Example : 
//   arr = {1,1,2,2,3,3,4,5,5,6,6} → return 4  
//   arr = {1,1,2}                 → return 2  
//   arr = {3,3,7,7,10,11,11}     → return 10  
//   arr = {5}                     → return 5  
// Constraint : 
//   1 ≤ n ≤ 10^5  
//   Every element appears **twice** except **one**  
//   Array is **sorted**  
//   Find the **single element**

// Approach 1 Brute Force : 
// Intuition :  
// Imagine a line of kids holding hands in pairs.  
// But **one kid is alone** — no partner.  
// You don’t know who.  
// So? Just walk through the line and check each kid.  
// If a kid’s partner is missing → that’s the single one!  
// Simple. But slow.

// Algo :  
// 1. Loop i from 0 to n-2 step 2  
//    → If arr[i] != arr[i+1] → return arr[i]  
// 2. If loop ends → single is at last → return arr[n-1]  

// TC : O(n) → worst case: single at end  
// SC : O(1)  

int bruteForce(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i += 2) {
        if (arr[i] != arr[i + 1]) {
            return arr[i];
        }
    }
    return arr[n - 1];  // last element is single
}

// Approach 2 Better : 
// Intuition :  
// **XOR is magic**!  
// → `a ^ a = 0`  
// → `a ^ 0 = a`  
// So:  
// → XOR all elements → all pairs cancel out → only single remains!  
// Like:  
// > 1^1 = 0, 2^2 = 0, 3^3 = 0, ..., 4^0 = 4  
// Fast. Clean. No extra space.

// Algo :  
// 1. ans = 0  
// 2. For each element → ans ^= arr[i]  
// 3. Return ans  

// TC : O(n) → still linear  
// SC : O(1)  

int betterXOR(vector<int>& arr) {
    int ans = 0;
    for (int num : arr) {
        ans ^= num;
    }
    return ans;
}

// Approach 3 Optimal: 
// Intuition :  
// Array is **sorted** + **pairs** → **pattern**!  
// → Before single element: pairs are **(even, odd)** index  
// → After single element: pairs are **(odd, even)** index  
// So:  
// → At any `mid`:  
//    → If `mid` is even and `arr[mid] == arr[mid+1]` → pair intact → **left half**  
//    → If `mid` is odd and `arr[mid] == arr[mid-1]` → pair intact → **left half**  
//    → Else → **right half** or **mid is single**  
// We **binary search** for the **disruption point**!

// Algo :  
// 1. Edge cases:  
//    → n == 1 → return arr[0]  
//    → arr[0] != arr[1] → return arr[0]  
//    → arr[n-1] != arr[n-2] → return arr[n-1]  
// 2. low = 1, high = n-2  
// 3. While low <= high:  
//    mid = low + (high-low)/2  
//    → If arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1] → return arr[mid]  
//    → If (mid even && arr[mid] == arr[mid+1]) or (mid odd && arr[mid] == arr[mid-1])  
//        → We are in **left half** → low = mid + 1  
//    → Else → **right half** → high = mid - 1  
// 4. Return -1 (won’t reach)

// TC : O(log n) → binary search  
// SC : O(1)  

// Edge Cases Handled:  
// → n = 1 → [5] → return 5  
// → Single at start → [4,1,1,2,2] → return 4  
// → Single at end → [1,1,2,2,3] → return 3  
// → Single in middle → [1,1,2,3,3,4,4] → return 2  

// Best Case  : O(1) → single at start/end  
// Avg Case   : O(log n)  
// Worst Case : O(log n) → single in middle  

int optimalBinarySearch(vector<int>& arr) {
    int n = arr.size();
    
    // Edge cases
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n-1] != arr[n-2]) return arr[n-1];
    
    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Found single element
        if (arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1]) {
            return arr[mid];
        }
        
        // We are in left half → eliminate left
        if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) ||
            (mid % 2 == 1 && arr[mid] == arr[mid - 1])) {
            low = mid + 1;
        }
        // We are in right half → eliminate right
        else {
            high = mid - 1;
        }
    }
    return -1;  // won't reach
}

int main() {
    vector<int> arr = {1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6};

    cout << "Brute Force     : " << bruteForce(arr) << endl;
    cout << "Better (XOR)    : " << betterXOR(arr) << endl;
    cout << "Optimal (BS)    : " << optimalBinarySearch(arr) << endl;

    return 0;
}
/*

## **Concept Recap**

We are finding **the single (non-duplicate) element** in a sorted array where **every other element appears exactly twice**.

### Key Observation:

Before the single element → pairs follow pattern `(even, odd)`
After the single element → pairs become `(odd, even)`

We’ll use **binary search** to find where this pattern breaks.

---

## **Array Setup**

```
arr = [1,1,2,2,3,3,4,5,5,6,6]
index: 0 1 2 3 4 5 6 7 8 9 10
n = 11
```

---

## **Step 1: Edge Cases**

```
n = 11 → not 1
arr[0] == arr[1] → 1 == 1 → OK
arr[n-1] == arr[n-2] → 6 == 6 → OK
→ none of edge cases matched → proceed to binary search
```

---

## **Step 2: Initialize**

```
low = 1
high = 9
```

(We skip first and last because edge cases already handled)

---

## **Step 3: Binary Search Loop**

### **Iteration 1**

```
mid = low + (high - low) / 2
    = 1 + (9 - 1)/2
    = 1 + 4
    = 5

arr[mid] = arr[5] = 3
arr[mid-1] = arr[4] = 3
arr[mid+1] = arr[6] = 4
```

**Check if arr[mid] is single:**

```
arr[mid] != arr[mid-1]? 3 != 3 → false
arr[mid] != arr[mid+1]? 3 != 4 → true
→ But both must be true → not single
```

**Now pattern check:**

```
mid = 5 (odd)
arr[mid] == arr[mid-1]? 3 == 3 → true
→ (odd index, pair intact) → we are in left half
→ Move right: low = mid + 1 = 6
```

```
low = 6
high = 9
```

---

### **Iteration 2**

```
mid = 6 + (9 - 6)/2 = 7
arr[mid] = arr[7] = 5
arr[mid-1] = arr[6] = 4
arr[mid+1] = arr[8] = 5
```

**Check single:**

```
arr[mid] != arr[mid-1]? 5 != 4 → true
arr[mid] != arr[mid+1]? 5 != 5 → false
→ not single
```

**Pattern check:**

```
mid = 7 (odd)
arr[mid] == arr[mid-1]? 5 == 4 → false
→ Not a proper pair → single must be on left side
→ Move left: high = mid - 1 = 6
```

```
low = 6
high = 6
```

---

### **Iteration 3**

```
mid = 6 + (6 - 6)/2 = 6
arr[mid] = arr[6] = 4
arr[mid-1] = arr[5] = 3
arr[mid+1] = arr[7] = 5
```

**Check single:**

```
arr[mid] != arr[mid-1]? 4 != 3 → true
arr[mid] != arr[mid+1]? 4 != 5 → true
→ Both true → FOUND single element
```

✅ **Return arr[mid] = 4**

---

## **Step 4: Result**

```
Optimal (BS): 4
```
---

## **Final Output**

```
Brute Force     : 4
Better (XOR)    : 4
Optimal (BS)    : 4
```

---

## **Time Complexity**

* Brute Force → O(n)
* XOR → O(n)
* Binary Search → **O(log n)**

---

## **Key Takeaway**

* Pattern of **even–odd pairing** is the core trick.
* Binary search only checks mid and neighbors.
* Works efficiently even for `10^5` elements.

*/