# STL — Container Adaptors (Complete Package)

---

## 1. What are Container Adaptors?

**Container adaptors** are **restricted-interface containers**.

They:

* Do **not** provide full container functionality
* Expose **only specific operations**
* Are built **on top of other STL containers**

In simple words:

> Container adaptors change the **interface**, not the **data structure**.

---

## 2. Why Container Adaptors Exist?

Problem with normal containers:

* Too much freedom
* Easy to misuse (wrong access, wrong order)

Container adaptors solve:

* Enforced access rules
* Clear intent
* Safer logic

Example:

* Stack → only top access
* Queue → FIFO order
* Priority queue → highest priority first

---

## 3. Types of Container Adaptors

STL provides **3 container adaptors**:

| Adaptor          | Behavior                       |
| ---------------- | ------------------------------ |
| `stack`          | LIFO (Last In First Out)       |
| `queue`          | FIFO (First In First Out)      |
| `priority_queue` | Highest priority element first |

---

## 4. Key Design Rule

Container adaptors:

* **Do not support iterators**
* **Do not support random access**
* **Do not support traversal**

You can only use:

* push
* pop
* top / front / back

---

## 5. `stack`

### What

* LIFO structure
* Only access to the **top**

### Default Internal Container

* `deque`

### Code Example

```cpp
#include <stack>
#include <iostream>
using namespace std;

int main() {
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);

    cout << st.top() << endl; // 30

    st.pop();

    cout << st.top(); // 20
}
```

### Time Complexity

| Operation | Complexity |
| --------- | ---------- |
| push      | O(1)       |
| pop       | O(1)       |
| top       | O(1)       |

### When to Use

* Undo/Redo
* Expression evaluation
* Function call stack logic

---

## 6. `queue`

### What

* FIFO structure
* Insert at back, remove from front

### Default Internal Container

* `deque`

### Code Example

```cpp
#include <queue>
#include <iostream>
using namespace std;

int main() {
    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << q.front() << endl; // 10

    q.pop();

    cout << q.front(); // 20
}
```

### Time Complexity

| Operation | Complexity |
| --------- | ---------- |
| push      | O(1)       |
| pop       | O(1)       |
| front     | O(1)       |
| back      | O(1)       |

### When to Use

* Scheduling
* Task processing
* BFS traversal

---

## 7. `priority_queue`

### What

* Special queue where **highest priority** element is always on top

### Default Behavior

* Max heap

### Default Internal Container

* `vector`

### Code Example (Max Heap)

```cpp
#include <queue>
#include <iostream>
using namespace std;

int main() {
    priority_queue<int> pq;

    pq.push(10);
    pq.push(50);
    pq.push(20);

    cout << pq.top(); // 50
}
```

### Min Heap Example

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

### Time Complexity

| Operation | Complexity |
| --------- | ---------- |
| push      | O(log n)   |
| pop       | O(log n)   |
| top       | O(1)       |

### When to Use

* Dijkstra’s algorithm
* Scheduling
* Top-K problems

---

## 8. Why No Iterators?

Container adaptors:

* Enforce discipline
* Prevent accidental misuse
* Keep abstraction strong

If iteration is needed:

* Use underlying container directly (vector, deque, list)

---

## 9. Comparison Summary

| Feature            | stack | queue      | priority_queue |
| ------------------ | ----- | ---------- | -------------- |
| Order              | LIFO  | FIFO       | Priority based |
| Iteration          | No    | No         | No             |
| Internal container | deque | deque      | vector         |
| Access             | top   | front/back | top            |

---

## 10. Common Interview Traps

1. You cannot iterate over stack/queue
2. `priority_queue` is max heap by default
3. Container adaptors are **not containers**, they are **wrappers**
4. No random access allowed

---

## 11. When NOT to Use Container Adaptors

* When you need traversal
* When you need index access
* When you need flexible insert/delete

Use base containers instead.

---

## 12. Summary

* Container adaptors restrict access intentionally
* They provide safer and clearer logic
* Built on top of other STL containers
* Perfect for stack, queue, and priority-based problems

---