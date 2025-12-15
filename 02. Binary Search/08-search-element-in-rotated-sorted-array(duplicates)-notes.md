# 🔍 Search Element in Rotated Sorted Array II (With Duplicates)

---

## 1. Problem Restated (Very Simple)

You are given:

- a **sorted array**
- which is **rotated**
- and **may contain duplicates**
- a target value `k`

👉 Return **true** if `k` exists
👉 Otherwise return **false**

**Important difference from previous problem**
Here → **duplicates exist**, so some binary search assumptions break.

---

## 2. Brute Force Approach (Baseline – Always Start Here)

### 💡 Intuition

Forget sorting, forget rotation.

Just **check every element**.

If target is present anywhere → answer is `true`.

---

### 🧠 Algorithm

1. Traverse array from index `0` to `n-1`
2. If `arr[i] == k` → return `true`
3. End of loop → return `false`

---

### 💻 Brute Force Code (C++)

```cpp
class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int>& arr, int k) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == k)
                return true;
        }
        return false;
    }
};
```

---

### ⏱ Complexity (Brute Force)

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

## 3. Why We Need Optimization

- Array is **almost sorted**
- Linear scan wastes structure
- We _should_ use **Binary Search**

But ⚠️
**Duplicates break normal rotated-array logic**

So we need **extra handling**

---

## 4. Key Binary Search Observation (VERY IMPORTANT)

In **rotated sorted array (without duplicates)**:

- One half is always sorted

But with **duplicates**:

```
arr[low] == arr[mid] == arr[high]
```

👉 We **cannot determine** which half is sorted

So we must:
➡️ **shrink the search space manually**

---

## 5. Core Intuition (This is the HEART of the problem)

### Three cases every time:

#### ✅ Case 1: Target found

```
arr[mid] == k → return true
```

---

#### ⚠️ Case 2: Duplicate ambiguity

```
arr[low] == arr[mid] == arr[high]
```

👉 Cannot decide sorted side
👉 Just **shrink boundaries**

```
low++
high--
```

This is why **worst case becomes O(N)**

---

#### ✅ Case 3: One side is sorted

##### Left half sorted

```
arr[low] <= arr[mid]
```

- If target lies in `[low, mid]` → go left
- Else → go right

##### Right half sorted

```
arr[mid] <= arr[high]
```

- If target lies in `[mid, high]` → go right
- Else → go left

---

## 6. Step-by-Step Algorithm (Optimized)

1. Set `low = 0`, `high = n-1`
2. While `low <= high`:

   - Compute `mid`
   - If `arr[mid] == k` → return true
   - If `arr[low] == arr[mid] == arr[high]`:

     - `low++`, `high--`

   - Else if left half sorted:

     - Check target range → move accordingly

   - Else right half sorted:

     - Check target range → move accordingly

3. Loop ends → return false

---

## 7. Optimized Code (C++ – Interview Standard)

```cpp
class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int>& arr, int k) {
        int low = 0, high = arr.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Case 1: found target
            if (arr[mid] == k)
                return true;

            // Case 2: duplicates, cannot decide
            if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
                low++;
                high--;
                continue;
            }

            // Case 3: left half sorted
            if (arr[low] <= arr[mid]) {
                if (arr[low] <= k && k <= arr[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // Right half sorted
            else {
                if (arr[mid] <= k && k <= arr[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return false;
    }
};
```

---

## 8. Dry Run (Example)

```
arr = [7,8,1,2,3,3,3,4,5,6]
k = 3
```

- mid lands on `3` → found → return true

```
k = 10
```

- binary search keeps shrinking
- never found → return false

---

## 9. Complexity Analysis (IMPORTANT FOR INTERVIEW)

| Case                   | Time     |
| ---------------------- | -------- |
| Best / Avg             | O(log N) |
| Worst (all duplicates) | O(N)     |
| Space                  | O(1)     |

⚠️ **Worst case degrades because of duplicates**

---

## 10. Interview Notes (VERY IMPORTANT)

### ❓ Why worst case is O(N)?

Because when:

```
arr[low] == arr[mid] == arr[high]
```

we only shrink by **1 element** on each side.

---

### ❓ Difference from Rotated Array I?

| Feature        | Version I | Version II |
| -------------- | --------- | ---------- |
| Duplicates     | ❌ No     | ✅ Yes     |
| Worst Case     | O(log N)  | O(N)       |
| Extra handling | ❌        | ✅         |

---

### ❓ What to say in interview?

> “Because duplicates exist, binary search may degenerate to linear time in worst case.”

---

## 11. Common Mistakes

❌ Forgetting duplicate case
❌ Assuming one side always sorted
❌ Using `<` instead of `<=`
❌ Missing `continue` after shrinking

---
