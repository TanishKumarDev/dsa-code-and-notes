# STL — Sequence Containers (Complete Package)

---

## 1. What are Sequence Containers?

**Sequence containers** store elements in a **linear sequence**, meaning:

* Elements are stored **one after another**
* **Order is preserved**
* Position of elements matters

Examples:

* First element
* Last element
* Middle element
* Next / Previous element

They are best when you care about **ordering and traversal**.

---

## 2. Why Sequence Containers Exist?

Problem before STL:

* Fixed-size arrays
* Manual memory handling
* Difficult insert/delete operations

Sequence containers solve:

* Dynamic sizing
* Safe memory management
* Easy insertion, deletion, traversal

---

## 3. Types of Sequence Containers

STL provides **5 sequence containers**:

| Container      | Internal Structure | Key Feature        |
| -------------- | ------------------ | ------------------ |
| `array`        | Static array       | Fixed size         |
| `vector`       | Dynamic array      | Fast random access |
| `deque`        | Segmented array    | Fast front & back  |
| `list`         | Doubly linked list | Fast insert/delete |
| `forward_list` | Singly linked list | Less memory        |

---

## 4. `array` (Fixed Size)

### What

* Wrapper over normal array
* Size fixed at compile time

### When to Use

* Size is known
* Want STL features with array safety

### Code Example

```cpp
#include <array>
#include <iostream>
using namespace std;

int main() {
    array<int, 5> arr = {1, 2, 3, 4, 5};

    cout << arr[0] << endl;
    cout << arr.size() << endl;
}
```

### Time Complexity

* Access: O(1)
* Insert/Delete: Not allowed

---

## 5. `vector` (Dynamic Array)

### What

* Most used STL container
* Automatically resizes

### Why

* Combines array speed with dynamic size

### How (Internally)

* Uses contiguous memory
* When capacity is full → allocates bigger memory and copies

### Code Example

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for (int x : v) {
        cout << x << " ";
    }
}
```

### Time Complexity

| Operation     | Complexity     |
| ------------- | -------------- |
| Access        | O(1)           |
| Push back     | O(1) amortized |
| Insert middle | O(n)           |

### When NOT to Use

* Too many middle insertions/deletions

---

## 6. `deque` (Double Ended Queue)

### What

* Allows fast insertion at **both ends**

### Difference from vector

* Not fully contiguous
* Uses multiple blocks

### Code Example

```cpp
#include <deque>
#include <iostream>
using namespace std;

int main() {
    deque<int> dq;

    dq.push_back(10);
    dq.push_front(5);

    cout << dq.front() << " " << dq.back();
}
```

### Time Complexity

* Front insert: O(1)
* Back insert: O(1)
* Random access: O(1)

### When to Use

* Need fast front and back operations

---

## 7. `list` (Doubly Linked List)

### What

* Non-contiguous memory
* Each node has prev and next pointers

### Why

* Efficient insertion and deletion anywhere

### Code Example

```cpp
#include <list>
#include <iostream>
using namespace std;

int main() {
    list<int> l;

    l.push_back(10);
    l.push_front(5);

    for (int x : l) {
        cout << x << " ";
    }
}
```

### Time Complexity

| Operation     | Complexity |
| ------------- | ---------- |
| Insert/Delete | O(1)       |
| Access        | O(n)       |

### When NOT to Use

* When random access is needed

---

## 8. `forward_list` (Singly Linked List)

### What

* Like `list` but only forward traversal

### Why

* Saves memory

### Code Example

```cpp
#include <forward_list>
#include <iostream>
using namespace std;

int main() {
    forward_list<int> fl;

    fl.push_front(10);
    fl.push_front(20);

    for (int x : fl) {
        cout << x << " ";
    }
}
```

### Limitation

* No size()
* No backward traversal

---

## 9. Comparison Summary

| Feature            | array | vector | deque  | list | forward_list |
| ------------------ | ----- | ------ | ------ | ---- | ------------ |
| Dynamic size       | No    | Yes    | Yes    | Yes  | Yes          |
| Random access      | Yes   | Yes    | Yes    | No   | No           |
| Fast insert middle | No    | No     | No     | Yes  | Yes          |
| Memory efficient   | High  | Medium | Medium | Low  | Very High    |

---

## 10. Interview Mindset

Always justify your choice.

Example:

* Use `vector` → random access needed
* Use `list` → frequent insert/delete
* Use `deque` → front + back operations

---

## 11. Summary

* Sequence containers store data **linearly**
* Choice depends on:

  * Access pattern
  * Insert/delete frequency
  * Memory constraints
* `vector` is default choice unless constraints demand otherwise

---
