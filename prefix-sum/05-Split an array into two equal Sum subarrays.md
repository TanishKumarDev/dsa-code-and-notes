## 1. Problem ko bilkul base se samjho

Tumhe ek array diya hai (elements > 0).
Tumhe check karna hai:

> Kya array ko **do continuous subarrays** me split kiya ja sakta hai
> aise ki **left subarray ka sum == right subarray ka sum**

Rules:

* Order change nahi kar sakte
* Split sirf ek jagah hoga
* Agar possible ho → dono subarrays print karo
* Nahi ho → “Not Possible”

---

## 2. Example se intuition banao

Example 1:

```
arr = {1, 2, 3, 4, 5, 5}
```

Possible split:

```
Left  = {1, 2, 3, 4} → sum = 10
Right = {5, 5}       → sum = 10
```

Example 2:

```
arr = {4, 3, 2, 1}
```

No split possible → Not Possible

---

## 3. Tumhari natural (first) thinking — Naive approach

Tum naturally sochoge:

> “Har possible split point pe check kar lete hain
> left ka sum == right ka sum ya nahi”

Isme:

* Ek index `i` ko split point maan lo
* `0..i` = left part
* `i+1..n-1` = right part

---

## 4. Approach 1: Naive (Nested Loop)

## Intuition

Har index ke liye:

* Left sum calculate karo
* Right sum calculate karo
* Agar equal ho → wahi split point

Same sums baar-baar calculate ho rahe hain.

---

## Pseudocode (Naive)

```
for i from 0 to n-1:
    leftSum = sum of arr[0..i]
    rightSum = sum of arr[i+1..n-1]
    if leftSum == rightSum:
        return i+1
return -1
```

---

## Code (Naive, fully commented)

```cpp
int findSplitPoint(int arr[], int n) {
    int leftSum = 0;

    for (int i = 0; i < n; i++) {
        leftSum += arr[i];

        int rightSum = 0;
        for (int j = i + 1; j < n; j++) {
            rightSum += arr[j];
        }

        if (leftSum == rightSum)
            return i + 1; // split index
    }

    return -1;
}
```

---

## Time & Space (Naive)

* Time: **O(n²)**
* Space: **O(1)**

Problem: inefficient for large arrays.

---

## 5. Core observation (turning point)

Total sum agar **odd** hai:

```
Total sum % 2 != 0 → split impossible
```

Agar total sum **even** hai:

```
Target sum = totalSum / 2
```

Ab problem simplify ho jaati hai:

> Kya array me koi prefix hai jiska sum = target?

---

## 6. Approach 2: Efficient (Prefix Sum idea)

## Intuition

* Pehle poore array ka sum nikaalo
* Left se traverse karo
* Jaise hi leftSum == totalSum - leftSum
  → split mil gaya

Isme:

* Har element ek hi baar use hota hai
* Koi nested loop nahi

---

## Pseudocode (Efficient)

```
total = sum of array
leftSum = 0

for i from 0 to n-1:
    leftSum += arr[i]
    rightSum = total - leftSum
    if leftSum == rightSum:
        return i+1

return -1
```

---

## Code (Efficient, fully commented)

```cpp
int findSplitPoint(int arr[], int n) {
    int totalSum = 0;

    // Step 1: calculate total sum
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }

    int leftSum = 0;

    // Step 2: find split point
    for (int i = 0; i < n; i++) {
        leftSum += arr[i];

        int rightSum = totalSum - leftSum;

        if (leftSum == rightSum)
            return i + 1; // split index
    }

    return -1;
}
```

---

## 7. Printing the two subarrays

```cpp
void printTwoParts(int arr[], int n) {
    int splitPoint = findSplitPoint(arr, n);

    if (splitPoint == -1 || splitPoint == n) {
        cout << "Not Possible" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (i == splitPoint)
            cout << endl;
        cout << arr[i] << " ";
    }
}
```

---

## 8. Complete Dry Run (Efficient approach)

Input:

```
arr = {1, 2, 3, 4, 5, 5}
```

Total sum:

```
1+2+3+4+5+5 = 20
```

### i = 0

```
left = 1
right = 19
```

### i = 1

```
left = 3
right = 17
```

### i = 2

```
left = 6
right = 14
```

### i = 3

```
left = 10
right = 10  ✅
split index = 4
```

Result:

```
{1 2 3 4}
{5 5}
```

---

## 9. Time & Space Comparison

* Naive:

  * Time: O(n²)
  * Space: O(1)

* Efficient:

  * Time: **O(n)**
  * Space: **O(1)**

---

## 10. Relation with Equilibrium Index

This problem is basically:

> **Equilibrium index ka special case**
> jahan split point element khud kisi side me nahi jaata

Same core idea:

* Prefix sum
* Total sum
* One-pass solution

---

## 11. Final mental model (sabse important)

> “Jaise hi left ka sum total ka aadha ho jaaye
> wahi split point hai”

Yaad rakhne ka shortcut:

* Total nikaalo
* Left chalao
* Right = total - left

---

## 12. Interview one-liner

> “I compute the total sum and iterate while maintaining a running left sum. When left sum equals total minus left sum, I split the array at that index.”
