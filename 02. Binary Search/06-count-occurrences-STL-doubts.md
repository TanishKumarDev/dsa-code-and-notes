## What you are confused about

This line:

```cpp
lower_bound(arr.begin(), arr.end(), x) - arr.begin();
```

You are asking:

> “Why `- arr.begin()`?
> lower_bound already gives something, right?”

---

## What `lower_bound` actually returns

❗ **Important**: `lower_bound` does **NOT** return an index.

It returns an **iterator** (pointer-like thing).

Example:

```cpp
vector<int>::iterator it = lower_bound(...);
```

`it` points to **some element inside the vector**.

---

## Why we subtract `arr.begin()`

Because:

* `arr.begin()` → iterator pointing to **first element**
* `it` → iterator pointing to **target position**

To get **index**, we calculate **distance** between them.

```cpp
index = it - arr.begin();
```

---

## Simple real-life analogy

Imagine a ruler:

```
| 0 | 1 | 2 | 3 | 4 |
```

* `arr.begin()` → position 0
* `it` → position 3

To find index:

```
3 - 0 = 3
```

That’s exactly what STL does.

---

## Visual example

```cpp
arr = {10, 20, 30, 40, 50}
x = 30
```

```cpp
auto it = lower_bound(arr.begin(), arr.end(), 30);
```

`it` points to **30**.

Memory picture:

```
arr.begin()  → 10
it           → 30
```

Index calculation:

```cpp
it - arr.begin() = 2
```

---

## What happens if you don’t subtract

```cpp
int first = lower_bound(...); ❌
```

❌ Compilation error
Because:

* iterator ≠ integer

---

## Short rule (remember forever)

```text
STL returns iterator
Index = iterator - begin()
```

---

## One-line answer (interview safe)

> Because `lower_bound` returns an iterator, not an index.
> Subtracting `begin()` converts it into an index.

---

## Final clarity

| Expression         | Meaning             |
| ------------------ | ------------------- |
| `arr.begin()`      | start of array      |
| `lower_bound(...)` | pointer to position |
| `- arr.begin()`    | distance = index    |

---

## **In short:**

`lower_bound` (and `upper_bound`) return an **iterator**, not an index.
To convert that iterator into an **index**, we subtract the iterator of the first element.

```cpp
index = iterator - arr.begin();
```

**One-line rule:**

> **STL gives iterator → subtract `begin()` to get index.**
