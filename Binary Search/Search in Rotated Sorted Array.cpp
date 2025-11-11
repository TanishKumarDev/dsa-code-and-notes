#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : Search Element in a Rotated Sorted Array  
// Example : arr = {7,8,9,1,2,3,4,5,6}, k = 1 → return 3  
//           arr = {4,5,6,7,0,1,2}, k = 0 → return 4  
//           arr = {1}, k = 1 → return 0  
// Constraint : 1 ≤ n ≤ 10^5, distinct values, rotated sorted array

// 🔴 Approach 1 Brute Force : 
// Intuition :  
// Imagine you’re standing in front of a long shelf of books. The books were once in perfect order (1,2,3...), but someone spun the shelf — now it’s broken into two parts, but each part is still sorted!  
// You don’t know where the break is, but you *do* know the books are unique.  
// So, the simplest thing? Just walk from left to right and check every book.  
// No smart moves — just pure effort. Works always. But slow.

// Algo :  
// 1. Loop through array from i = 0 to n-1  
// 2. If arr[i] == k → return i  
// 3. If loop ends → return -1  

// TC : O(n) → worst case: check every element  
// SC : O(1) → only using one variable i  

// 🔵 Approach 2 Better :  
// Intuition :  
// We know **Binary Search** is magic on sorted arrays — cuts search in half every step.  
// But here? The array is **rotated**, so it’s not fully sorted.  
// Still… if you look closely:  
// → At any point, **one half is always sorted**!  
// → Like a broken ruler — one side is straight, the other is bent.  
// So idea:  
// 1. Find which half is sorted  
// 2. Check if target can be in that sorted half  
// 3. If yes → search there  
// 4. If no → jump to the other half  
// This is **smart elimination** — we’re not guessing, we’re *reasoning*!

// Algo :  
// 1. low = 0, high = n-1  
// 2. While low <= high:  
//    mid = (low + high) / 2  
//    If arr[mid] == k → return mid  
//    Else:  
//       → If left half sorted (arr[low] <= arr[mid]):  
//           → If k is in [arr[low], arr[mid]] → search left: high = mid-1  
//           → Else → search right: low = mid+1  
//       → Else (right half sorted):  
//           → If k is in [arr[mid], arr[high]] → search right: low = mid+1  
//           → Else → search left: high = mid-1  
// 3. Return -1 if not found  

// TC : O(log n) → each step cuts search space in half  
// SC : O(1) → only low, high, mid  

// 🟢 Approach 3 Optimal:  
// Intuition :  
// Same as Better — **there is no faster than O(log n)** for search in sorted/rotated data!  
// Why? Because even with rotation, we’re still doing **binary decisions**.  
// The key insight:  
// > “Even in a rotated sorted array, **exactly one half is always sorted**.”  
// This lets us **confidently eliminate half** every time.  
// It’s like playing 20 questions — but with math.

// Edge Cases & Analysis :  
// → n = 1: [5], k = 5 → return 0  
// → k not present: [1,2,3], k = 4 → return -1  
// → k at pivot: [4,5,1,2,3], k = 1 → return 2  
// → k at start: [7,8,9,1,2], k = 7 → return 0  
// → k at end: [3,4,5,1,2], k = 2 → return 4  
// → Duplicates? → Problem says **distinct values** → safe!  
// → Overflow? → Use mid = low + (high-low)/2 → but in C++ int is fine for n≤1e5  

// Best Case  : O(1) → target at middle  
// Avg Case   : O(log n)  
// Worst Case : O(log n) → target at end or not present  

// 🟢 Optimal Code (Clean & Safe)

int search(vector<int>& arr, int n, int k) {
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoids overflow
        
        if (arr[mid] == k) 
            return mid;
        
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            // Target lies in left sorted half
            if (arr[low] <= k && k <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // Right half is sorted
        else {
            // Target lies in right sorted half
            if (arr[mid] <= k && k <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    vector<int> arr = {7, 8, 9, 1, 2, 3, 4, 5, 6};
    int n = arr.size(), k = 1;
    int ans = search(arr, n, k);
    
    if (ans == -1)
        cout << "Target is not present.\n";
    else
        cout << "The index is: " << ans << "\n";
    
    return 0;
}
/*

## **Problem Recap**

We are searching for `k` in a **rotated sorted array** (distinct values).
Array is formed by rotating a normally sorted array at some pivot index.

Example:

```
Original: [1,2,3,4,5,6,7,8,9]
Rotated : [7,8,9,1,2,3,4,5,6]   (rotated 3 times)
```

We must find the index of `k` if it exists.

---

## **Example Input**

```
arr = {7,8,9,1,2,3,4,5,6}
k = 1
```

Expected Output:
`Index = 3`

---

## **Step-by-Step Dry Run**

### **Step 1: Initialization**

```
low = 0
high = 8
```

Array:

```
Index:  0  1  2  3  4  5  6  7  8
Value:  7  8  9  1  2  3  4  5  6
```

---

### **Iteration 1**

```
mid = low + (high - low)/2
    = 0 + (8 - 0)/2
    = 4
arr[mid] = arr[4] = 2
```

Check:

```
arr[mid] == k? → 2 == 1 → false
```

Determine sorted half:

```
arr[low] = 7, arr[mid] = 2
→ arr[low] <= arr[mid]? → 7 <= 2 → false
```

So **left half is not sorted**, hence **right half is sorted**.

Now check if target lies in right sorted half:

```
arr[mid] = 2, arr[high] = 6
Is k in [2,6]? → 1 in [2,6]? → false
```

So target lies in the **left half**.

Move:

```
high = mid - 1 = 3
```

---

### **Iteration 2**

```
low = 0
high = 3
mid = 0 + (3 - 0)/2 = 1
arr[mid] = arr[1] = 8
```

Check:

```
arr[mid] == k? → 8 == 1 → false
```

Determine sorted half:

```
arr[low] = 7, arr[mid] = 8
→ arr[low] <= arr[mid] → 7 <= 8 → true
→ Left half is sorted.
```

Now check if k lies in left half:

```
Is k in [arr[low], arr[mid]] → [7,8]? → 1 in [7,8]? → false
```

So target is in the **right half**.

Move:

```
low = mid + 1 = 2
```

---

### **Iteration 3**

```
low = 2
high = 3
mid = 2 + (3 - 2)/2 = 2
arr[mid] = arr[2] = 9
```

Check:

```
arr[mid] == k? → 9 == 1 → false
```

Determine sorted half:

```
arr[low] = 9, arr[mid] = 9 → left sorted (equal means sorted).
```

Check range:

```
Is k in [9,9]? → 1 in [9,9]? → false
→ Not in left → go right
```

Move:

```
low = mid + 1 = 3
```

---

### **Iteration 4**

```
low = 3
high = 3
mid = 3 + (3 - 3)/2 = 3
arr[mid] = arr[3] = 1
```

Check:

```
arr[mid] == k → 1 == 1 → true
```

✅ Found at **index = 3**

---

## **Dry Run Summary Table**

| Iteration | low | high | mid | arr[mid] | Sorted Half  | Range Check    | Next low | Next high |
| --------- | --- | ---- | --- | -------- | ------------ | -------------- | -------- | --------- |
| 1         | 0   | 8    | 4   | 2        | Right sorted | k not in [2,6] | 0        | 3         |
| 2         | 0   | 3    | 1   | 8        | Left sorted  | k not in [7,8] | 2        | 3         |
| 3         | 2   | 3    | 2   | 9        | Left sorted  | k not in [9,9] | 3        | 3         |
| 4         | 3   | 3    | 3   | 1        | —            | Found          | —        | —         |

---

## **Output**

```
The index is: 3
```

✅ Correct.

---

## **Complexity Analysis**

| Approach         | Method        | Time         | Space |
| ---------------- | ------------- | ------------ | ----- |
| Brute Force      | Linear scan   | O(n)         | O(1)  |
| Better / Optimal | Binary Search | **O(log n)** | O(1)  |

---

## **Edge Case Verification**

| Case           | Array           | k | Output | Explanation                        |
| -------------- | --------------- | - | ------ | ---------------------------------- |
| Single element | [5]             | 5 | 0      | Found at index 0                   |
| No rotation    | [1,2,3,4,5]     | 3 | 2      | Works same as normal binary search |
| Fully rotated  | [2,3,4,5,1]     | 1 | 4      | Found at last index                |
| Pivot search   | [4,5,6,7,0,1,2] | 0 | 4      | Found correctly                    |
| Not found      | [3,4,5,6,7]     | 9 | -1     | Returns correctly                  |

---

## **Key Insights**

1. **One half is always sorted** in a rotated sorted array.
   This property makes binary search applicable.
2. Checking `arr[low] <= arr[mid]` helps identify the sorted half.
3. Compare the target range to eliminate half each iteration.
4. Distinct elements guarantee no ambiguity.
5. `mid = low + (high - low)/2` avoids overflow for large arrays.

---

*/