#include <bits/stdc++.h>
using namespace std;

// Problem : Search Element in Rotated Sorted Array II (with duplicates)  
// Example : 
//   arr = {7,8,1,2,3,3,3,4,5,6}, k = 3 → return true  
//   arr = {1,0,1,1,1}, k = 0 → return true  
//   arr = {2,2,2,2,2}, k = 3 → return false  
//   arr = {1}, k = 1 → return true  
// Constraint : 
//   1 ≤ n ≤ 10^5  
//   Array is sorted & rotated  
//   May contain duplicates  
//   Return true if k exists, else false

// Approach 1 Brute Force : 
// Intuition :  
// Picture a messy room with scattered toys — some are same, some different.  
// You don’t care about order. You just want to know: **Is the red car here?**  
// So you check **every toy**, one by one.  
// No shortcuts. No tricks. Just pure effort.  
// Works always — even with duplicates.

// Algo :  
// 1. Loop from i = 0 to n-1  
// 2. If arr[i] == k → return true  
// 3. End of loop → return false  

// TC : O(n) → must check every element in worst case  
// SC : O(1) → only loop variable  

bool bruteForce(vector<int>& arr, int k) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == k) return true;
    }
    return false;
}

// Approach 2 Better : 
// Intuition :  
// We want **Binary Search** speed — O(log n).  
// But now? **Duplicates exist** → like [1,1,1,1,0,1,1]  
// Problem: When `arr[low] == arr[mid] == arr[high]`, we **can’t tell** which half is sorted!  
// Example: [3,3,3,3,3] → mid=3, low=3, high=3 → no clue!  
// So we **trim** the edges:  
// → Skip `low` and `high` if they equal `mid`  
// → Because if `k` was there, we’d have found it at `mid`  
// → This **reduces search space safely**  
// Then apply **same logic** as before: find sorted half → eliminate  

// Algo :  
// 1. low = 0, high = n-1  
// 2. While low <= high:  
//    mid = low + (high-low)/2  
//    If arr[mid] == k → return true  
//    If arr[low] == arr[mid] == arr[high] → low++, high-- (trim edges)  
//    Else:  
//       → If left sorted (arr[low] <= arr[mid]):  
//           → If k in [arr[low], arr[mid]] → high = mid-1  
//           → Else → low = mid+1  
//       → Else (right sorted):  
//           → If k in [arr[mid], arr[high]] → low = mid+1  
//           → Else → high = mid-1  
// 3. Return false  

// TC : 
//   Best/Avg : O(log n) → normal binary search  
//   Worst    : O(n) → when array is like [1,1,1,1,...,1,0] → keeps trimming  
// SC : O(1)  

bool betterApproach(vector<int>& arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == k) 
            return true;
        
        // Handle duplicate case: can't decide which side is sorted
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }
        
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (k >= arr[low] && k <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if (k >= arr[mid] && k <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return false;
}

// Approach 3 Optimal: 
// Intuition :  
// The "Better" approach **is already optimal**!  
// Why?  
// → With **no duplicates** → O(log n)  
// → With **duplicates** → worst case O(n) is **unavoidable**  
// → Example: [1,1,1,1,1,1,1,1,0] → to find 0, you **must** check nearly all  
// → No way to skip large chunks when values are same  
// So this **trim + binary search** is the **best possible**  
// It’s like:  
// > “I’ll be smart when I can (log n),  
// > But if everything looks the same, I have no choice but to look carefully.”  

// Edge Cases Handled:  
// → All elements same, k not present: [2,2,2,2], k=3 → false  
// → All elements same, k present: [2,2,2,2], k=2 → true  
// → Target at pivot: [1,0,1,1,1] → true  
// → n = 1: [5], k=5 → true  
// → k at start/end: [7,8,1,2,3], k=7 → true  

// Best Case  : O(1) → target at mid  
// Avg Case   : O(log n) → few duplicates  
// Worst Case : O(n) → many duplicates, target at end  

// Optimal Code (Clean, Safe, Commented)

bool optimalSearch(vector<int>& arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Found target
        if (arr[mid] == k) 
            return true;
        
        // Edge case: can't tell which side is sorted
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }
        
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            // Target lies in left half
            if (k >= arr[low] && k <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // Right half is sorted
        else {
            // Target lies in right half
            if (k >= arr[mid] && k <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return false;
}

int main() {
    vector<int> arr = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6};
    int k = 3;

    cout << "Brute Force: " << (bruteForce(arr, k) ? "true" : "false") << endl;
    cout << "Better:      " << (betterApproach(arr, k) ? "true" : "false") << endl;
    cout << "Optimal:     " << (optimalSearch(arr, k) ? "true" : "false") << endl;

    return 0;
}

/*
## **Goal**

Find whether element `k` exists in a **rotated sorted array** that **may contain duplicates**.

---

## **Input Example**

```
arr = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6}
k = 3
n = 10
```

Expected Output: **true**

---

## **Algorithm Reminder**

### Logic used:

1. Compute `mid = (low + high)/2`
2. If `arr[mid] == k` → found → return true
3. If duplicates confuse sorting (`arr[low] == arr[mid] == arr[high]`) →
   → skip both ends (`low++`, `high--`)
4. If **left half sorted** (`arr[low] <= arr[mid]`):

   * If `k` lies between `arr[low]` and `arr[mid]` → move left
   * Else → move right
5. Else (**right half sorted**):

   * If `k` lies between `arr[mid]` and `arr[high]` → move right
   * Else → move left

---

## **Step-by-Step Dry Run**

### Step 1: Initialization

```
low = 0
high = 9
```

---

### Iteration 1:

```
mid = (0 + 9)/2 = 4
arr[mid] = arr[4] = 3
```

Check:

```
arr[mid] == k → 3 == 3 → true
```

✅ Found immediately → return `true`.

---

### So, for this input, it ends in **just one iteration (best case)**.

---

## **Let’s take a more detailed dry run**

(for clarity, let’s simulate a trickier input).

### Case: arr = {1, 0, 1, 1, 1}, k = 0

This is the classic ambiguous-duplicate case.

```
index: 0  1  2  3  4
value: 1  0  1  1  1
```

We want to see how trimming (`low++`, `high--`) works.

---

### Initialization

```
low = 0, high = 4
```

---

### Iteration 1

```
mid = (0 + 4)/2 = 2
arr[mid] = arr[2] = 1
```

→ Not found.

Now check ambiguity:

```
arr[low] == arr[mid] == arr[high]
1 == 1 == 1 → true
→ Can't tell sorted half → skip edges
low++, high--
```

```
low = 1, high = 3
```

---

### Iteration 2

```
mid = (1 + 3)/2 = 2
arr[mid] = arr[2] = 1
```

Check sorted halves:

```
arr[low] = 0, arr[mid] = 1 → left half sorted
```

Check if target (k=0) in [arr[low], arr[mid]]:

```
0 >= 0 && 0 <= 1 → true
→ So target in left half
→ high = mid - 1 = 1
```

```
low = 1, high = 1
```

---

### Iteration 3

```
mid = (1 + 1)/2 = 1
arr[mid] = arr[1] = 0
```

Check:

```
arr[mid] == k → 0 == 0 → true
```

✅ Found → return true.

---

## **Dry Run Summary Table**

| Iteration | low | high | mid | arr[mid] | arr[low] | arr[high] | Decision          | Next low | Next high |
| --------- | --- | ---- | --- | -------- | -------- | --------- | ----------------- | -------- | --------- |
| 1         | 0   | 4    | 2   | 1        | 1        | 1         | duplicates → trim | 1        | 3         |
| 2         | 1   | 3    | 2   | 1        | 0        | 1         | target in left    | 1        | 1         |
| 3         | 1   | 1    | 1   | 0        | 0        | 1         | found             | —        | —         |

---

## **Output**

```
Brute Force: true
Better:      true
Optimal:     true
```

---

## **Complexity Analysis**

| Case    | Time Complexity | Reason                                  |
| ------- | --------------- | --------------------------------------- |
| Best    | O(1)            | found at first mid                      |
| Average | O(log n)        | normal binary search                    |
| Worst   | O(n)            | when many duplicates like [1,1,1,1,1,0] |

---

## **Edge Case Checks**

| Case                | Input            | Output | Reason                 |
| ------------------- | ---------------- | ------ | ---------------------- |
| All same, not found | [2,2,2,2], k=3   | false  | trims all edges        |
| All same, found     | [2,2,2,2], k=2   | true   | found instantly        |
| Target at pivot     | [1,0,1,1,1], k=0 | true   | handled correctly      |
| Single element      | [5], k=5         | true   | trivial                |
| Target at start     | [7,8,1,2,3], k=7 | true   | left half sorted works |

---

## **Key Insights**

1. **Duplicates cause uncertainty**, so the algorithm trims edges carefully.
2. In all other cases, **binary search logic** works as usual.
3. Worst-case linear time is **mathematically unavoidable** if all values are same.
4. Using `arr[low]`, `arr[mid]`, `arr[high]` comparisons ensures **no out-of-bound** issues.

---
*/