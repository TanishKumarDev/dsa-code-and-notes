# STL — Associative Containers (Complete Package)

---

## 1. What are Associative Containers?

**Associative containers** store elements in a way that **each element is associated with a key** and is **automatically kept in sorted order**.

Key idea:

* Elements are **not stored by insertion order**
* They are stored according to a **comparison rule**

Sorted order is maintained **internally**, not by you.

---

## 2. Why Associative Containers Exist?

Problem with sequence containers:

* Searching is slow (`O(n)`)
* Manual sorting needed
* Order can break after insertions

Associative containers solve:

* Automatic sorting
* Fast searching
* Logical organization of data

---

## 3. Internal Working (How)

All associative containers are implemented using a **self-balancing binary search tree**, typically a **Red-Black Tree**.

Because of this:

* Height is kept balanced
* Operations take `O(log n)` time

This guarantees performance even in worst cases.

---

## 4. Types of Associative Containers

| Container  | Key Property              |
| ---------- | ------------------------- |
| `set`      | Unique keys               |
| `multiset` | Duplicate keys allowed    |
| `map`      | Unique keys, key–value    |
| `multimap` | Duplicate keys, key–value |

---

## 5. `set`

### What

* Stores **unique values**
* Automatically sorted

### Code Example

```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    set<int> s;

    s.insert(10);
    s.insert(5);
    s.insert(10); // ignored

    for (int x : s) {
        cout << x << " ";
    }
}
```

Output:

```
5 10
```

### Time Complexity

* insert: O(log n)
* erase: O(log n)
* find: O(log n)

---

## 6. `multiset`

### What

* Same as `set`
* Allows **duplicate values**

### Code Example

```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    multiset<int> ms;

    ms.insert(10);
    ms.insert(10);
    ms.insert(5);

    for (int x : ms) {
        cout << x << " ";
    }
}
```

Output:

```
5 10 10
```

---

## 7. `map`

### What

* Stores data as **key → value**
* Keys are unique
* Sorted by key

### Code Example

```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    map<int, string> mp;

    mp[1] = "A";
    mp[3] = "C";
    mp[2] = "B";

    for (auto p : mp) {
        cout << p.first << " " << p.second << endl;
    }
}
```

Output:

```
1 A
2 B
3 C
```

---

## 8. `multimap`

### What

* Same as `map`
* Allows **duplicate keys**

### Code Example

```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    multimap<int, string> mm;

    mm.insert({1, "A"});
    mm.insert({1, "B"});

    for (auto p : mm) {
        cout << p.first << " " << p.second << endl;
    }
}
```

---

## 9. Ordering & Comparators

Default ordering:

* Ascending (`less<T>`)

Custom ordering possible using comparators (we will deep dive later).

---

## 10. Important Functions (Common)

| Function    | Purpose        |
| ----------- | -------------- |
| insert      | Add element    |
| erase       | Remove element |
| find        | Search         |
| count       | Frequency      |
| lower_bound | First ≥ key    |
| upper_bound | First > key    |
| equal_range | Range of keys  |

All run in `O(log n)` time.

---

## 11. When to Use Associative Containers

Use when:

* Sorted data required
* Fast search needed
* Keys matter more than positions

Avoid when:

* Order doesn’t matter
* Need `O(1)` lookup (use unordered containers)

---

## 12. Associative vs Sequence Containers

| Feature         | Sequence  | Associative |
| --------------- | --------- | ----------- |
| Order           | Insertion | Sorted      |
| Search          | O(n)      | O(log n)    |
| Access by index | Yes       | No          |
| Key based       | No        | Yes         |

---

## 13. Interview Traps

1. `map[key]` inserts key if not present
2. No random access (`mp[2]` is not index-based)
3. Iteration is always sorted
4. All operations are logarithmic

---

## 14. Summary

* Associative containers maintain sorted data
* Internally tree-based
* Predictable `O(log n)` performance
* Best when order + search both matter

---
