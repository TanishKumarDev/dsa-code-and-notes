# Prefix Sum — Pehle Dimaag se Samjho

## 1. Problem jo prefix sum solve karta hai

Socho tumhare paas ek array hai:

```
arr = [2, 4, 1, 3, 5]
```

Aur tumse baar-baar ye poocha ja raha hai:

* index 0 se 2 tak ka sum?
* index 1 se 4 tak ka sum?
* index 2 se 3 tak ka sum?

### Normal soch (slow)

Har query ke liye loop lagao → O(n) time
Agar queries zyada ho gayi → TLE

---

## 2. Prefix Sum ka IDEA (sirf ek line)

> **Har index tak ka total pehle se store kar lo**

Bas.
Isse zyada kuch nahi hai prefix sum.

---

## 3. Prefix sum ka matlab kya hota hai

Prefix sum array `pref` banate hain:

```
pref[i] = arr[0] + arr[1] + ... + arr[i]
```

Example:

```
arr   = [2, 4, 1, 3, 5]
pref  = [2, 6, 7, 10, 15]
```

Explanation:

* pref[0] = 2
* pref[1] = 2 + 4 = 6
* pref[2] = 2 + 4 + 1 = 7
* pref[3] = 10
* pref[4] = 15

So:

> pref[i] = start se i tak ka sum

---

## 4. Ab asli magic (range sum)

Question:
**index L se R tak ka sum kaise nikale?**

### Example:

L = 1, R = 3
Elements = `[4, 1, 3]`
Answer = 8

### Prefix sum se:

```
sum(L to R) = pref[R] - pref[L-1]
```

So:

```
pref[3] = 10
pref[0] = 2

10 - 2 = 8
```

Boom.
**O(1) time me answer**.

---

## 5. Formula yaad rakhne ka trick

> “R tak ka sum − (L−1) tak ka sum”

Bas itna yaad rakho.

---

## 6. L = 0 ka case (important confusion)

Agar L = 0 ho:

```
sum(0 to R) = pref[R]
```

Kyun?

* pref[-1] exist nahi karta
* Isliye direct pref[R]

---

## 7. Prefix sum kyun powerful hai

* Pehle ek baar O(n) ka kaam
* Phir har query O(1)

Isliye use hota hai jab:

* Range sum queries zyada ho
* Array static ho

---
*explain deeply...*

### Problem situation (bina prefix sum)

Maan lo tumhare paas ek array hai:

```
arr = [10, 20, 10, 5, 15]
```

Aur tumse baar-baar poocha ja raha hai:

* sum(0 to 2)
* sum(1 to 3)
* sum(2 to 4)

---

### Bina prefix sum ka approach (slow way)

Har query ke liye tum kya karoge?

Example: sum(1 to 3)

```
20 + 10 + 5 = 35
```

Tumhe:

* index 1 se index 3 tak loop chalana padega
* har baar naye se add karna padega

Agar array size = `n`

* Ek query ka time = **O(n)**
* Agar queries = `q`
* Total time = **O(n × q)**

#### Problem:

* Queries zyada ho gayi → program slow
* Same elements baar-baar add ho rahe hain

---

### Yahin se prefix sum ka idea aata hai

Soch aayi:

> “Same cheez baar-baar add karne ke bajaye
> kyun na pehle hi cumulative sums store kar liye jaayein?”

---

### Prefix sum ke saath approach (smart way)

Pehle **sirf ek baar** prefix sum bana lo:

```
arr       = [10, 20, 10, 5, 15]
prefixSum = [10, 30, 40, 45, 60]
```

Iska matlab:

* prefixSum[i] = sum from index 0 to i

---

### Ab queries kaise fast ho jaati hain

Example: sum(1 to 3)

```
prefixSum[3] - prefixSum[0]
= 45 - 10
= 35
```

⚡ **Sirf 2 array access + 1 subtraction**

---

### Time comparison clearly samjho

Without prefix sum:

* Har query → loop
* Time per query → **O(n)**

With prefix sum:

* Prefix banane ka time → **O(n)** (sirf ek baar)
* Har query → **O(1)**

---

### Ek real comparison

Maan lo:

* n = 1,00,000
* q = 1,00,000

Without prefix sum:

```
100000 × 100000 = 10^10 operations (TLE)
```

With prefix sum:

```
100000 (build once) + 100000 (queries)
≈ 2 × 10^5 operations (FAST)
```

---

### Isliye yeh line boli jaati hai

> Pehle ek baar O(n) ka kaam
> Phir har query O(1)

Matlab:

* Thoda sa kaam pehle
* Bahut saara kaam future me bach jaata hai

---

### Prefix sum kab use karna chahiye

Jab problem me ho:

* “range sum”
* “sum from i to j”
* “multiple queries”
* “subarray sum”

---

### One-line mental model (sabse important)

> **Prefix sum future ke liye time bachaane ka investment hai**

---

## 8. Common mistake (tumhara confusion yahin hota hai)

Galat soch:

> “Prefix sum koi algorithm hai”

Sahi soch:

> **Prefix sum ek preprocessing technique hai**

Ye DP nahi hai
Ye greedy nahi hai
Ye bas **memory me sums store karna** hai

---

## 9. Real-life analogy

Socho tum bank me ho:

* Har din ka balance likh liya (prefix sum)
* Ab pichhle 5 din me kitna kharcha hua?

  * Aaj ka balance − 5 din pehle ka balance

Exactly wahi.

---

## 10. Very simple code (sirf dekhne ke liye)

```cpp
vector<int> pref(n);
pref[0] = arr[0];

for (int i = 1; i < n; i++) {
    pref[i] = pref[i-1] + arr[i];
}
```

Range sum:

```cpp
int rangeSum(int L, int R) {
    if (L == 0) return pref[R];
    return pref[R] - pref[L-1];
}
```

---

## 11. Prefix sum kab use kare (exam/interview hint)

Use prefix sum when you see:

* “range sum”
* “sum between i and j”
* “multiple queries”
* “subarray sum”

---

## 12. One-line mental model (IMPORTANT)

> **Prefix sum = cumulative total stored once to answer future sums instantly**

---

## 13. Prefix Sum Implementation 


##### To solve the problem follow the given steps:

```
* Declare a new array prefixSum[] of the same size as the input array
* Run a for loop to traverse the input array
* For each index add the value of the current element and the previous value of the prefix sum array
```
### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
    Function: prefSum
    Purpose:
    --------
    Given an input array, this function builds and returns
    a prefix sum array.

    Prefix Sum Definition:
    ----------------------
    prefixSum[i] = sum of elements from index 0 to index i
                 = arr[0] + arr[1] + ... + arr[i]

    Why Prefix Sum?
    ---------------
    - Helps answer range sum queries in O(1) time
    - Preprocessing takes O(n)
*/
vector<int> prefSum(vector<int> &arr)
{
    // Number of elements in input array
    int n = arr.size();

    /*
        prefixSum array will store cumulative sums.
        Size is same as input array.
    */
    vector<int> prefixSum(n);

    /*
        Base case:
        prefixSum[0] stores sum till index 0,
        which is just the first element itself.
    */
    prefixSum[0] = arr[0];

    /*
        Build prefix sum array:
        At each index i,
        prefixSum[i] = sum till previous index + current element
                     = prefixSum[i-1] + arr[i]
    */
    for (int i = 1; i < n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    // Return the fully built prefix sum array
    return prefixSum;
}

int main()
{
    // Input array
    vector<int> arr = {10, 20, 10, 5, 15};

    // Generate prefix sum array
    vector<int> prefixSum = prefSum(arr);

    // Print prefix sum array
    for (auto value : prefixSum)
    {
        cout << value << " ";
    }

    return 0;
}

/*
    Time Complexity:
    ----------------
    O(n) → single loop over the array

    Space Complexity:
    -----------------
    O(n) → extra prefixSum array
*/
```

---

### Complete Dry Run (Step-by-Step, No Jumps)

#### Input array

```
arr = [10, 20, 10, 5, 15]
```

Index mapping:

```
index:  0   1   2   3   4
value: 10  20  10   5  15
```

---

#### Step 1: Initialization

```cpp
n = arr.size();  // n = 5
prefixSum = vector<int>(5);
```

prefixSum (initial state):

```
[ ?, ?, ?, ?, ? ]
```

---

#### Step 2: Base case

```cpp
prefixSum[0] = arr[0];
```

Calculation:

```
prefixSum[0] = 10
```

prefixSum now:

```
[10, ?, ?, ?, ?]
```

---

#### Step 3: Loop execution

##### i = 1

```cpp
prefixSum[1] = prefixSum[0] + arr[1];
```

Calculation:

```
prefixSum[1] = 10 + 20 = 30
```

State:

```
[10, 30, ?, ?, ?]
```

---

##### i = 2

```cpp
prefixSum[2] = prefixSum[1] + arr[2];
```

Calculation:

```
prefixSum[2] = 30 + 10 = 40
```

State:

```
[10, 30, 40, ?, ?]
```

---

##### i = 3

```cpp
prefixSum[3] = prefixSum[2] + arr[3];
```

Calculation:

```
prefixSum[3] = 40 + 5 = 45
```

State:

```
[10, 30, 40, 45, ?]
```

---

##### i = 4

```cpp
prefixSum[4] = prefixSum[3] + arr[4];
```

Calculation:

```
prefixSum[4] = 45 + 15 = 60
```

Final prefixSum:

```
[10, 30, 40, 45, 60]
```

---

#### Step 4: Output

Printed output:

```
10 30 40 45 60
```

---

##### What Each Value Represents (Important Insight)

```
prefixSum[0] = sum of arr[0..0] = 10
prefixSum[1] = sum of arr[0..1] = 30
prefixSum[2] = sum of arr[0..2] = 40
prefixSum[3] = sum of arr[0..3] = 45
prefixSum[4] = sum of arr[0..4] = 60
```

---

### Why This Works (Mental Model)

> Har index pe **pichle total me current element add kar do**

No magic.
No advanced algorithm.
Sirf **cumulative addition**.

---

### Quick Range Sum Example (Just to Connect Dots)

Sum from index **1 to 3**:

Elements:

```
20 + 10 + 5 = 35
```

Using prefix sum:

```
prefixSum[3] - prefixSum[0]
= 45 - 10
= 35
```

---

### Final One-Line Takeaway

> Prefix sum array har index tak ka total store karta hai, taaki future range sums O(1) me mil jaayein.

---


## 14.Problems
[Prefix Sum ](https://www.geeksforgeeks.org/dsa/top-problems-on-prefix-sum-technique-for-interviews/)