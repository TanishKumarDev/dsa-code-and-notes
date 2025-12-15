# Find How Many Times the Array Has Been Rotated

*(Distinct Elements Only)*

---

## 1. Problem Restatement (Simple Words)

You are given:

* an array originally **sorted in ascending order**
* all elements are **distinct**
* the array is **rotated some number of times** (between `0` and `N-1`)

Your task:

* find **how many times the array was rotated**

---

## 2. Key Insight (Very Important)

### Rotation count = index of the **minimum element**

Why ?

---

#### Key Insight (Rotation Count)

**Rotation count = index of the minimum element**

##### Why this is true

* A sorted array starts with the **smallest element**
* Rotating the array means:

  * taking elements from the **front**
  * and moving them to the **end**
* Each rotation shifts the **smallest element one position to the right**

So:

> The number of rotations done
> = how far the smallest element moved from index `0`

That distance is exactly the **index of the minimum element**.

---

#### Example

```
Original sorted array:
[0, 1, 2, 3, 4, 5]

After 3 rotations:
[3, 4, 5, 0, 1, 2]
            ↑
     minimum element (0) at index 3
```

```
Rotation count = 3
```

---

#### Final one-line intuition (memorize)

> **Count rotations by finding where the minimum element is.**

This is the core idea used in all rotation-count problems.

---

## 3. Brute Force Approach

### Intuition

Ignore rotation logic.
Just find the **minimum element** and return its index.

---

### Algorithm

1. Assume first element is minimum
2. Traverse entire array
3. Whenever a smaller element is found:

   * update minimum
   * store its index
4. Return the index of minimum element

---

### Brute Force Code (C++)

```cpp
class Solution {
public:
    int findRotations(vector<int>& arr) {
        int n = arr.size();

        int minVal = arr[0];
        int minIndex = 0;

        for (int i = 1; i < n; i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
                minIndex = i;
            }
        }

        return minIndex;
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

## 4. Better Linear Observation (One-Pass Improvement)

### Intuition

In a rotated sorted array:

* there is **exactly one place** where order breaks
* i.e. `arr[i] > arr[i+1]`

That break point tells us:

```
rotation count = i + 1
```

If no break exists → array was not rotated.

---

### Algorithm

1. Traverse from index `0` to `n-2`
2. If `arr[i] > arr[i+1]`:

   * return `i + 1`
3. If loop ends:

   * return `0`

---

### Better Approach Code (C++)

```cpp
int findRotationCount(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return i + 1;
        }
    }

    return 0; // not rotated
}
```

---

### Complexity (Better)

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

## 5. Why Binary Search Is Possible (Core Intuition)

This problem is **exactly the same** as:

> Find the minimum in a rotated sorted array

And we already know:

* the array is split into **two sorted halves**
* minimum element is the **pivot**

So we apply **binary search** to locate the minimum efficiently.

---

## 6. Binary Search Thinking (Most Important)

Compare `arr[mid]` with `arr[high]`:

### Case 1: `arr[mid] > arr[high]`

```
[min is on the right side]
```

So:

```
low = mid + 1
```

---

### Case 2: `arr[mid] <= arr[high]`

```
[min is at mid or on the left]
```

So:

```
high = mid
```

---

When `low == high`:

* that index points to **minimum**
* which is the **rotation count**

---

## 7. Optimal Approach Algorithm

1. Set `low = 0`, `high = n - 1`
2. While `low < high`:

   * calculate `mid`
   * compare `arr[mid]` and `arr[high]`
   * discard one half
3. Return `low`

---

## 8. Optimal Code (C++ – Interview Standard)

```cpp
class Solution {
public:
    int findRotations(vector<int>& arr) {
        int low = 0;
        int high = arr.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] > arr[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }
};
```

---

## 9. Dry Run Example

```
arr = [4,5,6,7,0,1,2,3]
```

| low | mid | high | arr[mid] | arr[high] | Action        |
| --- | --- | ---- | -------- | --------- | ------------- |
| 0   | 3   | 7    | 7        | 3         | low = mid + 1 |
| 4   | 5   | 7    | 1        | 3         | high = mid    |
| 4   | 4   | 5    | 0        | 1         | high = mid    |

Stop when `low == high == 4`
Rotation count = **4**

---

## 10. Complexity (Optimal)

| Metric | Value    |
| ------ | -------- |
| Time   | O(log N) |
| Space  | O(1)     |

---

## 11. Common Interview Mistakes

* Using `low <= high` instead of `low < high`
* Returning `mid` instead of `low`
* Forgetting that this logic works only for **distinct elements**
* Confusing rotation count with number of inversions

---

## 12. Final Summary

| Approach    | Idea                     | Time     |
| ----------- | ------------------------ | -------- |
| Brute Force | Find minimum by scanning | O(N)     |
| Better      | Find break point         | O(N)     |
| Optimal     | Binary search on pivot   | O(log N) |

---