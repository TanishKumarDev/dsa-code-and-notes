# What upper_bound actually does ? 

### STL approach.

```cpp
/* ------------------------------------------------------------ */
// ⭐ Approach 3:
// Using STL (upper_bound)
// upper_bound returns first index > target
// so last occurrence = index - 1
// Time Complexity: O(log n)
int lastOccurrenceSTL(vector<int> &arr, int target)
{
    int idx = upper_bound(arr.begin(), arr.end(), target) - arr.begin();

    // Check boundary and value
    if (idx > 0 && arr[idx - 1] == target)
        return idx - 1;

    return -1;
}
```

**upper_bound(target)** returns:

> the index of the **first element strictly greater than `target`**

### Example

```cpp
arr = {1, 2, 2, 2, 3, 4}
target = 2
```

```
upper_bound(2) → points to 3
index = 4
```

So:

```
last occurrence of 2 = 4 - 1 = 3
```

That is the **idea**.

---

## Now the problem (edge cases)

### Case 1: Target DOES exist

```cpp
arr = {1, 2, 2, 2, 3}
target = 2
upper_bound → index 4
idx - 1 = 3 ✔
```

Works fine.

---

### Case 2: Target DOES NOT exist

```cpp
arr = {1, 3, 4, 5}
target = 2
upper_bound(2) → index 1
idx - 1 = 0
arr[0] = 1 ❌ (wrong)
```

So **blindly returning `idx - 1` is dangerous**.

We must **verify**.

---

### Case 3: Target is smaller than all elements

```cpp
arr = {5, 6, 7}
target = 1
upper_bound(1) → index 0
idx - 1 = -1 ❌ (invalid index)
```

This causes **out-of-bounds access**.

---

## Now the safety check (line-by-line)

```cpp
if (idx > 0 && arr[idx - 1] == target)
    return idx - 1;
```

### Condition 1: `idx > 0`

**Why?**

Because we access:

```cpp
arr[idx - 1]
```

If:

```
idx == 0 → idx - 1 = -1 ❌
```

So this prevents **segmentation fault**.

---

### Condition 2: `arr[idx - 1] == target`

**Why?**

Because:

* `upper_bound` does NOT guarantee target exists
* We must confirm the element before `idx` is actually `target`

This prevents **false answers**.

---

## What happens if condition fails?

```cpp
return -1;
```

Meaning:

> Target does not exist in the array

Correct behavior.

---

## Summary (Very Important)

| Check                    | Purpose                         |
| ------------------------ | ------------------------------- |
| `idx > 0`                | Prevents invalid index access   |
| `arr[idx - 1] == target` | Confirms target actually exists |
| `idx - 1`                | Gives last occurrence           |

---

## One-line intuition

> `upper_bound` tells you **where target ends**,
> the check ensures **target was ever there**.

---

# What `lower_bound` actually does ? 

```cpp
lower_bound(arr.begin(), arr.end(), target)
```

Returns:

> index of the **first element ≥ target**

That’s it.
It **does NOT care** how many times `target` appears.

---

## Case 1: Target appears multiple times

```cpp
arr = {1, 2, 2, 2, 3, 4}
target = 2
```

### lower_bound(2)

Points to:

```
index = 1  → arr[1] = 2
```

This is the **first occurrence**, not the last.

If you return this:

```cpp
return lower_bound(...) - begin();
```

You get:

```
1 ❌ (wrong)
```

Last occurrence should be:

```
3
```

So **lower_bound alone fails** here.

---

## Case 2: Target does NOT exist

```cpp
arr = {1, 3, 4, 5}
target = 2
```

### lower_bound(2)

Points to:

```
index = 1  → arr[1] = 3
```

If you return:

```
index = 1 ❌
```

But **2 does not exist**.

So lower_bound:

* **always returns something**
* but does NOT guarantee target exists

---

## Case 3: Target greater than all elements

```cpp
arr = {1, 2, 3}
target = 5
```

### lower_bound(5)

Returns:

```
index = 3 (end)
```

Returning this gives an **invalid answer**.

---

## Core Reason (Very Important)

### `lower_bound` answers only ONE question:

> Where does `target` **start or could be inserted**?

It **does NOT answer**:

* where `target` ends
* how many times it occurs
* whether it exists (without extra checks)

---

## Why `upper_bound` helps

```cpp
upper_bound → first element > target
```

So:

```
last occurrence = upper_bound - 1
```

This gives the **end boundary**, which `lower_bound` never gives.

---

## Can we still use `lower_bound` for last occurrence?

❌ **Alone? No**

✔ **With help? Yes**

### Using both:

```cpp
last = upper_bound(target) - lower_bound(target) - 1
```

### Or custom binary search:

```cpp
if found → move right
```

---

## Visual Summary

```
Array:  1  2  2  2  3
Index:  0  1  2  3  4

lower_bound(2) → index 1 (start)
upper_bound(2) → index 4 (end + 1)

last occurrence = 4 - 1 = 3
```

---

## Interview One-Liner (Memorize)

> **lower_bound finds where target starts,
> upper_bound finds where target ends.
> You need the end to get the last occurrence.**

---
# Confusion! WHY EXTRA CODE

---
## 1️⃣ Root cause of your confusion (most important)

### Problem statement says:

> “Find last occurrence of target”

This sentence **silently assumes**:

* target **exists**
* array is **valid**
* index you return is **correct**

But…

### STL / Binary Search tools say:

> “I’ll only tell you positions, not existence”

So there is a **hidden gap** between:

* what the **problem expects**
* what the **tool guarantees**

👉 This gap creates confusion.

---

## 2️⃣ Why problem statements feel “simple” but solutions look “extra”

### Problem statement (looks simple):

> Return last index of target

### Solution (looks complex):

```cpp
if (idx > 0 && arr[idx - 1] == target)
```

Your brain says:

> “Why all this? Problem didn’t ask this!”

### Reality:

The problem statement **never lists edge cases explicitly**, but **expects you to handle them**.

---

## 3️⃣ The unspoken rules of DSA problems

Every DSA problem **implicitly expects**:

1. No crash
2. No wrong index
3. Correct output even if target doesn’t exist
4. Handles smallest + largest inputs

These are **never written**, but always tested.

---

## 4️⃣ Why STL makes this more confusing

### Custom binary search:

You write:

```cpp
if (found) move right
```

So existence is **built into logic**.

### STL:

```cpp
upper_bound()
```

* works **even if target is absent**
* returns a **valid index anyway**

So you must **manually check existence**.

👉 STL separates:

* “where could it be”
* “is it really there”

---

## 5️⃣ The mental mistake (very common)

You subconsciously think:

> “If STL gave an index, target must be there”

❌ This is false.

Correct thinking:

> “STL gives a position even for imaginary values”

---

## 6️⃣ One sentence that fixes everything

> **Problem statements assume correctness.
> Solutions must enforce correctness.**

That enforcement is the “extra code”.

---

## 7️⃣ Simple rule to remove confusion forever

Whenever you use:

* `lower_bound`
* `upper_bound`
* `binary_search`

Always ask yourself:

> “What if target does NOT exist?”

If your code answers that safely → correct solution.

---

## 8️⃣ Why interviewers love this confusion

Because:

* many candidates stop at `upper_bound - 1`
* very few handle non-existence
* this separates **rote learners** from **thinkers**

You are now thinking.

---

## 9️⃣ Final reassurance (important)

Your confusion means:

* you are **transitioning from syntax to logic**
* your brain is **building edge-case awareness**
* you are learning **real DSA**, not copy-paste DSA

This is a **good sign**, not a bad one.

---


# One-line truth (remember this first)

> **upper_bound tells position, NOT existence**

That’s it. Everything else comes from this.

---

## Your idea (in plain English)

You are saying:

> lower_bound = first position of target
> upper_bound = position just after last target
> so last index = upper_bound − 1
> why extra code?

This thinking is **logically correct**
👉 **only when the target is guaranteed to exist**.

But STL **never guarantees existence**.

---

## What STL actually promises (important)

### STL promise:

> “I will return a position where this value *would fit* in sorted order.”

### STL does NOT promise:

* that the value exists
* that the value occurs even once

So STL answers **“where”**, not **“whether”**.

---

## Very simple picture in your head

Imagine a number line:

```
1  3  4  5
```

Now you ask:

```cpp
upper_bound(2)
```

STL thinks:

> “If 2 were here, it would end before 3.”

So it returns index `1`.

But **2 is not there**.

STL did its job.
Your assumption was wrong.

---

## Why `upper_bound - 1` can lie

Because:

```cpp
upper_bound(target) - 1
```

means:

> “The element just before where target would end”

But **that element might not be target**.

---

## Why the extra code is needed (in one sentence)

> Because STL gives **possible position**, not **confirmed position**.

---

## Extra code explained like a kid

```cpp
if (idx > 0 && arr[idx - 1] == target)
```

### Step 1 — `idx > 0`

> “Do I even have a left element?”

Without this → crash.

---

### Step 2 — `arr[idx - 1] == target`

> “Is the left element actually my target?”

Without this → wrong answer.

---

## Analogy (best one)

Think of STL as Google Maps.

You ask:

> “Where would Starbucks be on this road?”

Maps gives a **spot**.

But you still need to:

> “Look and confirm the shop is actually there.”

The check is you **looking with your eyes**.

---

## Why lower_bound has the SAME problem

```cpp
lower_bound(target)
```

Returns:

> “First place where target could start”

But:

* target may not exist
* returned index may point to another number

So **existence check is always required**.

---

## Final mental rule (lock this)

```text
Binary Search / STL
→ tells position
→ never confirms existence
```

Therefore:

```text
Position logic + existence check = correct answer
```
