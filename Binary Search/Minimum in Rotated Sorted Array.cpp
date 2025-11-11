#include <bits/stdc++.h>
using namespace std;

// Problem : Minimum in Rotated Sorted Array  
// Example : 
//   arr = {4,5,6,7,0,1,2} → return 0  
//   arr = {3,4,5,1,2}     → return 1  
//   arr = {1}             → return 1  
//   arr = {2,1}           → return 1  
// Constraint : 
//   1 ≤ n ≤ 10^5  
//   Array is sorted & rotated  
//   All values are **distinct**  
//   Find the **minimum** element

// Approach 1 Brute Force : 
// Intuition :  
// Imagine a rollercoaster track — it goes up, then suddenly drops.  
// The **lowest point** is where the drop starts.  
// But you don’t know where.  
// So? Just walk the whole track and find the lowest spot.  
// Simple. Reliable. But slow.

// Algo :  
// 1. Initialize min_val = arr[0]  
// 2. Loop i from 1 to n-1  
//    → If arr[i] < min_val → update min_val  
// 3. Return min_val  

// TC : O(n) → worst case: min at the end  
// SC : O(1) → only one variable  

int bruteForce(vector<int>& arr) {
    int min_val = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Approach 2 Better : 
// Intuition :  
// We know **one half is always sorted**, and the **minimum is the start of the unsorted half**.  
// Think of the array like a **mountain**:  
// → Left of min → increasing  
// → Right of min → increasing  
// → The **minimum** is the **pivot** where rotation happened.  
// So:  
// → If `arr[mid] > arr[high]` → right half has the drop → go right  
// → Else → left half (including mid) has the min → go left  
// It’s like **binary search for the drop point**!

// Algo :  
// 1. low = 0, high = n-1  
// 2. While low < high:  
//    mid = low + (high-low)/2  
//    → If arr[mid] > arr[high] → min is in right → low = mid + 1  
//    → Else → min is in left (incl mid) → high = mid  
// 3. Return arr[low] (or arr[high]) — both point to min  

// TC : O(log n) → halve search space every step  
// SC : O(1)  

int betterApproach(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return arr[low];
}

// Approach 3 Optimal: 
// Intuition :  
// The "Better" approach **is already optimal**!  
// Why?  
// → We’re doing **O(log n)** comparisons  
// → We **must** check log n elements to find the pivot  
// → No faster way exists  
// Key insight:  
// > “The minimum element is the **only one smaller than the last element in its half**.”  
// So we **compare mid with high** — not low — to avoid confusion.  
// This is **cleaner and safer** than comparing with low.

// Edge Cases Handled:  
// → n = 1 → [5] → return 5  
// → No rotation → [1,2,3,4,5] → min = 1 → correct  
// → Full rotation → [2,1] → min = 1  
// → Min at start → [1,2,3,4] → correct  
// → Min at end → [4,5,1,2,3] → correct  

// Best Case  : O(1) → min at middle  
// Avg Case   : O(log n)  
// Worst Case : O(log n) → min at end  

// Optimal Code (Clean, Safe, Minimal)

int optimalMin(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        // Right half has the drop → min is in right
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } 
        // Left half (incl mid) has the min
        else {
            high = mid;
        }
    }
    return arr[low];  // low == high at end
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, -1, 1, 2};

    cout << "Brute Force : " << bruteForce(arr) << endl;
    cout << "Better      : " << betterApproach(arr) << endl;
    cout << "Optimal     : " << optimalMin(arr) << endl;

    return 0;
}

/*
## **Concept Recap**

We are finding the **minimum element** (pivot) in a **rotated sorted array** with **distinct elements**.
The array is logically split into two sorted halves:

```
Left half  → increasing
Right half → increasing
Pivot (min) → smallest, where rotation happened
```

Binary Search is used to find that pivot efficiently.

---

## **Example Input**

```
arr = {4, 5, 6, 7, 0, -1, 1, 2}
index: 0  1  2  3  4  5  6  7
n = 8
```

Expected Output → `-1`
because it’s the smallest element.

---

## **Initial Setup**

```
low = 0
high = 7
```

We will keep updating `low` and `high` using the rule:

```
if (arr[mid] > arr[high]) → min is in right half → low = mid + 1
else                     → min is in left half (including mid) → high = mid
```

---

## **Iteration 1**

```
mid = low + (high - low)/2
    = 0 + (7 - 0)/2
    = 3

arr[mid] = arr[3] = 7
arr[high] = arr[7] = 2
```

Compare:

```
arr[mid] > arr[high] → 7 > 2 → true
→ right half has the drop → move right
→ low = mid + 1 = 4
```

```
Now: low = 4, high = 7
```

---

## **Iteration 2**

```
mid = 4 + (7 - 4)/2
    = 5

arr[mid] = arr[5] = -1
arr[high] = arr[7] = 2
```

Compare:

```
arr[mid] > arr[high] → -1 > 2 → false
→ min lies in left half (including mid)
→ high = mid = 5
```

```
Now: low = 4, high = 5
```

---

## **Iteration 3**

```
mid = 4 + (5 - 4)/2
    = 4

arr[mid] = arr[4] = 0
arr[high] = arr[5] = -1
```

Compare:

```
arr[mid] > arr[high] → 0 > -1 → true
→ min lies in right half
→ low = mid + 1 = 5
```

```
Now: low = 5, high = 5
```

---

## **Loop Ends (low == high)**

Exit condition satisfied.

Return:

```
arr[low] = arr[5] = -1
```

✅ **Output = -1**

---

## **Dry Run Summary Table**

| Iteration | low | high | mid | arr[mid] | arr[high] | Comparison | Decision   | Next low | Next high |
| --------- | --- | ---- | --- | -------- | --------- | ---------- | ---------- | -------- | --------- |
| 1         | 0   | 7    | 3   | 7        | 2         | 7 > 2      | move right | 4        | 7         |
| 2         | 4   | 7    | 5   | -1       | 2         | -1 < 2     | move left  | 4        | 5         |
| 3         | 4   | 5    | 4   | 0        | -1        | 0 > -1     | move right | 5        | 5         |

Final:

```
low = 5, high = 5
arr[5] = -1
```

---

## **Output of Program**

```
Brute Force : -1
Better      : -1
Optimal     : -1
```

---

## **Time Complexity Analysis**

| Approach    | Idea                   | Time     | Space |
| ----------- | ---------------------- | -------- | ----- |
| Brute Force | Linear scan            | O(n)     | O(1)  |
| Better      | Binary Search          | O(log n) | O(1)  |
| Optimal     | Same + clean condition | O(log n) | O(1)  |

---

## **Edge Case Verification**

| Case            | Array              | Output | Reason                |
| --------------- | ------------------ | ------ | --------------------- |
| No rotation     | [1,2,3,4,5]        | 1      | already sorted        |
| Single element  | [5]                | 5      | trivial               |
| Full rotation   | [2,1]              | 1      | pivot at end          |
| Rotated many    | [3,4,5,1,2]        | 1      | pivot at mid          |
| Negative values | [4,5,6,7,0,-1,1,2] | -1     | pivot correctly found |

---

## **Key Insight**

Binary search works because in a rotated sorted array:

* **Left half sorted** ⇒ pivot on right
* **Right half sorted** ⇒ pivot on left
* Comparison with `arr[high]` keeps direction consistent.
*/