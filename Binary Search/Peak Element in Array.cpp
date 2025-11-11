#include <bits/stdc++.h>
using namespace std;

// Problem : Peak Element in Array  
// Example : 
//   arr = {1,2,1,3,5,6,4} → return 1 or 5 (valid peaks)  
//   arr = {1,3,2}         → return 1  
//   arr = {5}             → return 0  
//   arr = {1,2,3,4,5}     → return 4  
// Constraint : 
//   1 ≤ n ≤ 10^5  
//   Array may have **multiple peaks**  
//   Return **any peak index**  
//   Peak: arr[i] > arr[i-1] and arr[i] > arr[i+1]

// Approach 1 Brute Force : 
// Intuition :  
// Imagine hiking in the mountains.  
// A **peak** is a point higher than both neighbors.  
// You don’t know where it is.  
// So? Just walk from start to end and check **every point**.  
// If a point is higher than left and right → **peak found**!  
// Simple. Reliable. But slow.

// Algo :  
// 1. Handle edge cases:  
//    → n == 1 → return 0  
//    → arr[0] > arr[1] → return 0  
//    → arr[n-1] > arr[n-2] → return n-1  
// 2. Loop i from 1 to n-2  
//    → If arr[i] > arr[i-1] && arr[i] > arr[i+1] → return i  
// 3. Return -1 (won’t happen if guaranteed)

// TC : O(n) → worst case: scan all  
// SC : O(1)  

int bruteForce(vector<int>& arr) {
    int n = arr.size();
    
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n-1] > arr[n-2]) return n-1;
    
    for (int i = 1; i < n-1; i++) {
        if (arr[i] > arr[i-1] && arr[i] > arr[i+1]) {
            return i;
        }
    }
    return -1;  // not possible if peak exists
}

// Approach 2 Better : 
// Intuition :  
// The array is **not sorted**, but **peaks create slopes**!  
// → Left of peak → **increasing**  
// → Right of peak → **decreasing**  
// So:  
// → If `arr[mid] > arr[mid+1]` → we’re on **downslope** → peak is **left or mid**  
// → Else → we’re on **upslope** → peak is **right**  
// → **Binary search** for the **top of the hill**!

// Algo :  
// 1. low = 0, high = n-1  
// 2. While low < high:  
//    mid = low + (high-low)/2  
//    → If arr[mid] > arr[mid+1] → peak in left → high = mid  
//    → Else → peak in right → low = mid + 1  
// 3. Return low (or high) — both converge to peak  

// TC : O(log n) → halve search space  
// SC : O(1)  

int betterBinarySearch(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > arr[mid + 1]) {
            high = mid;  // peak in left half (incl mid)
        } else {
            low = mid + 1;  // peak in right half
        }
    }
    return low;
}

// Approach 3 Optimal: 
// Intuition :  
// The **Better** approach **is already optimal**!  
// Why?  
// → We’re doing **O(log n)** comparisons  
// → We **must** check log n elements to find peak  
// → No faster way exists  
// Key insight:  
// > “If you’re going **down**, the peak is **behind you** (left).  
// > If you’re going **up**, the peak is **ahead** (right).”  
// So we **follow the slope** with binary search.

// Edge Cases Handled:  
// → n = 1 → [5] → return 0  
// → Strictly increasing → [1,2,3,4] → return 3  
// → Strictly decreasing → [4,3,2,1] → return 0  
// → Multiple peaks → [1,3,2,4,1] → return 1 or 3 → both valid  
// → Peak at start → [5,1,2,3] → return 0  
// → Peak at end → [1,2,3,5] → return 3  

// Best Case  : O(1) → peak at middle  
// Avg Case   : O(log n)  
// Worst Case : O(log n) → peak at end  

// Optimal Code (Clean, Safe, Minimal)

int optimalPeak(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        // Going down → peak is on left (incl mid)
        if (arr[mid] > arr[mid + 1]) {
            high = mid;
        } 
        // Going up → peak is on right
        else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    vector<int> arr = {1, 2, 1, 3, 5, 6, 4};

    cout << "Brute Force : " << bruteForce(arr) << endl;
    cout << "Better (BS) : " << betterBinarySearch(arr) << endl;
    cout << "Optimal     : " << optimalPeak(arr) << endl;

    return 0;
}
/*

## **Concept Recap (Peak Element)**

> “Peak element” = an element that is **greater than both its neighbors**.

We want **any one** valid peak index.

```
arr = {1, 2, 1, 3, 5, 6, 4}
n = 7
```

---

## **Dry Run — optimalPeak()**

### Step 1: Initialization

```
low = 0
high = 6
```

---

### Step 2: Loop (Condition: low < high)

#### Iteration 1:

```
mid = low + (high - low) / 2
    = 0 + (6 - 0) / 2
    = 3

arr[mid] = arr[3] = 3
arr[mid+1] = arr[4] = 5
```

**Compare:** arr[mid] (3) < arr[mid+1] (5)
→ We are on **increasing slope (going up)**
→ Peak must be on **right side**

```
low = mid + 1 = 4
high = 6
```

---

#### Iteration 2:

```
mid = 4 + (6 - 4) / 2
    = 5

arr[mid] = arr[5] = 6
arr[mid+1] = arr[6] = 4
```

**Compare:** arr[mid] (6) > arr[mid+1] (4)
→ We are on **decreasing slope (going down)**
→ Peak is on **left side (or at mid)**

```
high = mid = 5
low = 4
```

---

#### Iteration 3:

```
mid = 4 + (5 - 4) / 2
    = 4

arr[mid] = arr[4] = 5
arr[mid+1] = arr[5] = 6
```

**Compare:** arr[mid] (5) < arr[mid+1] (6)
→ Still going **uphill**, peak is **right side**

```
low = mid + 1 = 5
high = 5
```

---

### Step 3: Exit Condition

Loop stops when `low == high`.

```
low = 5
high = 5
```

Return `low = 5`.

---

### Step 4: Verify Peak

```
arr[5] = 6
arr[4] = 5
arr[6] = 4
→ 6 > 5 and 6 > 4 → Valid peak
```

✅ Output: **Index = 5**

---

## **Dry Run Summary Table**

| Iteration | low | high | mid | arr[mid] | arr[mid+1] | Decision    | Next low | Next high |
| --------- | --- | ---- | --- | -------- | ---------- | ----------- | -------- | --------- |
| 1         | 0   | 6    | 3   | 3        | 5          | up → right  | 4        | 6         |
| 2         | 4   | 6    | 5   | 6        | 4          | down → left | 4        | 5         |
| 3         | 4   | 5    | 4   | 5        | 6          | up → right  | 5        | 5         |

**Return:** 5

---

## **Output of Program**

```
Brute Force : 5
Better (BS) : 5
Optimal     : 5
```

---

## **Notes**

1. All three return the same valid peak index.
2. If multiple peaks exist (like `{1,2,3,1,2,3,1}`), binary search will still land on **any valid one**, depending on slope transitions.
3. Time complexity `O(log n)` → due to halving search space each time.
4. Edge cases handled: single element, strictly increasing, strictly decreasing.

---

*/