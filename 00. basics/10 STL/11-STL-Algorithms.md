# STL — Algorithms (Complete Introduction)

---

## 1. What are STL Algorithms?

**STL algorithms** are **predefined generic functions** that perform operations on a range of elements.

They:

* Do **not** store data
* Do **not** know about containers
* Work only on **iterators**

Key idea:

> Algorithms operate on **ranges**, not on containers.

---

## 2. Why STL Algorithms Exist?

Before STL:

* Logic was tightly coupled with data structures
* Repetitive loop-based code
* Error-prone and hard to reuse

STL algorithms solve:

* Code reusability
* Separation of concerns
* High performance (optimized internally)
* Clean and expressive code

---

## 3. How STL Algorithms Work (Core Design)

STL algorithms are built on **three pillars**:

1. Containers – store data
2. Iterators – point to elements
3. Algorithms – operate on ranges

Algorithm signature conceptually looks like:

```
algorithm(begin_iterator, end_iterator, optional_parameters)
```

Because of this:

* Same algorithm works on `vector`, `list`, `deque`, etc.
* Algorithm doesn’t care about container type

---

## 4. Important Rule (Very Important)

STL algorithms:

* **Do not change container size**
* They only:

  * Modify values
  * Rearrange elements
  * Inspect data

Operations like insertion or deletion must be done via containers.

---

## 5. Categories of STL Algorithms

STL algorithms are broadly classified into **6 categories**.

---

## 6. Non-Modifying Algorithms

Used to **read or inspect** data.

Examples:

* `find`
* `count`
* `all_of`
* `any_of`
* `none_of`

Example:

```cpp
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4};

    auto it = find(v.begin(), v.end(), 3);

    if (it != v.end()) {
        cout << "Found";
    }
}
```

These algorithms do **not** change data.

---

## 7. Modifying Algorithms

Used to **change values or order**.

Examples:

* `sort`
* `reverse`
* `rotate`
* `replace`
* `remove`

Example:

```cpp
sort(v.begin(), v.end());
reverse(v.begin(), v.end());
```

Important:

* `remove` does NOT erase elements
* It only shifts values

---

## 8. Partitioning Algorithms

Used to divide elements based on a condition.

Examples:

* `partition`
* `stable_partition`

They group elements but do not sort.

---

## 9. Binary Search Algorithms

Work only on **sorted ranges**.

Examples:

* `binary_search`
* `lower_bound`
* `upper_bound`
* `equal_range`

Example:

```cpp
binary_search(v.begin(), v.end(), 10);
```

Using these on unsorted data gives **undefined results**.

---

## 10. Numeric Algorithms

Used for numerical operations.

Examples:

* `accumulate`
* `partial_sum`
* `inner_product`

Example:

```cpp
#include <numeric>

int sum = accumulate(v.begin(), v.end(), 0);
```

---

## 11. Heap Algorithms

Used to work with heap structures.

Examples:

* `make_heap`
* `push_heap`
* `pop_heap`
* `sort_heap`

These work on **heap ranges**, not containers.

---

## 12. Algorithm + Function Object / Lambda

Many algorithms accept:

* Function pointers
* Functors
* Lambdas

Example idea:

```cpp
sort(v.begin(), v.end(), greater<int>());
```

This allows:

* Custom behavior
* Cleaner logic
* Flexible conditions

---

## 13. Time Complexity Intuition

Algorithm complexity depends on:

* Type of algorithm
* Iterator category
* Container type

Examples:

* `find` → O(n)
* `sort` → O(n log n)
* `binary_search` → O(log n)

Always mention complexity in interviews.

---

## 14. When to Use STL Algorithms

Use when:

* You want clean, readable code
* Standard logic is enough
* Performance matters

Avoid when:

* Custom behavior is extremely specific
* You need full control over memory

---

## 15. Common Interview Traps

1. Algorithms work on iterators, not containers
2. `remove` does not erase
3. Binary search requires sorted data
4. Algorithms don’t change container size
5. Wrong iterator range leads to bugs

---

## 16. Summary (Mental Model)

* Containers store data
* Iterators point to data
* Algorithms process data

STL algorithms are:

* Generic
* Efficient
* Reusable
* Interview critical

---