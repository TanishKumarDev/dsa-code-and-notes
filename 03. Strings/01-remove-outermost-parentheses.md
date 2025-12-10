# Remove Outermost Parentheses

---

## 1. Problem Statement

**English**:
You are given a valid parentheses string `s` (only `'('` and `')'`), which is made by concatenating **one or more primitive parentheses strings**.

A **primitive** parentheses string is:

* Non-empty
* Valid
* And it cannot be split into two non-empty valid parentheses strings

Your task:
From each primitive substring, **remove its outermost pair of parentheses**, and return the final resulting string.

**Hinglish**:
String `s` mein bohot saare valid brackets hain, jo primitive parts mein bane hue hain.
Har primitive part ka **bahar wala outer bracket pair** hatao, aur jo beech ka content bache, sabko jod kar ek final string return karo.

---

## 2. Input / Output / Constraints

**Input**: String `s`

* Only `'('` and `')'`
* `1 ≤ |s| ≤ 10^5`
* `s` is guaranteed to be a valid parentheses string

**Output**:
String after removing outermost parentheses of each primitive component.

---

## 3. Examples

### Example 1

Input:
`s = "(()())(())"`

Explanation:

* Primitive 1: `"(()())"` → outermost: `(` and `)` → remove → `"()()"`
* Primitive 2: `"(())"` → outermost: `(` and `)` → remove → `"()"`

Final string = `"()()" + "()" = "()()()"`

Output:
`"()()()"`

---

### Example 2

Input:
`s = "(()())(())(()(()))"`

Primitives:

* `"(()())"` → `"()()"`
* `"(())"` → `"()"`
* `"(()(()))"` → `"()(())"`

Final string = `"()()" + "()" + "()(())" = "()()()()(())"`

Output:
`"()()()()(())"`

---

### Example 3

Input:
`s = "()()"`

Primitives:

* `"()"` → remove outermost → `""`
* `"()"` → remove outermost → `""`

Final string = `"" + "" = ""`

Output:
`""` (empty string)

---

## 4. Intuition & Core Thinking

Think about **depth / nesting level** of brackets.

* When you see `'('`, depth increases
* When you see `')'`, depth decreases

For each **primitive**, the **first '(' that makes depth from 0 → 1** is the **outermost opening**.
The **')' that makes depth from 1 → 0** is the **outermost closing**.

We want to:

* **Skip** those outermost parentheses
* **Keep everything** in between (where depth > 1 or after first)

So we can simulate depth:

* Scan from left to right
* Maintain a `balance` / `depth` variable
* Add character to answer only if it is **not** the outermost pair

Key idea (super important):

* For `'('`:

  * If current `balance > 0`, then this `'('` is **not outermost** → keep it
  * Then increase `balance++`
* For `')'`:

  * First decrease `balance--`
  * If new `balance > 0`, then this `')'` is **not outermost** → keep it

That’s it.

---

## 5. Approach (Optimal – O(n) Time, O(n) Space)

We don’t need any extra complex data structure; just a counter.

### Why this works?

* `balance` tracks **how deep inside** we are:

  * `balance == 0` → we are **outside** any primitive or just at boundary
  * `balance >= 1` → **inside** a primitive
* Outer pair is the pair that touches `balance` = 0 ↔ 1

---

## 6. Algorithm (Step-by-step)

1. Initialize:

   * `balance = 0`
   * `result = ""`
2. Loop over each character `ch` in string `s`:

   * If `ch == '('`:

     * If `balance > 0`:
       → append `'('` to result (this is not outermost)
     * `balance++`
   * Else (`ch == ')'`):

     * `balance--`
     * If `balance > 0`:
       → append `')'` to result (this is not outermost)
3. At the end, return `result`.

---

## 7. Dry Run

### s = "(()())(())"

Let’s go char by char:

* Start: `balance = 0`, `res = ""`

1. `(`:

   * `balance = 0` → outermost opening → do NOT add
   * `balance = 1`
2. `(`:

   * `balance = 1` > 0 → add `'('` → `res = "("`
   * `balance = 2`
3. `)`:

   * `balance = 2 → 1`
   * now `balance = 1` > 0 → add `')'` → `res = "()"`
4. `(`:

   * `balance = 1` > 0 → add `'('` → `res = "()("`
   * `balance = 2`
5. `)`:

   * `balance = 2 → 1`
   * `balance = 1` > 0 → add `')'` → `res = "()()"`
6. `)`:

   * `balance = 1 → 0`
   * `balance = 0` → outermost closing → do NOT add

Now primitive 1 is done.

7. `(`:

   * `balance = 0` → outermost opening → don’t add
   * `balance = 1`
8. `(`:

   * `balance = 1` > 0 → add `'('` → `res = "()()("`
   * `balance = 2`
9. `)`:

   * `balance = 2 → 1`
   * `balance = 1` > 0 → add `')'` → `res = "()()()"`
10. `)`:

    * `balance = 1 → 0`
    * `balance = 0` → outermost closing → don’t add

End → `res = "()()()"`

Correct.

---

## 8. C++ Code (with line-by-line comments)

```cpp
// 01-remove-outermost-parentheses.cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        // 'balance' will track current depth of parentheses.
        // balance == 0  -> we are outside any current primitive.
        // balance >= 1  -> we are inside some primitive.
        int balance = 0;

        // Result string to store answer.
        string result;

        // Traverse each character in the input string.
        for (char ch : s) {
            if (ch == '(') {
                // If balance > 0, means we are already inside
                // some primitive, so this '(' is NOT the outermost.
                // Hence, we should keep it.
                if (balance > 0) {
                    result.push_back(ch);
                }

                // Now we go one level deeper.
                balance++;
            } else {
                // For ')', we first move one level back (decrease depth).
                balance--;

                // After decreasing, if balance > 0,
                // this ')' is not closing the outermost primitive.
                // So we should keep it.
                if (balance > 0) {
                    result.push_back(ch);
                }
            }
        }

        // Finally, 'result' contains the string with
        // all outermost parentheses removed.
        return result;
    }
};

// You can use this main for quick local testing.
int main() {
    Solution sol;

    cout << sol.removeOuterParentheses("(()())(())") << endl;           // Output: ()()()
    cout << sol.removeOuterParentheses("(()())(())(()(()))") << endl;   // Output: ()()()()(())
    cout << sol.removeOuterParentheses("()()") << endl;                 // Output: (empty line)

    return 0;
}
```

---

## 9. JavaScript Code (with clear comments)

```javascript
// 01-remove-outermost-parentheses.js

/**
 * @param {string} s
 * @return {string}
 */
function removeOuterParentheses(s) {
    // balance tracks how deep we are inside parentheses.
    let balance = 0;
    let result = [];

    // Iterate over each character
    for (let ch of s) {
        if (ch === '(') {
            // If we are already inside a primitive (balance > 0),
            // then this '(' is not outermost, so we keep it.
            if (balance > 0) {
                result.push(ch);
            }
            // Go one level deeper.
            balance++;
        } else {
            // For ')', we first decrease depth.
            balance--;

            // After decreasing, if depth is still > 0,
            // this ')' is not the outermost closing, so we keep it.
            if (balance > 0) {
                result.push(ch);
            }
        }
    }

    // Join array of characters into a final string.
    return result.join('');
}

// Quick tests
console.log(removeOuterParentheses("(()())(())"));             // ()()()
console.log(removeOuterParentheses("(()())(())(()(()))"));     // ()()()()(())
console.log(removeOuterParentheses("()()"));                   // ""
```

---

## 10. Edge Cases

1. `s = "()"`

   * Single primitive, outermost removed → `""`
2. `s = "()()"`

   * Two primitives, each becomes empty → `""`
3. Nested deep: `"((()))"`

   * Primitive: `"((()))"`
   * Remove outermost → `"(())"`
4. Very long string (length up to `10^5`)

   * Our O(n) scan is fine.
5. All primitives of size 2 (`"()()()()..."`)

   * Output will be empty.

All are naturally handled by our `balance` logic.

---

## 11. Time & Space Complexity

* Time:

  * We scan the string once → **O(n)**
* Space:

  * Output string of length ≤ n → **O(n)**
  * Only using an `int` for balance → extra **O(1)**

---

## 12. Interview Discussion Points / Questions

You can use or prepare around these:

1. How do you define a **primitive** parentheses string?
2. Why is tracking **balance / depth** enough here instead of using a full stack?
3. What will happen if you mistakenly push characters **before** updating balance in both cases?
4. How would you modify the logic if the string could have **invalid** parentheses? (not guaranteed valid)
5. Is there any way to do this in-place (modifying the original string) in C++? What would be the approach?
6. Why do we treat `'('` and `')'` differently in terms of when we increase/decrease balance?
7. Can we solve this with a stack of characters? What would that look like? What’s the trade-off?
8. How would you extend this logic if the string had **multiple types of brackets** like `()[]{}`?

---
