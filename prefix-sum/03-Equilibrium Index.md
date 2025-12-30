## 1. Problem ko zero se samjho (plain thinking)

Tumhe ek array diya hai.
Tumhe **ek aisa index `i` dhoondhna hai** jahan:

```
Left side ka sum == Right side ka sum
```

Rules:

* Left side = index `i` se pehle ke saare elements
* Right side = index `i` ke baad ke saare elements
* Agar `i = 0` → left sum = 0
* Agar `i = n-1` → right sum = 0

Agar aisa koi index mil jaaye → return index
Nahi mile → return -1

---

## 2. Example se intuition banao

```
arr = [-7, 1, 5, 2, -4, 3, 0]
```

Index 3 pe check karo:

Left:

```
-7 + 1 + 5 = -1
```

Right:

```
-4 + 3 + 0 = -1
```

Left == Right → **answer = 3**

---

## 3. Approach 1: Naive (first jo dimaag me aata hai)

### Intuition

Tum sochoge:

> “Har index ko ek baar equilibrium maan ke check kar lete hain”

Har index ke liye:

* Left sum nikaalo
* Right sum nikaalo
* Compare karo

---

### Pseudocode (Naive)

```
for i from 0 to n-1:
    leftSum = sum of arr[0 to i-1]
    rightSum = sum of arr[i+1 to n-1]
    if leftSum == rightSum:
        return i
return -1
```

---

### Code (Naive, fully commented)

```cpp
int findEquilibrium(vector<int>& arr) {
    int n = arr.size();

    // Try every index as equilibrium index
    for (int i = 0; i < n; i++) {

        int leftSum = 0;
        for (int j = 0; j < i; j++) {
            leftSum += arr[j];
        }

        int rightSum = 0;
        for (int j = i + 1; j < n; j++) {
            rightSum += arr[j];
        }

        if (leftSum == rightSum)
            return i;
    }

    return -1;
}
```

---

### Time & Space

* Time: **O(n²)**
* Space: **O(1)**

Problem: same sums baar-baar calculate ho rahe hain.

---

## 4. Approach 2: Prefix Sum + Suffix Sum Arrays

### Intuition (upgrade thinking)

Yahan soch badalti hai:

> “Same sums baar-baar kyu nikalu?
> Ek baar sab prefix aur suffix sum store kar leta hoon.”

---

### Prefix & Suffix ka matlab

* `pref[i]` = sum from `0 to i`
* `suff[i]` = sum from `i to n-1`

Agar kisi index `i` pe:

```
pref[i] == suff[i]
```

→ equilibrium index

---

### Pseudocode

```
build prefix array
build suffix array

for each index i:
    if pref[i] == suff[i]:
        return i
return -1
```

---

### Code (Prefix + Suffix Array)

```cpp
int findEquilibrium(vector<int>& arr) {
    int n = arr.size();

    vector<int> pref(n), suff(n);

    // Prefix sum
    pref[0] = arr[0];
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + arr[i];
    }

    // Suffix sum
    suff[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suff[i] = suff[i + 1] + arr[i];
    }

    // Check equilibrium
    for (int i = 0; i < n; i++) {
        if (pref[i] == suff[i])
            return i;
    }

    return -1;
}
```

---

### Time & Space

* Time: **O(n)**
* Space: **O(n)** (extra arrays)

---

## 5. Approach 3: Expected / Best (Running Prefix Sum)

### Core intuition (most important)

Total sum ko ek baar nikaal lo.

For any index `i`:

```
Right sum = totalSum - leftSum - arr[i]
```

Agar:

```
leftSum == rightSum
```

→ equilibrium mil gaya

---

### Formula intuition (yaad rakhne layak)

```
left + current + right = total
right = total - left - current
```

---

### Pseudocode

```
total = sum of array
leftSum = 0

for i from 0 to n-1:
    rightSum = total - leftSum - arr[i]
    if leftSum == rightSum:
        return i
    leftSum += arr[i]

return -1
```

---

### Code (Best, O(1) space, fully commented)

```cpp
int equilibriumPoint(vector<int>& arr) {
    int total = 0;

    // Step 1: total sum
    for (int x : arr) {
        total += x;
    }

    int leftSum = 0;

    // Step 2: move pivot
    for (int i = 0; i < arr.size(); i++) {

        int rightSum = total - leftSum - arr[i];

        if (leftSum == rightSum)
            return i;

        leftSum += arr[i];
    }

    return -1;
}
```

---

## 6. Complete Dry Run (Best Approach)

```
arr = [-7, 1, 5, 2, -4, 3, 0]
total = 0
```

Calculate total:

```
total = 0
```

### i = 0

```
left = 0
right = total - left - arr[0] = 0 - 0 - (-7) = 7
not equal
left = -7
```

### i = 1

```
left = -7
right = 0 - (-7) - 1 = 6
not equal
left = -6
```

### i = 2

```
left = -6
right = 0 - (-6) - 5 = 1
not equal
left = -1
```

### i = 3

```
left = -1
right = 0 - (-1) - 2 = -1
equal → answer = 3
```

---

## 7. Time & Space Comparison (final clarity)

* Naive:

  * Time: O(n²)
  * Space: O(1)

* Prefix + Suffix array:

  * Time: O(n)
  * Space: O(n)

* Running prefix (best):

  * Time: **O(n)**
  * Space: **O(1)**

---

## 8. Final mental model (most important)

> Equilibrium index problem =
> **Left sum ko chalao, right sum ko formula se nikaalo**

Is problem ka core:

* Prefix sum thinking
* Boundary cases (start, end)
* One-pass optimization

---

## 9. Interview one-liner

> “I compute the total sum first, then iterate while maintaining a running left sum. At each index, right sum is total minus left sum and current element. If both sides match, that index is the equilibrium point.”

---