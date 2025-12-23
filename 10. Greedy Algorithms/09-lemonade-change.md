# LEMONADE CHANGE (GREEDY)

---

## What We Covered Here

1. Clear problem statement (what is given, what is asked)
2. Very important constraints (why confusion happens)
3. Real-life lemonade stand mindset (MOST IMPORTANT)
4. Why this is a greedy problem
5. Core greedy observation (lock this)
6. Step-by-step rules for each bill (5, 10, 20)
7. Multiple dry runs (including failing cases)
8. C++ code

   * V1: function only
   * V2: full program with `main()` + deep comments
9. JavaScript code

   * V1
   * V2 with example run
10. Time & Space complexity (simple + deep)
11. Common mistakes (WHY people get confused)
12. Interview-level Q&A
13. One-line greedy takeaway

---

## 1. Problem Statement (VERY CLEAR)

You are running a **lemonade stand**.

* Price of **1 lemonade = $5**
* Customers stand in a **queue**
* Each customer pays with **one bill only**

Allowed bills:

```
5, 10, 20
```

Initially:

```
You have NO money (no change)
```

---

### What is given?

```
bills[i] = bill given by i-th customer
```

Example:

```
bills = [5, 5, 10, 20]
```

---

### What is asked?

> Can you give **correct change to every customer**, in order?

Return:

* `true` → if possible
* `false` → if at any point you fail

---

## 2. IMPORTANT RULES (WHY CONFUSION HAPPENS)

Read slowly:

1. Customers come **one by one**
2. You must give change **immediately**
3. You **cannot reorder** customers
4. You **cannot borrow money**
5. You can only use **money you already have**

This is why future planning matters.

---

## 3. Real-Life Lemonade Stand Mindset (KEY)

Think like this:

> “What cash do I have **right now** to give change?”

We don’t care about:

* total money
* future customers

Only:

```
current change in hand
```

So we track:

```
number of $5 bills
number of $10 bills
```

We **never need to track $20 bills** (why? explained later).

---

## 4. Why This Is a Greedy Problem

At each customer:

* You must make a **local decision**
* You cannot undo it later
* If you fail now → game over

This is classic greedy:

> **make the best decision at the current step**

---

## 5. Core Greedy Observation (MOST IMPORTANT)

> **Always try to save $5 bills.**

Why?

* $5 is the **only bill** that can give change for $10
* $5 is **essential** to make $15 change for $20

If you waste $5 bills early → you die later.

This single rule removes most confusion.

---

## 6. Step-by-Step Rules (NO CONFUSION ZONE)

We process customers **one by one**.

Maintain:

```
five = count of $5 bills
ten  = count of $10 bills
```

---

### Case 1: Customer pays with $5

Price = $5
Change needed = $0

Action:

```
Take the $5 bill
five++
```

Always safe. Never a problem.

---

### Case 2: Customer pays with $10

Price = $5
Change needed = $5

Action:

```
You MUST give one $5 bill
```

So:

* If `five > 0` → OK
* Else → ❌ impossible

Update:

```
five--
ten++
```

---

### Case 3: Customer pays with $20 (MOST CONFUSING)

Price = $5
Change needed = $15

Two possible ways to give $15:

#### Option A (BEST)

```
$10 + $5
```

#### Option B

```
$5 + $5 + $5
```

---

### Greedy Choice (VERY IMPORTANT)

> **Always prefer: $10 + $5**

Why?

* Saves $5 bills
* $10 is useless for $10 customers
* $5 is precious

So order is:

1. If `(ten > 0 && five > 0)` → use them
2. Else if `(five >= 3)` → use three $5
3. Else → ❌ impossible

---

## 7. Dry Runs (STEP-BY-STEP, SLOW)

---

### Example 1 (WORKS)

```
bills = [5, 5, 5, 10, 20]
```

Start:

```
five = 0, ten = 0
```

| Customer | Pays | Action    | five | ten |
| -------- | ---- | --------- | ---- | --- |
| 1        | 5    | take      | 1    | 0   |
| 2        | 5    | take      | 2    | 0   |
| 3        | 5    | take      | 3    | 0   |
| 4        | 10   | give 5    | 2    | 1   |
| 5        | 20   | give 10+5 | 1    | 0   |

All customers served → **true**

---

### Example 2 (FAILS)

```
bills = [5, 5, 10, 10, 20]
```

| Customer | Pays | five | ten | Result |
| -------- | ---- | ---- | --- | ------ |
| 1        | 5    | 1    | 0   | OK     |
| 2        | 5    | 2    | 0   | OK     |
| 3        | 10   | 1    | 1   | OK     |
| 4        | 10   | 0    | 2   | OK     |
| 5        | 20   | ❌    | ❌   | FAIL   |

Why fail?

* Need $15
* Have two $10, zero $5
* Impossible

Answer = **false**

---

### Example 3 (EDGE CASE)

```
bills = [10]
```

First customer needs $5 change
You have none → ❌ false

---

## 8. C++ Code

---

### V1 — Function Only

```cpp
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;

    for (int bill : bills) {
        if (bill == 5) {
            five++;
        }
        else if (bill == 10) {
            if (five == 0) return false;
            five--;
            ten++;
        }
        else { // bill == 20
            if (ten > 0 && five > 0) {
                ten--;
                five--;
            }
            else if (five >= 3) {
                five -= 3;
            }
            else {
                return false;
            }
        }
    }
    return true;
}
```

---

### V2 — Full Program with `main()` (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

class LemonadeStand {
public:
    bool lemonadeChange(vector<int>& bills) {

        int five = 0; // number of $5 bills
        int ten  = 0; // number of $10 bills

        for (int bill : bills) {

            // Case 1: customer pays $5
            if (bill == 5) {
                five++;
            }

            // Case 2: customer pays $10
            else if (bill == 10) {
                if (five == 0)
                    return false; // cannot give $5 change

                five--;
                ten++;
            }

            // Case 3: customer pays $20
            else {
                // Prefer $10 + $5
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                // Else use three $5
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false; // no valid change
                }
            }
        }
        return true;
    }
};

int main() {
    vector<int> bills = {5, 5, 5, 10, 20};

    LemonadeStand stand;
    bool result = stand.lemonadeChange(bills);

    if (result)
        cout << "Change can be provided to all customers.\n";
    else
        cout << "Change cannot be provided.\n";

    return 0;
}
```

---

## 9. JavaScript Code

---

### V1 — Function Only

```javascript
function lemonadeChange(bills) {
    let five = 0, ten = 0;

    for (let bill of bills) {
        if (bill === 5) {
            five++;
        } else if (bill === 10) {
            if (five === 0) return false;
            five--;
            ten++;
        } else {
            if (ten > 0 && five > 0) {
                ten--;
                five--;
            } else if (five >= 3) {
                five -= 3;
            } else {
                return false;
            }
        }
    }
    return true;
}
```

---

### V2 — With Example

```javascript
let bills = [5, 5, 10, 10, 20];
console.log(lemonadeChange(bills)); // false
```

---

## 10. Time & Space Complexity

### Time Complexity

```
O(N)
```

**Why exactly O(N)? (Not just a one-liner)**

Let:

* `N = number of customers = bills.size()`

Now look at the code behavior carefully:

```cpp
for (int bill : bills)
{
    ...
}
```

This loop:

* Iterates **once per customer**
* Each iteration performs:

  * Constant comparisons (`bill == 5`, `bill == 10`)
  * Constant updates to counters (`five--`, `ten++`, etc.)
  * No nested loops
  * No recursion
  * No revisiting any element

So total operations:

```
Work done = c1 + c2 + c3 + ... + cN
          = N * constant
```

Hence:

```
Time Complexity = O(N)
```

Important observation:

* Even the “hardest” case (`bill == 20`) still does **constant work**
* No backtracking
* No sorting
* No retries

This is why this greedy solution is optimal.

---

### Space Complexity

```
O(1)
```

**Why exactly O(1)? (Memory-level reasoning)**

Look at all extra memory used:

```cpp
int five = 0;
int ten = 0;
```

Only:

* Two integer variables
* Their size does **not depend on N**

What we do **not** use:

* No extra arrays
* No maps
* No stacks
* No recursion
* No auxiliary data structures

Even though `bills` is a vector:

* It is **input**
* Not counted as extra space

So:

```
Extra Space Used = constant
Space Complexity = O(1)
```

---

### Why This Greedy Strategy Works (One-line Insight Explained)

> **Save $5 bills whenever possible; they are your lifeline.**

Reason:

* `$5` is the **only bill** that can help you give change to:

  * `$10` (needs one `$5`)
  * `$20` (needs either `$10+$5` or `3×$5`)
* `$10` bills are **less flexible**
* `$20` bills are useless for making change

That’s why this logic is critical:

```cpp
// Prefer $10 + $5
if (ten > 0 && five > 0)
```

This preserves `$5` bills for future customers.

---

### Final Lock-in Rule (Interview Grade)

> One pass, two counters, greedy preservation of `$5` ⇒ **O(N) time, O(1) space**

---

## 11. Common Mistakes (WHY CONFUSION HAPPENS)

1. Using 3×$5 when $10+$5 is available
2. Tracking total money instead of change
3. Forgetting order matters
4. Thinking $20 bills matter
5. Not simulating step-by-step

---

## 12. Interview-Level Q&A

**Q: Why prefer $10+$5 for $20?**
To save $5 bills for future customers.

**Q: Why not track $20 bills?**
They are never used as change.

**Q: Is greedy always correct here?**
Yes, because local optimal choice is globally safe.

---

## 13. One-Line Greedy Rule (LOCK THIS)

> **Save $5 bills whenever possible; they are your lifeline.**
