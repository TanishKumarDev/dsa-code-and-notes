# Pair Pattern in Sorted Array

---

## First, the rule you must remember

In a **sorted array** where every element appears twice **except one**:

### Index pattern

```
Before the single element:
(first of pair at EVEN index)

After the single element:
(first of pair at ODD index)
```

---

## Example (very important)

```text
Index:  0  1  2  3  4  5  6  7  8
Array:  1  1  2  3  3  4  4  8  8
                 ↑
            single element = 2
```

### Look at pairs:

| Value | Indices | Start index |
| ----- | ------- | ----------- |
| 1     | (0,1)   | even        |
| 3     | (3,4)   | odd         |
| 4     | (5,6)   | odd         |
| 8     | (7,8)   | odd         |

Pattern **breaks after single element**.

---

## Now explain the condition line-by-line

```cpp
if (
   (mid % 2 == 0 && arr[mid] == arr[mid + 1]) ||
   (mid % 2 == 1 && arr[mid] == arr[mid - 1])
)
```

### Case 1️⃣

```cpp
mid % 2 == 0 && arr[mid] == arr[mid + 1]
```

Meaning:

* `mid` is **even**
* element at `mid` matches **next**

So this is a **valid pair** in the **left side pattern**

👉 Single element is **not here**, it is **on the right**

---

### Case 2️⃣

```cpp
mid % 2 == 1 && arr[mid] == arr[mid - 1]
```

Meaning:

* `mid` is **odd**
* element at `mid` matches **previous**

Again → **valid pair pattern**

👉 Single element is **on the right**

---

## So what do we do?

```cpp
low = mid + 1;
```

We **discard left part** because it is behaving normally.

---

## Else part (pattern broken)

```cpp
else
{
    high = mid - 1;
}
```

Means:

* pairing pattern is **broken**
* single element lies on the **left side**

---

## Very short intuition (lock this)

> If pairing is normal → go right
> If pairing is broken → go left

---

## One-line interview explanation

> We use index parity to detect where the pairing pattern breaks and move binary search accordingly.

---

## Tiny memory trick

```text
even = match next → right
odd  = match prev → right
otherwise → left
```
