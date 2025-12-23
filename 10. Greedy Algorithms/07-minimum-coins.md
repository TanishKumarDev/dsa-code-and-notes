# FIND MINIMUM NUMBER OF COINS (INDIAN CURRENCY) — GREEDY

---

## What We Covered Here

1. Clear problem statement (what is given, what is asked)
2. Simple real-life intuition
3. Why this looks like DP at first
4. Why DP is unnecessary here
5. Core greedy observation (MOST IMPORTANT)
6. Why Indian currency is special (why greedy works)
7. Greedy approach (step-by-step thinking)
8. Detailed dry runs (multiple examples)
9. C++ implementation

   * V1: required function
   * V2: full program with `main()` + deep comments
10. JavaScript implementation

    * V1
    * V2 with example run
11. Time & Space complexity (deep explanation)
12. Common beginner mistakes
13. Interview-level Q&A
14. One-line greedy takeaway (lock this)

---

## 1. Problem Statement (VERY CLEAR)

You are given:

```
V = total amount (in rupees)
```

You also have **infinite supply** of Indian currency denominations:

```
{1, 2, 5, 10, 20, 50, 100, 500, 1000}
```

---

### Rules

1. You can use **any denomination any number of times**
2. Order does not matter
3. You must form **exactly V**

---

### Goal (What is asked?)

> **Find the minimum number of coins/notes required to make amount V**

Not:

* list all combinations
* maximize number of coins
  Only **minimum count** matters.

---

## 2. Example (Input → Output Understanding)

### Example 1

```
V = 70
```

Output:

```
2
```

Explanation:

```
50 + 20 = 70
```

Only **2 notes**, which is minimum.

---

### Example 2

```
V = 121
```

Output:

```
3
```

Explanation:

```
100 + 20 + 1 = 121
```

---

## 3. Simple Real-Life Intuition (Before Algorithms)

Think like a human cashier:

> If amount is large, you first give the **largest possible note**.

You will **never** give:

```
70 = 20 + 20 + 20 + 10
```

when:

```
70 = 50 + 20
```

This intuition is **greedy**.

---

## 4. Why This Looks Like DP at First

Your brain may think:

* For amount V
* Try using each coin
* Take minimum among all possibilities

This is similar to **Coin Change DP problem**.

Yes, DP works.

But…

---

## 5. Why DP Is NOT Required Here

Important observation:

> **Indian currency is designed such that greedy always works.**

This is NOT true for all coin systems.

Example where greedy fails (NOT Indian currency):

```
coins = {1, 3, 4}, V = 6
Greedy → 4 + 1 + 1 (3 coins)
Optimal → 3 + 3 (2 coins)
```

But Indian currency **guarantees greedy correctness**.

---

## 6. Core Greedy Observation (MOST IMPORTANT)

Read slowly:

> **Always use the largest denomination possible
> that does not exceed the remaining amount.**

Why this is safe here:

* Larger notes reduce value faster
* Smaller notes are only useful when large notes don’t fit
* No future combination can beat taking a larger note first

This satisfies the **greedy choice property**.

---

## 7. Why Sorting / Order Matters

Given denominations:

```
{1, 2, 5, 10, 20, 50, 100, 500, 1000}
```

We must process them:

```
from largest → smallest
```

Because:

* Large notes first minimize count
* Small notes fill leftover amount

---

## 8. Greedy Approach (Step-by-Step Thinking)

1. Start from **largest denomination**
2. While denomination ≤ remaining amount:

   * take that coin
   * subtract from V
3. Move to next smaller denomination
4. Stop when V becomes 0

No backtracking.
No reconsideration.
Pure greedy.

---

## 9. Greedy Pseudocode (VERY CLEAR)

```
coins = [1,2,5,10,20,50,100,500,1000]
ans = empty list

for i from last coin to first:
    while V >= coins[i]:
        V = V - coins[i]
        add coins[i] to ans

return ans
```

---

## 10. Dry Runs (VERY IMPORTANT)

### Dry Run 1

```
V = 49
```

Start from 1000 → skip
500 → skip
100 → skip
50 → skip
20 → take → V = 29
20 → take → V = 9
10 → skip
5 → take → V = 4
2 → take → V = 2
2 → take → V = 0

Coins used:

```
20, 20, 5, 2, 2
```

Count = **5**

---

### Dry Run 2

```
V = 121
```

Steps:

```
100 → V = 21
20  → V = 1
1   → V = 0
```

Coins:

```
100, 20, 1
```

Count = **3**

---

### Dry Run 3 (Edge Case)

```
V = 0
```

Result:

```
0 coins
```

---

## 11. C++ Implementation

---

### V1 — Required Function Only

```cpp
vector<int> minCoins(int V) {
    int coins[] = {1,2,5,10,20,50,100,500,1000};
    int n = 9;

    vector<int> ans;

    for (int i = n - 1; i >= 0; i--) {
        while (V >= coins[i]) {
            V -= coins[i];
            ans.push_back(coins[i]);
        }
    }
    return ans;
}
```

---

### V2 — Full Program with `main()` (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to find minimum coins
vector<int> minCoins(int V) {

    // Indian currency denominations
    int coins[] = {1,2,5,10,20,50,100,500,1000};
    int n = 9;

    vector<int> result;

    // Start from largest denomination
    for (int i = n - 1; i >= 0; i--) {

        // Take as many coins[i] as possible
        while (V >= coins[i]) {
            V -= coins[i];
            result.push_back(coins[i]);
        }
    }

    return result;
}

int main() {
    int V = 121;

    vector<int> ans = minCoins(V);

    cout << "Minimum number of coins = " << ans.size() << endl;
    cout << "Coins used: ";

    for (int coin : ans) {
        cout << coin << " ";
    }

    cout << endl;
    return 0;
}
```

---

## 12. JavaScript Implementation

---

### V1 — Function Only

```javascript
function minCoins(V) {
    let coins = [1,2,5,10,20,50,100,500,1000];
    let result = [];

    for (let i = coins.length - 1; i >= 0; i--) {
        while (V >= coins[i]) {
            V -= coins[i];
            result.push(coins[i]);
        }
    }
    return result;
}
```

---

### V2 — With Example Run

```javascript
function minCoins(V) {
    let coins = [1,2,5,10,20,50,100,500,1000];
    let result = [];

    for (let i = coins.length - 1; i >= 0; i--) {
        while (V >= coins[i]) {
            V -= coins[i];
            result.push(coins[i]);
        }
    }
    return result;
}

// Example
let V = 70;
let ans = minCoins(V);

console.log("Minimum coins:", ans.length);
console.log("Coins used:", ans);
```

---

## 13. Time & Space Complexity (Deep Explanation)

### Time Complexity

Worst case:

```
V = 1 + 1 + 1 + ... (V times)
```

So:

```
O(V)
```

---

### Space Complexity

Worst case:

```
All coins are 1
→ result array size = V
```

So:

```
O(V)
```

---

## 14. Common Beginner Mistakes

1. Trying DP for Indian currency
2. Starting from smallest coin
3. Forgetting infinite supply
4. Thinking greedy works for all coin systems
5. Not explaining **why greedy works**

---

## 15. Interview-Level Q&A

**Q: Why greedy works here?**
Because Indian currency denominations are canonical.

**Q: Does greedy always work for coin change?**
No. Only for specific coin systems.

**Q: What if denominations change?**
Then DP may be required.

---

## 16. One-Line Greedy Rule (LOCK THIS)

> **Always pick the largest denomination possible at each step.**
