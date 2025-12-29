# STL — Unordered Containers (Complete Package)

---

## 1. What are Unordered Containers?

**Unordered containers** store elements using **hashing**, not sorting.

Key idea:

* **Order does NOT matter**
* Elements are placed based on a **hash function**
* Focus is on **fast lookup**, not order

So when you iterate:

* Order is **unpredictable**
* It can change after insertions or rehashing

---

## 2. Why Unordered Containers Exist?

Problem with associative containers (`map`, `set`):

* Always sorted
* Operations cost `O(log n)`

Unordered containers solve:

* Faster average operations
* Direct access using hash keys
* Ideal when sorting is unnecessary

---

## 3. Internal Working (How Hashing Works)

Unordered containers are implemented using a **hash table**.

High-level flow:

1. Key is passed to a **hash function**
2. Hash function converts key → index
3. Index decides **bucket**
4. Element is stored in that bucket

If multiple keys map to same bucket → **collision**
Handled internally (usually chaining).

---

## 4. Types of Unordered Containers

| Container            | Key Property             |
| -------------------- | ------------------------ |
| `unordered_set`      | Unique values            |
| `unordered_multiset` | Duplicate values allowed |
| `unordered_map`      | Unique keys, key–value   |
| `unordered_multimap` | Duplicate keys allowed   |

---

## 5. `unordered_set`

### What

* Stores unique values
* No sorting

### Code Example

```cpp
#include <unordered_set>
#include <iostream>
using namespace std;

int main() {
    unordered_set<int> us;

    us.insert(10);
    us.insert(5);
    us.insert(10); // ignored

    for (int x : us) {
        cout << x << " ";
    }
}
```

Important:

* Output order is not guaranteed

### Time Complexity

* insert: O(1) average
* find: O(1) average
* erase: O(1) average
* worst case: O(n)

---

## 6. `unordered_multiset`

### What

* Same as `unordered_set`
* Allows duplicates

### Code Example

```cpp
#include <unordered_set>
#include <iostream>
using namespace std;

int main() {
    unordered_multiset<int> ums;

    ums.insert(10);
    ums.insert(10);
    ums.insert(5);

    for (int x : ums) {
        cout << x << " ";
    }
}
```

---

## 7. `unordered_map`

### What

* Stores **key → value**
* Keys are unique
* No sorting

### Code Example

```cpp
#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
    unordered_map<int, string> ump;

    ump[1] = "A";
    ump[3] = "C";
    ump[2] = "B";

    for (auto p : ump) {
        cout << p.first << " " << p.second << endl;
    }
}
```

Important behavior:

* `ump[key]` creates key if not present

---

## 8. `unordered_multimap`

### What

* Same as `unordered_map`
* Duplicate keys allowed

### Code Example

```cpp
#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
    unordered_multimap<int, string> umm;

    umm.insert({1, "A"});
    umm.insert({1, "B"});

    for (auto p : umm) {
        cout << p.first << " " << p.second << endl;
    }
}
```

---

## 9. Average vs Worst Case (Very Important)

| Case    | Complexity |
| ------- | ---------- |
| Average | O(1)       |
| Worst   | O(n)       |

Worst case happens when:

* Poor hash function
* Too many collisions
* All keys fall into one bucket

Interviewers care a lot about this distinction.

---

## 10. Load Factor & Rehashing (Conceptual)

* **Load factor** = elements / buckets
* If load factor increases:

  * Performance drops
* STL automatically:

  * Creates more buckets
  * Rehashes elements

This operation is expensive but rare.

---

## 11. When to Use Unordered Containers

Use when:

* Order does not matter
* Fast lookup is critical
* Large data sets

Avoid when:

* Sorted order required
* Need predictable iteration order
* Worst-case guarantees are important

---

## 12. Ordered vs Unordered Containers

| Feature            | Ordered  | Unordered  |
| ------------------ | -------- | ---------- |
| Internal structure | Tree     | Hash table |
| Order              | Sorted   | Random     |
| Search             | O(log n) | O(1) avg   |
| Worst case         | O(log n) | O(n)       |

---

## 13. Common Interview Traps

1. Iteration order is not fixed
2. `unordered_map` is NOT always O(1)
3. `operator[]` inserts key if missing
4. Worst case must be mentioned
5. Hashing depends on key type

---

## 14. Summary (Mental Model)

* Unordered containers trade **order** for **speed**
* Hashing gives fast access
* Average case is excellent
* Worst case exists and must be acknowledged

---
