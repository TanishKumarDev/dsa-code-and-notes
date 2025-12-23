# FRACTIONAL KNAPSACK (GREEDY)

---

## What We Covered Here

1. Problem statement (what is given, what is asked)
2. Real-life intuition (before algorithms)
3. Why brute force / DP seems possible
4. Why DP is unnecessary here
5. Core greedy observation (MOST IMPORTANT)
6. Greedy strategy (value / weight ratio)
7. Step-by-step dry runs (multiple examples)
8. C++ implementation

   * V1: required function
   * V2: full program with `main()` + deep comments
9. JavaScript implementation

   * V1
   * V2 with example run
10. Time & Space complexity (deep explanation)
11. Common mistakes
12. Interview-level Q&A
13. One-line greedy takeaway (lock this)

---

## 1. Problem Statement (VERY CLEAR)

You are given:

### 1️⃣ Items

For each item `i`:

* `value[i]` → value of item
* `weight[i]` → weight of item

Example:

```
value  = [60, 100, 120]
weight = [10, 20, 30]
```

---

### 2️⃣ Knapsack Capacity

```
capacity = W
```

Example:

```
W = 50
```

---

### 3️⃣ Important Rule (THIS CHANGES EVERYTHING)

> You are allowed to **take fractions of an item**.

Meaning:

* You can take full item
* OR take part of an item

This is **NOT** 0/1 Knapsack.

---

### Goal (What is asked?)

> **Maximize total value inside the knapsack
> without exceeding capacity**

---

## 2. Example (Input → Output Understanding)

### Example 1

```
value  = [60, 100, 120]
weight = [10, 20, 30]
W = 50
```

Output:

```
240.000000
```

### Why?

* Take item 0 fully → (10 weight, 60 value)
* Take item 1 fully → (20 weight, 100 value)
* Remaining capacity = 50 − 30 = 20
* Take 20/30 of item 2 → value = 120 × (20/30) = 80

Total value:

```
60 + 100 + 80 = 240
```

---

## 3. Real-Life Intuition (Before Algorithms)

Imagine:

* You have a bag of limited weight
* You are allowed to **cut items**
* You want **maximum money**

Common sense says:

> Take items that give **maximum value per unit weight** first.

This intuition is the key.

---

## 4. Why This Looks Like DP / Brute Force First

Your brain thinks:

* For each item:

  * take full
  * take partial
  * skip

That creates **choices** → DP feeling.

Yes, DP can solve it.

But…

---

## 5. Why DP Is Unnecessary Here

Because:

* Items are **divisible**
* We don’t need to explore combinations
* There exists a **clear safe greedy choice**

This is where greedy becomes perfect.

---

## 6. Core Greedy Observation (MOST IMPORTANT)

> **Always take the item with the highest
> value / weight ratio first.**

Why this works:

* It gives maximum value for each unit of weight
* Since items are divisible, no future restriction happens
* Taking best ratio early can never hurt optimality

This is the **greedy choice property**.

---

## 7. Greedy Strategy (Step-by-Step Thinking)

1. For every item, compute:

   ```
   ratio = value / weight
   ```
2. Sort items by **descending ratio**
3. Start filling knapsack:

   * If item fits fully → take it
   * Else → take required fraction and stop

Once knapsack is full → done.

---

## 8. Greedy Pseudocode (Very Clear)

```
sort items by (value / weight) descending

currentWeight = 0
totalValue = 0

for each item:
    if currentWeight + item.weight <= W:
        take full item
        currentWeight += item.weight
        totalValue += item.value
    else:
        remaining = W - currentWeight
        totalValue += item.value * (remaining / item.weight)
        break

return totalValue
```

---

## 9. Dry Run (DETAILED)

### Example

```
value  = [60, 100, 120]
weight = [10, 20, 30]
W = 50
```

### Step 1: Compute ratios

| Item | Value | Weight | Ratio |
| ---- | ----- | ------ | ----- |
| 0    | 60    | 10     | 6.0   |
| 1    | 100   | 20     | 5.0   |
| 2    | 120   | 30     | 4.0   |

Sorted order: **0 → 1 → 2**

---

### Step 2: Fill knapsack

| Step | Item | Action | Weight Used | Value Added | Total Value |
| ---- | ---- | ------ | ----------- | ----------- | ----------- |
| 1    | 0    | full   | 10          | 60          | 60          |
| 2    | 1    | full   | 30          | 100         | 160         |
| 3    | 2    | 20/30  | 50          | 80          | 240         |

Answer = **240**

---

## 10. C++ Code — Greedy

### V1: Required Function Only

```cpp
double fractionalKnapsack(int W, vector<int>& val, vector<int>& wt) {
    int n = val.size();

    vector<pair<double, pair<int, int>>> items;
    for (int i = 0; i < n; i++) {
        double ratio = (double)val[i] / wt[i];
        items.push_back({ratio, {val[i], wt[i]}});
    }

    sort(items.begin(), items.end(), greater<>());

    int curWeight = 0;
    double totalValue = 0.0;

    for (auto& item : items) {
        int value = item.second.first;
        int weight = item.second.second;

        if (curWeight + weight <= W) {
            curWeight += weight;
            totalValue += value;
        } else {
            int remain = W - curWeight;
            totalValue += value * ((double)remain / weight);
            break;
        }
    }

    return totalValue;
}
```

---

### V2: Full Program with `main()` (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double fractionalKnapsack(int W, vector<int>& val, vector<int>& wt) {

        int n = val.size();

        // Store items as (ratio, value, weight)
        vector<pair<double, pair<int, int>>> items;

        for (int i = 0; i < n; i++) {
            double ratio = (double)val[i] / wt[i];
            items.push_back({ratio, {val[i], wt[i]}});
        }

        // Sort items by descending value/weight ratio
        sort(items.begin(), items.end(), greater<>());

        int currentWeight = 0;
        double totalValue = 0.0;

        // Fill the knapsack greedily
        for (auto& item : items) {
            int value = item.second.first;
            int weight = item.second.second;

            if (currentWeight + weight <= W) {
                // Take full item
                currentWeight += weight;
                totalValue += value;
            } else {
                // Take fraction of item
                int remaining = W - currentWeight;
                totalValue += value * ((double)remaining / weight);
                break; // knapsack is full
            }
        }

        return totalValue;
    }
};

int main() {
    vector<int> value = {60, 100, 120};
    vector<int> weight = {10, 20, 30};
    int W = 50;

    Solution obj;
    double ans = obj.fractionalKnapsack(W, value, weight);

    cout << fixed << setprecision(2);
    cout << "Maximum value = " << ans << endl;

    return 0;
}
```

---

## 11. JavaScript Code

### V1

```javascript
function fractionalKnapsack(W, val, wt) {
    let items = [];

    for (let i = 0; i < val.length; i++) {
        items.push({
            ratio: val[i] / wt[i],
            value: val[i],
            weight: wt[i]
        });
    }

    items.sort((a, b) => b.ratio - a.ratio);

    let curWeight = 0;
    let totalValue = 0;

    for (let item of items) {
        if (curWeight + item.weight <= W) {
            curWeight += item.weight;
            totalValue += item.value;
        } else {
            let remain = W - curWeight;
            totalValue += item.value * (remain / item.weight);
            break;
        }
    }

    return totalValue;
}
```

---

### V2 (With Example Run)

```javascript
function fractionalKnapsack(W, val, wt) {
    let items = [];

    for (let i = 0; i < val.length; i++) {
        items.push({
            ratio: val[i] / wt[i],
            value: val[i],
            weight: wt[i]
        });
    }

    items.sort((a, b) => b.ratio - a.ratio);

    let currentWeight = 0;
    let totalValue = 0;

    for (let item of items) {
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            let remaining = W - currentWeight;
            totalValue += item.value * (remaining / item.weight);
            break;
        }
    }

    return totalValue;
}

// Example
let value = [60, 100, 120];
let weight = [10, 20, 30];
let W = 50;

console.log(fractionalKnapsack(W, value, weight)); // 240
```

---

## 12. Time & Space Complexity (Deep)

### Time Complexity

* Sorting items: `O(n log n)`
* One pass through items: `O(n)`

Total:

```
O(n log n)
```

---

### Space Complexity

* Extra list of items
* No DP table

```
O(n)
```

---

## 13. Common Mistakes

1. Solving like 0/1 knapsack
2. Not sorting by ratio
3. Sorting by value only
4. Forgetting fractional part
5. Using DP unnecessarily

---

## 14. Interview-Level Q&A

**Q: Why greedy works here?**
Because items are divisible and ratio-based choice is safe.

**Q: Why DP not needed?**
No overlapping subproblem dependency after greedy choice.

**Q: Does greedy always work for knapsack?**
Only for **fractional**, not for **0/1 knapsack**.

---

## 15. One-Line Greedy Rule (LOCK THIS)

> **When items are divisible, always take the highest value-per-weight item first.**
