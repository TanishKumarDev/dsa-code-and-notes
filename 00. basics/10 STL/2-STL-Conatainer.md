# STL — Containers (Complete Introduction)

---

## 1. What is an STL Container?

An **STL Container** is a **pre-built data structure** provided by C++ that is used to **store and manage a collection of elements** in memory.

Instead of manually implementing arrays, linked lists, trees, or hash tables, STL gives you **ready-made, optimized, and tested containers**.

In simple words:

> Containers are **data holders**.
> Algorithms work **on containers**.
> Iterators connect **containers and algorithms**.

---

## 2. Why Containers Exist (Problem They Solve)

Before STL:

* You had to write your own:

  * Dynamic arrays
  * Linked lists
  * Trees
  * Hash tables
* This caused:

  * Bugs
  * Memory leaks
  * Time waste
  * Inconsistent performance

STL containers solve this by:

* Giving **standard implementations**
* Ensuring **efficiency**
* Providing **predictable time complexity**
* Integrating smoothly with STL algorithms

---

## 3. How Containers Work (High-Level)

Internally, every container is based on some **core data structure**:

| Container Type | Internally Based On |
| -------------- | ------------------- |
| vector         | Dynamic array       |
| list           | Doubly linked list  |
| deque          | Segmented array     |
| set / map      | Red-Black Tree      |
| unordered_*    | Hash table          |
| stack / queue  | Other containers    |

You **do not see** this internal structure directly, but it decides:

* Speed
* Memory usage
* Operation cost

---

## 4. When to Use STL Containers

Use STL containers when:

* You want **safe and clean code**
* You want **guaranteed performance**
* You want to avoid reinventing data structures
* You are writing:

  * DSA solutions
  * Competitive programming
  * Production code
  * Interviews

Avoid STL only when:

* Extremely low-level systems code
* Strict memory layout control required

---

## 5. Core Properties of Containers

Every STL container provides:

* Automatic memory management
* Dynamic size (except `array`)
* Standard functions like:

  * insert
  * erase
  * size
  * empty
* Compatibility with iterators
* Compatibility with algorithms (`sort`, `find`, etc.)

---

## 6. Classification of STL Containers

STL containers are divided into **4 major categories**.

---

### 6.1 Sequence Containers

Used when **order matters** and elements are stored sequentially.

| Container    | Key Idea           |
| ------------ | ------------------ |
| array        | Fixed-size array   |
| vector       | Dynamic array      |
| deque        | Double-ended array |
| list         | Doubly linked list |
| forward_list | Singly linked list |

Use when:

* You care about **position**
* You want **index-based or sequential access**

---

### 6.2 Associative Containers (Ordered)

Used when:

* Data must remain **sorted**
* Fast searching is needed

| Container | Key Property           |
| --------- | ---------------------- |
| set       | Unique keys            |
| multiset  | Duplicate keys         |
| map       | Key–value pairs        |
| multimap  | Duplicate keys allowed |

Important:

* Elements are always sorted
* Internally tree-based
* Operations are usually `O(log n)`

---

### 6.3 Unordered Containers (Hash-Based)

Used when:

* Order does NOT matter
* Fast lookup is required

| Container          |
| ------------------ |
| unordered_set      |
| unordered_map      |
| unordered_multiset |
| unordered_multimap |

Key idea:

* Based on hashing
* Average time: `O(1)`
* Worst case: `O(n)` (rare but important in interviews)

---

### 6.4 Container Adaptors

These do NOT expose full container functionality.

| Adaptor        |
| -------------- |
| stack          |
| queue          |
| priority_queue |

They:

* Restrict access
* Are built on top of other containers
* Provide specific behavior (LIFO / FIFO / Heap)

---

## 7. Time Complexity Intuition (High-Level)

No deep tables now, just intuition.

| Operation                    | Depends On    |
| ---------------------------- | ------------- |
| Fast random access           | vector, deque |
| Fast insert/delete in middle | list          |
| Always sorted                | set, map      |
| Fast lookup                  | unordered_map |
| Strict access control        | stack, queue  |

Choosing the **right container** is more important than knowing all functions.

---

## 8. Containers vs Algorithms (Important Distinction)

* Containers **store data**
* Algorithms **process data**
* Iterators **connect them**

Example idea (no code):

* Container holds numbers
* Algorithm sorts numbers
* Iterator points to elements

This separation is a **core STL design principle**.

---

## 9. Interview Perspective

Interviewers expect you to know:

* Why you chose a container
* Time complexity reasoning
* Trade-offs between containers

Bad answer:

> “I used vector because I know it.”

Good answer:

> “I used vector because I needed fast random access and minimal insertion in the middle.”

---

## 10. Summary (Mental Model)

* Containers = **Where data lives**
* Algorithms = **What we do with data**
* Iterators = **How we reach data**

STL containers give:

* Reliability
* Performance
* Clean code
* Industry-standard solutions

---