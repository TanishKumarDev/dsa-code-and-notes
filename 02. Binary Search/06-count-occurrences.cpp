#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Count number of occurrences of x in a SORTED array.
If x is not present, return 0.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time: O(n), Space: O(1)
int countOccurrencesBrute(vector<int> &arr, int x)
{
    int cnt = 0;

    // Traverse entire array
    for (int num : arr)
    {
        if (num == x)
            cnt++;
    }

    return cnt;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Binary Search
// Time: O(log n), Space: O(1)

/*
Find first occurrence of x
*/
int firstOccurrence(vector<int> &arr, int x)
{
    int low = 0, high = arr.size() - 1;
    int first = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
        {
            first = mid;    // possible answer
            high = mid - 1; // move left to find earlier
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return first;
}

/*
Find last occurrence of x
*/
int lastOccurrence(vector<int> &arr, int x)
{
    int low = 0, high = arr.size() - 1;
    int last = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
        {
            last = mid;    // possible answer
            low = mid + 1; // move right to find later
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return last;
}

/*
Count occurrences using first and last index
*/
int countOccurrencesBinary(vector<int> &arr, int x)
{
    // Find the first index where x appears
    int first = firstOccurrence(arr, x);

    // If first occurrence is -1,
    // it means x never appeared in the array at all
    // so count of x is 0 → return early
    if (first == -1)
        return 0;

    // Find the last index where x appears
    int last = lastOccurrence(arr, x);

    // Total count = last index - first index + 1
    return (last - first + 1);
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: STL
// Time: O(log n)
int countOccurrencesSTL(vector<int> &arr, int x)
{
    // lower_bound gives the index of the first element
    // which is >= x (this is where x would START if it exists)
    int first = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

    // upper_bound gives the index of the first element
    // which is > x (this is where x would END + 1 if it exists)
    int last = upper_bound(arr.begin(), arr.end(), x) - arr.begin();

    // If x does not exist
    if (first == arr.size() || arr[first] != x)
        return 0;

    return last - first;
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    int x = 2;

    cout << "Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    cout << "Target: " << x << endl;

    cout << "Count (Brute Force): "
         << countOccurrencesBrute(arr, x) << endl;

    cout << "Count (Binary Search): "
         << countOccurrencesBinary(arr, x) << endl;

    cout << "Count (STL): "
         << countOccurrencesSTL(arr, x) << endl;

    return 0;
}

/*
DRY RUN EXAMPLE
---------------

## Example where element does NOT exist

### Input

```cpp
vector<int> arr = {1, 3, 4, 5};
int x = 2;
```

---

## Step-by-step dry run

### Step 1 — Call function from `main`

```cpp
int result = countOccurrencesBinary(arr, 2);
```

---

### Step 2 — Inside `countOccurrencesBinary`

```cpp
int first = firstOccurrence(arr, 2);
```

Now run `firstOccurrence(arr, 2)`:

Binary search steps:

```
arr = {1,3,4,5}
x = 2

low = 0, high = 3
mid = 1 → arr[1] = 3 > 2 → move left
high = 0

mid = 0 → arr[0] = 1 < 2 → move right
low = 1

low > high → stop
```

Result:

```cpp
first = -1
```

Because **2 never appeared**.

---

### Step 3 — Check condition

```cpp
if (first == -1)
    return 0;
```

✔ Condition is TRUE
✔ Function **returns immediately**

⛔ `lastOccurrence()` is **NOT called**
⛔ `(last - first + 1)` is **NOT calculated**

---

## Step 4 — What `main()` receives

Back in `main`:

```cpp
int result = countOccurrencesBinary(arr, 2);
```

The returned value is:

```text
result = 0
```

---

## What this means (very simple)

> Because we never saw `2` even once,
> the number of occurrences of `2` is **0**.

---

## How you would print it in `main`

```cpp
cout << result;
```

Output:

```
0
```

---

## Why returning early is IMPORTANT

If we did NOT return early:

```cpp
first = -1
last = -1
return (-1 - (-1) + 1) = 1 ❌ wrong
```

So the early return **protects correctness**.

---

## One-line intuition (lock this)

> If the element never starts, it never exists — return 0.

---

## Final summary

| Situation    | first | function returns | main gets     |
| ------------ | ----- | ---------------- | ------------- |
| x exists     | ≥ 0   | count            | correct count |
| x not exists | -1    | 0                | 0             |
*/