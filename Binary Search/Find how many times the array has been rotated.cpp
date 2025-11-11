#include <bits/stdc++.h>
using namespace std;

// Problem : Find how many times the array has been rotated  
// Example : 
//   arr = {4,5,6,7,0,1,2,3} → rotated 4 times → return 4  
//   arr = {3,4,5,1,2}       → rotated 3 times → return 3  
//   arr = {1,2,3,4,5}       → rotated 0 times → return 0  
//   arr = {2,3,4,5,1}       → rotated 4 times → return 4  
// Constraint : 
//   1 ≤ n ≤ 10^5  
//   Array is sorted & rotated (distinct values)  
//   Return **number of rotations** = **index of minimum element**

// Approach 1 Brute Force : 
// Intuition :  
// Think of the array as a **circle that got cut and straightened**.  
// The **minimum element** is where the **cut happened**.  
// So:  
// → Walk through the array  
// → Find the **smallest element**  
// → Its **index** = number of rotations  
// Like finding where the "1" is in a rotated [1,2,3,4,5]

// Algo :  
// 1. Initialize min_val = arr[0], index = 0  
// 2. Loop i from 1 to n-1  
//    → If arr[i] < min_val → update min_val and index  
// 3. Return index  

// TC : O(n) → scan entire array  
// SC : O(1)  

int bruteForce(vector<int>& arr) {
    int n = arr.size();
    int min_val = arr[0];
    int index = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            index = i;
        }
    }
    return index;
}

// Approach 2 Better : 
// Intuition :  
// We **already know** how to find **minimum in rotated array** using **binary search**!  
// The **index of the minimum** = **number of rotations**  
// So:  
// → Use the same **binary search logic**  
// → But **track the index** of the smallest element seen  
// → Whenever we find a candidate for min → update `ans` and `index`  
// → Finally return the index  

// Algo :  
// 1. low = 0, high = n-1  
// 2. ans = INT_MAX, index = -1  
// 3. While low <= high:  
//    mid = low + (high-low)/2  
//    → If left half sorted (arr[low] <= arr[mid]):  
//        → arr[low] is a candidate → update ans & index  
//        → Eliminate left → low = mid + 1  
//    → Else (right half sorted):  
//        → arr[mid] is a candidate → update ans & index  
//        → Eliminate right → high = mid - 1  
// 4. Return index  

// TC : O(log n) → binary search  
// SC : O(1)  

int betterApproach(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = INT_MAX;
    int index = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // If entire search space is sorted → min is at low
        if (arr[low] <= arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            break;  // no need to search further
        }
        
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            // arr[low] is the smallest in left half
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = mid + 1;  // eliminate left
        }
        // Right half is sorted
        else {
            // arr[mid] is the smallest in right half
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            high = mid - 1;  // eliminate right
        }
    }
    return index;
}

// Approach 3 Optimal: 
// Intuition :  
// The **Better** approach **is already optimal**!  
// Why?  
// → We’re doing **O(log n)** comparisons  
// → We **must** check log n elements to find pivot  
// → But we **optimize further**:  
//    → If `arr[low] <= arr[high]` → **entire range is sorted** → min is at `low` → **break early**  
//    → This avoids unnecessary steps  
// So this is **cleaner and faster in practice**

// Edge Cases Handled:  
// → n = 1 → [5] → rotated 0 times → return 0  
// → No rotation → [1,2,3,4,5] → min at 0 → return 0  
// → Full rotation → [2,3,4,5,1] → min at 4 → return 4  
// → Min at start → [1,2,3,4] → return 0  
// → Min at end → [5,1,2,3,4] → return 1  

// Best Case  : O(1) → array is sorted → break immediately  
// Avg Case   : O(log n)  
// Worst Case : O(log n) → min at end  

// Optimal Code (Clean, Safe, Early Exit)

int optimalRotationCount(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = INT_MAX;
    int index = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Optimization: entire range is sorted
        if (arr[low] <= arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            break;
        }
        
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            high = mid - 1;
        }
    }
    return index;
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2, 3};

    cout << "Brute Force : " << bruteForce(arr) << " times" << endl;
    cout << "Better      : " << betterApproach(arr) << " times" << endl;
    cout << "Optimal     : " << optimalRotationCount(arr) << " times" << endl;

    return 0;
}

/*


## **Problem Recap**

We have a sorted array that’s been rotated `k` times.
The number of rotations = **index of the minimum element (pivot)**.

---

### Example:

```
arr = {4,5,6,7,0,1,2,3}
n = 8
```

We expect output = **4**,
because the smallest element (0) is at index **4**.

---

## **Step-by-Step Dry Run of `optimalRotationCount()`**

### Initial setup:

```
low = 0
high = 7
ans = INT_MAX
index = -1
```

---

### **Iteration 1**

```
mid = low + (high - low)/2
    = 0 + (7 - 0)/2
    = 3

arr[mid] = 7
arr[low] = 4
arr[high] = 3
```

Now check the **sorted half** logic:

```
if (arr[low] <= arr[high]) 
→ 4 <= 3 → false  → skip early exit
```

Check which half is sorted:

```
if (arr[low] <= arr[mid]) → 4 <= 7 → true
→ Left half [4,5,6,7] is sorted
```

So:

```
Candidate min = arr[low] = 4
→ ans = 4, index = 0

Now eliminate left half → low = mid + 1 = 4
```

**Now:**

```
low = 4
high = 7
```

---

### **Iteration 2**

```
mid = 4 + (7 - 4)/2 = 5
arr[mid] = 1
arr[low] = 0
arr[high] = 3
```

Check full sorted condition:

```
arr[low] <= arr[high] → 0 <= 3 → true
```

→ means **entire [4..7] range is sorted**

→ Minimum is at `arr[low] = 0`

```
ans = 0
index = 4
break loop
```

---

### **Loop Ends**

Return:

```
index = 4
```

---

## **Verification**

arr = [4,5,6,7,0,1,2,3]
Minimum = 0 at index 4
→ Rotated **4 times**.

✅ **Correct Output = 4**

---

## **Dry Run Table**

| Iteration | low | high | mid | arr[mid] | Sorted Half    | Candidate Min | Update index | Next low | Next high |
| --------- | --- | ---- | --- | -------- | -------------- | ------------- | ------------ | -------- | --------- |
| 1         | 0   | 7    | 3   | 7        | Left (4 ≤ 7)   | 4             | 0            | 4        | 7         |
| 2         | 4   | 7    | 5   | 1        | Entire (0 ≤ 3) | 0             | 4            | —        | —         |

---

## **Output**

```
Brute Force : 4 times
Better      : 4 times
Optimal     : 4 times
```

---

## **Time Complexity**

| Approach    | Method                     | Time                      | Space |
| ----------- | -------------------------- | ------------------------- | ----- |
| Brute Force | Linear Scan                | O(n)                      | O(1)  |
| Better      | Binary Search              | O(log n)                  | O(1)  |
| Optimal     | Binary Search + Early Exit | O(log n) (best case O(1)) | O(1)  |

---

## **Edge Case Dry Run Check**

### Case 1: `{1,2,3,4,5}`

```
arr[low] <= arr[high] → entire array sorted
→ ans = arr[0], index = 0
→ Rotated 0 times
```

### Case 2: `{3,4,5,1,2}`

```
mid=2 → arr[mid]=5
Left sorted [3,4,5]
→ Candidate=3, low=3
Next: mid=3 → arr[mid]=1
→ Right sorted → Candidate=1, index=3
→ Rotated 3 times
```
*/