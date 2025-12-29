# STL — Iterators (Complete Introduction)

---

## 1. What are Iterators?

**Iterators** are objects that **point to elements inside a container**.

They act like:

* Generalized pointers
* A bridge between **containers** and **algorithms**

Simple definition:

> Iterators allow algorithms to access container elements **without knowing the container type**.

---

## 2. Why Iterators Exist?

Problem without iterators:

* Algorithms would need container-specific logic
* `sort(vector)` vs `sort(list)` would need different implementations

Iterators solve:

* Container independence
* Code reuse
* Generic programming

This is why:

```cpp
sort(v.begin(), v.end());
```

works for different containers (when supported).

---

## 3. Core STL Design Rule (Very Important)

STL is built on **separation of concerns**:

| Component | Responsibility |
| --------- | -------------- |
| Container | Store data     |
| Iterator  | Access data    |
| Algorithm | Process data   |

Algorithms **never access containers directly**.
They only use **iterators**.

---

## 4. How Iterators Work (Conceptually)

An iterator:

* Points to an element
* Knows how to move to the next element
* Knows when the range ends

Typical usage:

```cpp
container.begin()  // points to first element
container.end()    // points past last element
```

Important:

* `end()` does NOT point to last element
* It points **one past the last**

---

## 5. Iterator as a Pointer (Mental Model)

Think of iterator as:

* A smart pointer
* With container-specific behavior

You can:

* Dereference: `*it`
* Move forward: `++it`

But:

* You cannot assume pointer arithmetic for all iterators

---

## 6. Types of Iterators (Very Important)

STL defines **5 iterator categories**, based on capabilities.

---

### 6.1 Input Iterator

* Can read values
* One-pass traversal
* Forward only

Used in:

* Input streams

---

### 6.2 Output Iterator

* Can write values
* One-pass traversal
* Forward only

Used in:

* Output streams

---

### 6.3 Forward Iterator

* Read + write
* Multi-pass
* Forward only

Containers:

* `forward_list`

---

### 6.4 Bidirectional Iterator

* Read + write
* Forward and backward movement

Containers:

* `list`
* `set`
* `map`

Supports:

```cpp
++it
--it
```

---

### 6.5 Random Access Iterator

* Full pointer-like behavior
* Jump to any position

Containers:

* `vector`
* `deque`
* `array`

Supports:

```cpp
it + n
it - n
it[i]
```

---

## 7. Iterator Support by Containers

| Container    | Iterator Type |
| ------------ | ------------- |
| array        | Random access |
| vector       | Random access |
| deque        | Random access |
| list         | Bidirectional |
| forward_list | Forward       |
| set / map    | Bidirectional |
| unordered_*  | Forward       |

This table is interview gold.

---

## 8. Why Some Algorithms Don’t Work Everywhere

Example:

```cpp
sort(list.begin(), list.end()); // INVALID
```

Reason:

* `sort` requires random access iterators
* `list` only provides bidirectional iterators

Correct approach:

```cpp
list.sort();
```

Algorithms depend on **iterator category**, not container.

---

## 9. Special Iterators

### 9.1 `const_iterator`

* Cannot modify element
* Used for read-only traversal

---

### 9.2 Reverse Iterators

* Traverse in reverse direction

Concept:

```cpp
rbegin() → last element
rend()   → before first element
```

---

## 10. Iterator Invalidation (Critical Concept)

Iterators can become **invalid** when container structure changes.

Examples:

* `vector` reallocation invalidates iterators
* `erase()` invalidates iterators at erased position

This causes:

* Undefined behavior
* Runtime bugs

Interviewers love this topic.

---

## 11. Iterators and Algorithms Relationship

Algorithm requirements depend on:

* Iterator category
* Range validity

Example:

* `find` → works with input iterators
* `sort` → requires random access iterators

Always check iterator requirements.

---

## 12. When to Use Iterators Explicitly

Use iterators when:

* Using STL algorithms
* Writing generic code
* Avoiding index-based loops

Avoid when:

* Simple loops where range-based for is enough

---

## 13. Common Interview Traps

1. `end()` is not last element
2. Using `sort` on `list`
3. Iterator invalidation after insert/erase
4. Assuming all iterators support `+`
5. Modifying data through `const_iterator`

---

## 14. Summary (Mental Model)

* Iterators are the **glue of STL**
* They abstract access, not storage
* Algorithm power depends on iterator category
* Correct iterator usage prevents subtle bugs

---
