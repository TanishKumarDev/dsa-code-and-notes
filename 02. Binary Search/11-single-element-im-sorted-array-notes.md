

# Search Single Element in a Sorted Array

*(Every element appears twice except one)*

---

## 1. Problem Restatement (Simple Words)

You are given:

* a **sorted array**
* every element appears **exactly twice**
* **one element appears only once**

Your task:

* find and return that **single (unique) element**

The array is guaranteed to follow this rule.

---

## 2. Important Observations

1. The array is **sorted**
2. Duplicate elements always appear **in pairs**
3. Only **one element breaks this pairing**
4. Pairing structure helps us optimize using **Binary Search**

---

## 3. Brute Force Approach 1 – Neighbor Comparison

### Intuition

Since the array is sorted:

* duplicates are next to each other
* the unique element will **not match** its neighbors

So:

* compare each element with left and right neighbors

---

### Algorithm

1. If array size is `1`, return the element
2. Traverse the array:

   * If index = `0`, compare with next
   * If index = `n-1`, compare with previous
   * Otherwise, compare with both neighbors
3. If current element is different → it is the answer

---

### Code (C++)

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) return arr[0];

        for (int i = 0; i < n; i++) {
            if (i == 0) {
                if (arr[i] != arr[i + 1]) return arr[i];
            }
            else if (i == n - 1) {
                if (arr[i] != arr[i - 1]) return arr[i];
            }
            else {
                if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1])
                    return arr[i];
            }
        }

        return -1;
    }
};
```

---

### Complexity

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

## 4. Brute Force Approach 2 – XOR Trick

### Intuition

XOR properties:

* `a ^ a = 0`
* `a ^ 0 = a`

If we XOR all elements:

* duplicate pairs cancel out
* only the unique element remains

---

### Algorithm

1. Initialize `ans = 0`
2. XOR every element with `ans`
3. Return `ans`

---

### Code (C++)

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {
        int ans = 0;
        for (int num : arr) {
            ans ^= num;
        }
        return ans;
    }
};
```

---

### Complexity

| Metric | Value |
| ------ | ----- |
| Time   | O(N)  |
| Space  | O(1)  |

---

### Note (Interview Important)

* XOR approach is **optimal in time**
* BUT it **does not use sorted property**
* Interviewers usually expect **Binary Search solution**

---

## 5. Core Binary Search Intuition (Most Important)

### Pair Pattern in Sorted Array

Before the single element:

```
index:  0 1 | 2 3 | 4 5
values: a a | b b | c c
```

* pairs start at **even index**

After the single element:

```
index:  0 1 | 2 | 3 4 | 5 6
values: a a | x | b b | c c
```

* pairing **shifts**
* now pairs start at **odd index**

This shift helps us decide which half to discard.

---

## 6. Binary Search Rule

Let `mid` be current index.

We compare:

```
arr[mid]  vs  arr[mid ^ 1]
```

Why `mid ^ 1`?

* if `mid` is even → `mid ^ 1 = mid + 1`
* if `mid` is odd  → `mid ^ 1 = mid - 1`

### Decision

* If `arr[mid] == arr[mid ^ 1]`
  → unique element is on the **right**
* Else
  → unique element is on the **left**

---

## 7. Optimal Algorithm (Binary Search)

1. Handle edge cases:

   * array size = 1
   * unique at first index
   * unique at last index
2. Set `low = 1`, `high = n - 2`
3. While `low <= high`:

   * calculate `mid`
   * if `arr[mid]` is unique → return it
   * check pairing pattern
   * discard half accordingly
4. Return result

---

## 8. Optimal Code (C++ – Interview Standard)

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) return arr[0];
        if (arr[0] != arr[1]) return arr[0];
        if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

        int low = 1, high = n - 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) {
                return arr[mid];
            }

            if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) ||
                (mid % 2 == 1 && arr[mid] == arr[mid - 1])) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }
};
```

---

## 9. Dry Run Example

```
arr = [1,1,2,2,3,3,4,5,5]
```

Unique element = `4`

* pairing correct till index `5`
* breaks at index `6`
* binary search converges to `4`

---

## 10. Complexity Comparison

| Approach          | Time     | Space | Uses Sorted Property |
| ----------------- | -------- | ----- | -------------------- |
| Brute (neighbors) | O(N)     | O(1)  | No                   |
| XOR               | O(N)     | O(1)  | No                   |
| Binary Search     | O(log N) | O(1)  | Yes                  |

---

## 11. Common Interview Mistakes

* Forgetting boundary checks
* Wrong mid pairing logic
* Using XOR when binary search is expected
* Not explaining **why pairing shifts**

---

## 12. Final Takeaway

This problem is a **classic binary search on pattern**, not on values.

Once you understand:

* even–odd index pairing
* shift caused by unique element

The solution becomes mechanical.
