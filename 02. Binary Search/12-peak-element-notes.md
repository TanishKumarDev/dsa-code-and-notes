# Peak Element in an Array

---

## 1. Problem Restatement (Very Simple)

You are given an array `arr` of size `N`.

A **peak element** is an element which is:

```
greater than its left neighbor
AND
greater than its right neighbor
```

Formally:

```
arr[i-1] < arr[i] > arr[i+1]
```

Rules:

* If there are **multiple peaks**, return the index of **any one**.
* Array indices are **0-based**.
* First and last elements have **only one neighbor**.

---

## 2. Key Observations

1. A peak **always exists** in any array.
2. First element can be a peak if `arr[0] > arr[1]`.
3. Last element can be a peak if `arr[n-1] > arr[n-2]`.
4. We are **not asked for maximum**, only **any peak**.
5. This problem is perfect for **Binary Search on answer space**.

---

## 3. Brute Force Approach (Linear Scan)

### Intuition

Check every element and compare it with its neighbors.

* If it is greater than both neighbors → peak found.
* For boundaries, compare with the only available neighbor.

---

### Algorithm

1. Traverse the array from index `0` to `n-1`.
2. For each index `i`:

   * If `i == 0`, check `arr[0] >= arr[1]`
   * If `i == n-1`, check `arr[n-1] >= arr[n-2]`
   * Otherwise, check `arr[i] >= arr[i-1] AND arr[i] >= arr[i+1]`
3. Return the index as soon as a peak is found.

---

### Code (C++ – Brute Force)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            bool leftOK  = (i == 0) || (nums[i] > nums[i - 1]);
            bool rightOK = (i == n - 1) || (nums[i] > nums[i + 1]);

            if (leftOK && rightOK)
                return i;
        }

        return -1; // logically unreachable
    }
};

int main() {
    vector<int> nums = {1, 3, 20, 4, 1, 0};
    Solution sol;
    int idx = sol.findPeakElement(nums);
    cout << "Peak index: " << idx << ", value: " << nums[idx] << endl;
    return 0;
}
```

---

### Complexity (Brute Force)

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

## 4. Why Binary Search Works Here

This is the **most important part**.

### Core Insight

If you look at any index `mid`:

* If `arr[mid] > arr[mid+1]`
  → you are on a **descending slope**
  → a peak exists on the **left side** (including mid)

* If `arr[mid] < arr[mid+1]`
  → you are on an **ascending slope**
  → a peak exists on the **right side**

This guarantee allows us to **discard half of the array** every time.

---

## 5. Optimal Approach (Binary Search)

### Intuition (Mountain Logic)

Think of the array as hills:

* Going up → peak is ahead
* Going down → peak already passed
* Either way, **a peak must exist**

---

### Algorithm

1. Initialize:

   ```
   low = 0
   high = n - 1
   ```
2. While `low < high`:

   * Compute `mid`
   * If `nums[mid] > nums[mid + 1]`
     → peak lies on left side → `high = mid`
   * Else
     → peak lies on right side → `low = mid + 1`
3. When loop ends, `low == high`
4. That index is a peak

---

### Code (C++ – Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[mid + 1]) {
                high = mid;      // peak is on left
            } else {
                low = mid + 1;   // peak is on right
            }
        }

        return low; // or high (same)
    }
};

int main() {
    vector<int> nums = {1, 2, 1, 3, 5, 6, 4};
    Solution obj;
    cout << obj.findPeakElement(nums) << endl;
    return 0;
}
```

---

## 6. Dry Run (Important)

Example:

```
nums = [1, 2, 1, 3, 5, 6, 4]
```

Steps:

* mid = 3 → nums[3]=3 < nums[4]=5 → go right
* mid = 5 → nums[5]=6 > nums[6]=4 → go left
* converge at index 5

Answer:

```
index = 5, value = 6
```

---

## 7. Complexity (Optimal)

| Metric | Value    |
| ------ | -------- |
| Time   | O(log N) |
| Space  | O(1)     |

---

## 8. Common Interview Mistakes

1. Trying to find **maximum** instead of **any peak**
2. Using full binary search comparisons unnecessarily
3. Forgetting boundary conditions
4. Thinking array must be bitonic (it need not be)

---

## 9. Final Takeaway

* Peak element **always exists**
* Binary search works because of **monotonic slope behavior**
* This is a **pattern-based binary search**, not value-based
