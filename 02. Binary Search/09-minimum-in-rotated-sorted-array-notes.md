# Minimum Element in Rotated Sorted Array

*(Distinct Elements Only)*

---

## 1. Problem Restatement (Simple Words)

You are given:

* an array sorted in **ascending order**
* all elements are **distinct**
* the array is **rotated** at some unknown index

Your task:

* find the **minimum element** in the array

---

## 2. Key Observation (Before Coding)

A rotated sorted array looks like:

```
Sorted:        [1, 2, 3, 4, 5, 6, 7]
Rotated:       [4, 5, 6, 7, 1, 2, 3]
                           ↑
                     minimum element
```

Important facts:

* Array consists of **two sorted parts**
* The **minimum element** is the point where rotation happened
* That element is the **only element smaller than its previous element**

---

## 3. Brute Force Approach

### Intuition

Ignore rotation and sorting.

Just scan the array and track the minimum.

---

### Algorithm

1. Initialize `minVal = +infinity`
2. Traverse the array
3. Update `minVal` with the smallest value seen
4. Return `minVal`

---

### Brute Force Code (C++)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int minVal = INT_MAX;

        for (int i = 0; i < nums.size(); i++) {
            minVal = min(minVal, nums[i]);
        }

        return minVal;
    }
};
```

---

### Complexity (Brute Force)

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

## 4. Why We Need Optimization

* The array is **almost sorted**
* Brute force ignores structure
* Binary search can reduce search space from **N → log N**

---

## 5. Core Binary Search Intuition (Most Important Part)

### What we want

We want to **locate the pivot point** (minimum element).

### Crucial Observation

Compare `nums[mid]` with `nums[high]`:

#### Case 1: `nums[mid] > nums[high]`

```
[ sorted | mid | rotated | min ]
```

* Minimum lies **to the right**
* Discard left half

```
low = mid + 1
```

---

#### Case 2: `nums[mid] <= nums[high]`

```
[ min | sorted | mid ]
```

* Minimum lies **at mid or to the left**
* Keep mid in search

```
high = mid
```

---

Why this works:

* Rightmost element always belongs to **second sorted part**
* Comparing with it tells us **which side mid belongs to**

---

## 6. Binary Search Algorithm (Step-by-Step)

1. Set `low = 0`, `high = n - 1`
2. While `low < high`:

   * Calculate `mid`
   * If `nums[mid] > nums[high]`:

     * `low = mid + 1`
   * Else:

     * `high = mid`
3. Loop ends when `low == high`
4. Return `nums[low]`

---

## 7. Optimal Code (C++ – Interview Standard)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return nums[low];
    }
};
```

---

## 8. Dry Run Example

### Example

```
nums = [4,5,6,7,0,1,2]
```

| low | mid | high | nums[mid] | nums[high] | Action                 |
| --- | --- | ---- | --------- | ---------- | ---------------------- |
| 0   | 3   | 6    | 7         | 2          | mid > high → low = 4   |
| 4   | 5   | 6    | 1         | 2          | mid <= high → high = 5 |
| 4   | 4   | 5    | 0         | 1          | mid <= high → high = 4 |

Stop when `low == high == 4`
Answer = `nums[4] = 0`

---

## 9. Complexity Analysis (Optimal)

| Metric | Value    |
| ------ | -------- |
| Time   | O(log N) |
| Space  | O(1)     |

---

## 10. Interview Notes (Very Important)

### Why `low < high` and not `<=`?

Because we want to **stop exactly at the minimum**, not overshoot.

---

### Why compare with `nums[high]`?

Because:

* `high` always lies in **right sorted portion**
* Helps detect which side is unsorted

---

### Distinct elements assumption

This logic **breaks with duplicates**
For duplicates, we need a different version (Rotated Sorted Array II)

---

## 11. Common Mistakes

* Using `low <= high` loop
* Comparing with `nums[low]` instead of `nums[high]`
* Returning `mid` instead of `nums[low]`
* Forgetting this works only for **distinct values**
