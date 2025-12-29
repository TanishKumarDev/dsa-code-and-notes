# C++ STL (Standard Template Library)

## What is STL?

STL is a collection of generic (template-based) classes and functions that provide ready-made implementations of common data structures and algorithms. It simplifies data handling and improves code efficiency, reliability, and readability.

---

## Main Components of STL

STL is broadly divided into 3 core components:

### 1. Containers

Data structures used to store collections of objects.
Examples: vector, list, set, map, deque, stack.

### 2. Algorithms

Functions that perform operations on containers.
Examples: sort(), find(), reverse(), binary_search(), accumulate().

### 3. Iterators

Objects that act like pointers to traverse container elements.
Examples: begin(), end(), rbegin(), rend().

These three work together:
Containers store data → Iterators access data → Algorithms process data

---

## Advantages of STL (Concise)

* Reusability – Ready-made containers and algorithms reduce coding effort.
* Efficiency – Highly optimized implementations.
* Type Safety – Template-based, works with any data type safely.
* Consistency – Standardized across all C++ compilers.
* Faster Development – Saves time by avoiding manual data structure coding.
* Modular Design – Clear separation of data and logic.
* Scalability – Easily handles large data sets.
* Community & Documentation – Well-supported and widely used.

---

## STL Component 1 – Containers

Containers store data in an organized way. Each container is defined in its own header file and implemented as a template class.

### Types of Containers

### 1. Sequence Containers

Store elements in a linear order.
Examples:

* vector – Dynamic array, fast random access
* list – Doubly linked list
* deque – Double-ended queue
* array – Fixed-size array (C++11)
* forward_list – Singly linked list

Use when order matters and indexed access is required.

---

### 2. Container Adaptors

Provide restricted interfaces over sequence containers.
Examples:

* stack – LIFO structure
* queue – FIFO structure
* priority_queue – Highest priority element first

Used to implement specific behavior patterns.

---

### 3. Associative Containers

Store elements in a sorted order based on keys.
Examples:

* set – Unique sorted elements
* multiset – Duplicate allowed
* map – Key-value pairs (unique keys)
* multimap – Key-value pairs (duplicate keys)

Implemented using balanced binary trees (usually Red-Black Tree).

---

### 4. Unordered Associative Containers

Store data using hash tables (no sorted order).
Examples:

* unordered_set
* unordered_multiset
* unordered_map
* unordered_multimap

Faster access (average O(1)) compared to ordered containers.

---

### Key Differences (Quick View)

| Type        | Order        | Data Structure | Access Speed |
| ----------- | ------------ | -------------- | ------------ |
| Sequence    | Insert Order | Array / List   | Fast Random  |
| Associative | Sorted       | Tree           | Log n        |
| Unordered   | No Order     | Hash Table     | O(1) avg     |

---

## STL Component 2 – Algorithms

Algorithms operate on container ranges through iterators.
Defined in:
#include <algorithm>
#include <numeric>

### Common STL Algorithms

* sort() – Sorts elements
* find() – Searches an element
* count() – Counts occurrences
* reverse() – Reverses sequence
* transform() – Applies function to range
* accumulate() – Computes sum
* binary_search() – Searches in sorted data
* merge() – Merges sorted ranges
* unique() – Removes duplicate adjacent values
* replace() – Replaces specific values
* partition() – Divides based on condition

Features:

* Highly optimized
* Generic and reusable
* Works with any container using iterators

---

## STL Component 3 – Iterators

Iterators are pointer-like objects used to navigate container elements safely.

### Types of Iterators

1. Input Iterator – Read-only, single pass
2. Output Iterator – Write-only
3. Forward Iterator – Read + Write, single direction
4. Bidirectional Iterator – Move forward & backward
5. Random Access Iterator – Direct access using index

Examples:

* vector supports Random Access
* list supports Bidirectional
* forward_list supports Forward

Iterators allow algorithms and containers to work together seamlessly.

---

## STL Workflow Example

Container → vector<int> v
Iterator → v.begin(), v.end()
Algorithm → sort(v.begin(), v.end())

---

## Additional Benefits of STL

* Reduces bugs by using tested implementations
* Improves global code readability
* Encourages best coding practices
* Minimal memory leakage risk
* Portable and maintainable codebase

---

## Summary

STL is a powerful part of modern C++ that provides:

* Smart containers for data storage
* Efficient algorithms for data processing
* Flexible iterators for access

```md
C++ STL
│
├── Containers
│   ├── Sequence
│   │   ├── vector
│   │   ├── deque
│   │   └── list
│   │
│   ├── Adaptors
│   │   ├── stack
│   │   ├── queue
│   │   └── priority_queue
│   │
│   ├── Associative (Ordered)
│   │   ├── set
│   │   ├── multiset
│   │   ├── map
│   │   └── multimap
│   │
│   └── Unordered (Hash Based)
│       ├── unordered_set
│       ├── unordered_multiset
│       ├── unordered_map
│       └── unordered_multimap
│
├── Algorithms
│   ├── Sorting
│   │   ├── sort()
│   │   └── next_permutation()
│   │
│   ├── Searching
│   │   ├── min_element()
│   │   └── max_element()
│   │
│   └── Bit Operations
│       └── __builtin_popcount()
│
└── Iterators
    ├── begin() / end()
    ├── rbegin() / rend()
    └── iterator types
```