# Search Element in a Rotated Sorted Array

(Binary Search on Modified Sorted Structure)

---

## 1. Problem Restated (Very Simply)

You are given:

* a **sorted array**
* then it was **rotated at some unknown index**
* **all elements are distinct**
* you are given a target `k`

Your task:

* return the **index of `k`**
* if not present → return `-1`

---

## 2. Why Normal Binary Search Fails Directly

Normal Binary Search assumes:

```
Entire array is sorted
```

But here:

```
Array is sorted → then rotated
```

Example:

```
Original: [0,1,2,4,5,6,7]
Rotated : [4,5,6,7,0,1,2]
```

So:

* left half may be sorted
* or right half may be sorted
* **but never both unsorted**

This single property is the key.

---

## 3. Core Observation (MOST IMPORTANT)

> **In a rotated sorted array, at any index `mid`,
> at least ONE side (left or right) is always sorted.**

This is guaranteed because:

* array was originally sorted
* rotation only breaks it once

So every time:

* either `low → mid` is sorted
* or `mid → high` is sorted

Binary search still works — we just need to **detect the sorted side**.

---

## 4. Binary Search Thinking (Your Style)

We do **not** find pivot first.

We directly search the target.

At every step:

1. Check `mid`
2. Identify which side is sorted
3. Decide whether target lies in that sorted side
4. Eliminate half

Exactly like:

* Ship capacity
* Koko bananas
* Smallest divisor
* Bouquet problem

Same elimination logic.

---

## 5. How to Detect the Sorted Side

### Case 1: Left side is sorted

Condition:

```cpp
nums[low] <= nums[mid]
```

Means:

```
low -------- mid   (sorted)
```

Now check:

```text
Is target in [nums[low], nums[mid]) ?
```

If YES → go left
If NO  → go right

---

### Case 2: Right side is sorted

Otherwise:

```cpp
nums[mid] <= nums[high]
```

Means:

```
mid -------- high   (sorted)
```

Now check:

```text
Is target in (nums[mid], nums[high]] ?
```

If YES → go right
If NO  → go left

---

## 6. Full Decision Table (Very Important)

| Condition                | Meaning              | Action             |
| ------------------------ | -------------------- | ------------------ |
| `nums[mid] == k`         | target found         | return mid         |
| `nums[low] <= nums[mid]` | left sorted          | check target range |
| target in left range     | safe to search left  | `high = mid-1`     |
| target not in left       | must be right        | `low = mid+1`      |
| else                     | right sorted         | check target range |
| target in right range    | safe to search right | `low = mid+1`      |
| target not in right      | must be left         | `high = mid-1`     |

---

## 7. Dry Run (Your Way)

```
nums = [4,5,6,7,0,1,2]
k = 0
```

### Step 1

```
low = 0, high = 6
mid = 3 → nums[mid] = 7
```

Left sorted?

```
nums[low]=4 <= 7 → YES
```

Is `0` in `[4,7)` ?
NO → discard left

```
low = mid+1 = 4
```

---

### Step 2

```
low = 4, high = 6
mid = 5 → nums[mid] = 1
```

Left sorted?

```
nums[4]=0 <= 1 → YES
```

Is `0` in `[0,1)` ?
YES → go left

```
high = mid-1 = 4
```

---

### Step 3

```
low = 4, high = 4
mid = 4 → nums[mid] = 0
```

Found → return `4`

---

## 8. Final C++ Code (Interview Perfect)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Case 1: Found
            if (nums[mid] == target)
                return mid;

            // Case 2: Left half is sorted
            if (nums[low] <= nums[mid]) {

                // Target lies in left half
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // Case 3: Right half is sorted
            else {

                // Target lies in right half
                if (nums[mid] < target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }
};
```

---

## 9. Complexity Analysis

| Metric | Value      |
| ------ | ---------- |
| Time   | `O(log n)` |
| Space  | `O(1)`     |

---

## 10. Interview Notes (Say This)

* Rotated sorted array → binary search still works
* At every step, **one side is guaranteed sorted**
* Identify sorted side
* Check if target lies in that range
* Eliminate half

This is **binary search on structure**, not on values.

---

## 11. Common Mistakes (Avoid)

1. Trying to find pivot first (unnecessary)
2. Forgetting equality in comparisons
3. Mixing `<=` and `<` incorrectly
4. Assuming both sides sorted (never happens)

---