# INTRO TO LINKED LIST 

### What We Covered Here

1. Why arrays fail for dynamic data (fixed size problem)
2. Memory layout of arrays vs linked lists (contiguous vs non-contiguous)
3. High-level idea of a linked list
4. How linked list nodes are stored in memory
5. Node structure (data + next pointer/reference)
6. Difference between C++ pointers and JavaScript references
7. Role of head and tail in a linked list
8. Core rule: never traverse using `head` directly
9. **Problem:** Converting an array into a linked list
10. **Problem:** Traversing a linked list safely
11. **Problem:** Calculating the length of a linked list
12. **Problem:** Searching for a value in a linked list
13. Understanding `null` as the end of the list
14. Time and space complexity of basic linked list operations
15. Building traversal-based thinking for all future linked list problems

---

## 1. Why We Need Linked List (Problem With Arrays)

### Core Problem

Arrays have a **fixed size**.

Example:

```text
Array = [1, 3, 2, 5]  // size = 4
```

If later we want to add `8`, we **cannot**:

* The size is fixed
* Memory after the array may already be occupied

### Memory Reality of Arrays

* Arrays are stored in **contiguous memory**
* Example (conceptual):

```text
Index:   0     1     2     3
Value:   1     3     2     5
Address: 100   104   108   112
```

This makes:

* Index-based access easy
* Resizing difficult or impossible

---
## 2. What Is a Linked List (High-Level Idea)

A **Linked List** is a **linear data structure** where:

* Elements (**nodes**) are **not stored contiguously** in memory
* Each node stores:

  * **data** (actual value)
  * **link(s)** (pointer/reference to other node(s))

Because nodes are connected using links instead of memory position, the list can **grow or shrink dynamically** without reallocation.

---

### Core Characteristics (Why Linked List Is Different from Array)

* ❌ No contiguous memory requirement
* ✅ Dynamic size (insert/delete anytime)
* ❌ No direct index-based access
* ✅ Sequential access via traversal
* ✅ Efficient insert/delete (no shifting like arrays)

---

### Core Terminology (Must Be Clear)

![](https://cdn-images-1.medium.com/max/2560/1*GOKmkucFHN_gmTMUtyC2sQ.png)
#### Node

A **node** is the fundamental unit of a linked list.

```
[data | link(s)]
```

* `data` → value stored
* `link(s)` → address/reference of other node(s)

---

#### Head

* Reference to the **first node**
* Entry point of the linked list
* Losing `head` = losing the entire list

---

#### Tail

* The **last node** of the list
* Its link points to:

  * `null` → singly / doubly linked list
  * `head` → circular linked list

---

#### Traversal

* Process of visiting nodes **one by one**
* Always starts from `head`
* Stops when:

  * `null` is reached (SLL / DLL)
  * `head` is reached again (CLL)

---

### Why Do We Have Different Types of Linked Lists?

Different problems need different navigation and deletion behavior:

* Only forward movement → **Singly Linked List**
* Forward + backward movement → **Doubly Linked List**
* Continuous looping → **Circular Linked List**

So linked lists are classified based on **how nodes are connected**.

---

### Types of Linked Lists (Foundation Overview)

![](https://images.wondershare.com/edrawmax/articles2024/linked-list-c-plus-plus-program/efficient-linked-list-usage-in-c-plus-plus-02.jpg)

#### Type 1: Singly Linked List (SLL)

* Each node has:

  * `data`
  * `next`
* Traversal only in **one direction**

```
head → [5] → [10] → [15] → [20] → null
```

Key points:

* Memory efficient
* Cannot move backward
* Previous node needed for deletion

---

#### Type 2: Doubly Linked List (DLL)

* Each node has:

  * `back`
  * `data`
  * `next`
* Traversal in **both directions**

```
null ← [5] ⇄ [10] ⇄ [15] ⇄ [20] → null
```

Key points:

* Easier deletion
* Extra memory for `back` pointer
* More pointer handling

---

#### Type 3: Circular Linked List (CLL)

* Last node points back to **head**
* No `null` at the end

```
head → [5] → [10] → [15] → [20]
  ↑_________________________|
```

Key points:

* Continuous traversal
* Careful stopping condition required
* Useful for cyclic processes

---

### Comparison Summary (Quick Recall)

| Feature            | Singly | Doubly | Circular |
| ------------------ | ------ | ------ | -------- |
| Forward traversal  | Yes    | Yes    | Yes      |
| Backward traversal | No     | Yes    | Yes*     |
| Extra memory       | Low    | High   | Medium   |
| End marker         | null   | null   | head     |
| Complexity         | Simple | Medium | Tricky   |

* backward only if doubly circular

![](https://miro.medium.com/v2/resize:fit:1400/1*YaVBXzzBuMIHYaEczAcAig.png)
---

### Mental Model (Interview Ready)

* **SLL** → simple, memory-efficient, forward only
* **DLL** → flexible, easy deletion, extra memory
* **CLL** → looping structure, careful traversal

---

### Key Takeaway

> Linked Lists differ **only by how nodes connect**.
> Once node connections are clear, **all operations reduce to pointer updates**.

---

## 3. How Linked List Is Stored in Memory

### Conceptual Visualization

Elements can live **anywhere** in heap memory:

```text
Node(1) -> Node(3) -> Node(2) -> Node(5) -> null
```

But physically:

```text
1 at M1
3 at M7
2 at M3
5 at M20
```

They are **connected by storing addresses**, not by position.

---

## 4. Core Building Block: Node

Each node stores **two things**:

1. Data
2. Pointer to the next node

### Mental Model

```text
[ data | next ]
```

If `next == null`, that node is the **tail**.

---

## 5. Defining a Node (C++ and JavaScript)

### C++ Node Definition

```cpp
class Node {
public:
    int data;        // stores value
    Node* next;      // pointer to next node

    // Constructor to initialize a node
    Node(int value) {
        data = value;
        next = nullptr;
    }
};
```

Why each part exists:

* `data`: actual value
* `next`: remembers where the next node lives
* `nullptr`: marks end of list

---

### JavaScript Node Definition

```javascript
class Node {
    constructor(value) {
        this.data = value;   // stores value
        this.next = null;    // reference to next node
    }
}
```

Key difference:

* No pointers in JS
* References behave like pointers conceptually

---

## 6. Head and Tail (Very Important)

* **Head**: pointer/reference to first node
* **Tail**: last node whose `next == null`

Rule:

> Never lose the head.
> If you lose the head, the list is lost.

---

## 7. Converting an Array to a Linked List

### Problem Statement

Given an array, convert it into a singly linked list and return the **head**.

---

### Intuition

* First element becomes the head
* Use a moving pointer (`mover`) to attach new nodes
* Always append at the end

---

### Step-by-Step Dry Run

Array:

```text
[2, 1, 3, 8]
```

Steps:

1. Create head with `2`
2. `mover = head`
3. Create node `1`, attach to `mover.next`
4. Move `mover`
5. Repeat for `3`, then `8`

Final structure:

```text
head -> 2 -> 1 -> 3 -> 8 -> null
```
### PSEUDOCODE FILE : Array to Linked List

```
// ---------- Node Structure ----------

// DEFINE Node
//     data        -> value stored in node
//     next        -> pointer to next node
// END

// Meaning:
// Har Linked List node ke paas data hota hai
// aur next node ka address hota hai



// ---------- Function: convertArrayToLL ----------

// FUNCTION convertArrayToLL(arr)

//     IF arr size is 0
//         RETURN null
//     ENDIF

//     CREATE head node using arr[0]
//     SET mover = head

//     FOR i from 1 to arr size - 1
//         CREATE new node temp using arr[i]
//         SET mover.next = temp
//         SET mover = temp
//     END FOR

//     RETURN head

// END FUNCTION

// Meaning:
// Array ke first element se head banta hai
// Baaki elements ke liye naye nodes bante hain
// Har node ko previous node se link kiya jata hai



// ---------- Function: printLinkedList ----------

// FUNCTION printLinkedList(head)

//     SET temp = head

//     WHILE temp is not null
//         PRINT temp.data
//         MOVE temp to temp.next
//     END WHILE

// END FUNCTION

// Meaning:
// Head se start karke NULL tak traverse karte hain
// Har node ka data print karte hain



// ---------- Main Function ----------

// START main

//     CREATE array arr = [10, 20, 30, 40, 50]

//     CALL convertArrayToLL(arr)
//     STORE returned value in head

//     CALL printLinkedList(head)

// END main

// Meaning:
// Array banao
// Array ko Linked List me convert karo
// Linked List print karke verify karo



// ---------- One-line Intuition ----------

// Array  -> values already present
// Linked List -> nodes banao, connect karo, head return karo

```



---

### C++ Code (Array → Linked List)

```cpp
Node* convertArrayToLL(vector<int>& arr) {
    if (arr.size() == 0) return nullptr;

    // Step 1: Create head
    Node* head = new Node(arr[0]);

    // Step 2: Mover pointer
    Node* mover = head;

    // Step 3: Create remaining nodes
    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]); // new node
        mover->next = temp;            // link
        mover = temp;                  // move forward
    }

    return head; // return starting point
}
```

---

### JavaScript Code

```javascript
function convertArrayToLL(arr) {
    if (arr.length === 0) return null;

    // Step 1: Create head
    let head = new Node(arr[0]);

    // Step 2: Mover pointer
    let mover = head;

    // Step 3: Create remaining nodes
    for (let i = 1; i < arr.length; i++) {
        let temp = new Node(arr[i]);
        mover.next = temp;
        mover = temp;
    }

    return head;
}
```

---

### Time & Space Complexity

* Time: **O(n)**
* Space: **O(n)** (new nodes)

---
## 8. Traversal of a Linked List (Most Important Skill)

---

### Rule

> **Never traverse using `head` directly.**
> Always use a **temporary pointer**.

**Reason (Why this rule exists):**

* `head` stores the starting address of the linked list.
* If you move `head`, you **lose access** to the list.
* Many operations (insert, delete, print) still need `head` later.

So:

* `head` → permanent reference
* `temp` → moving pointer for traversal

---

### Traversal Logic (Step-by-Step Thinking)

1. Take a temporary pointer temp and assign it head
2. Check: is temp pointing to a valid node?
3. If yes:
    * Print temp->data
    * Move temp to temp->next
4. Repeat until temp becomes null
5. Stop traversal
Why stop at null?
    * null means no node exists after this
    * End of linked list

---

### Pseudocode (Before Writing Code)

```
TRAVERSE(head):
    temp ← head

    WHILE temp is not NULL:
        print temp.data
        temp ← temp.next
```

---

### C++ Traversal Code

```cpp
void traverse(Node* head) {
    Node* temp = head;

    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
```

---

### C++ Traversal Code (With Deep Explanation)

```cpp
#include <iostream>
using namespace std;

// Node structure for Linked List
class Node {
public:
    int data;       // Stores the value
    Node* next;     // Stores address of next node

    // Constructor to initialize node
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to traverse and print linked list
void traverse(Node* head) {
    // temp pointer is used so that original head is not modified
    Node* temp = head;

    // Loop continues until temp becomes NULL
    // NULL means we crossed the last node
    while (temp != nullptr) {

        // Print current node's data
        cout << temp->data << " ";

        // Move temp to next node
        temp = temp->next;
    }
}

// Main function to test traversal
int main() {
    /*
        Creating linked list:
        10 -> 20 -> 30 -> NULL
    */

    Node* head = new Node(10);          // First node
    head->next = new Node(20);          // Second node
    head->next->next = new Node(30);    // Third node

    // Calling traversal function
    traverse(head);

    return 0;
}
```

---

### Dry Run (C++)

Linked List:

```
10 -> 20 -> 30 -> NULL
```

| Step | temp points to | Printed | temp moves to |
| ---- | -------------- | ------- | ------------- |
| 1    | 10             | 10      | 20            |
| 2    | 20             | 20      | 30            |
| 3    | 30             | 30      | NULL          |
| Stop | NULL           | —       | loop ends     |

**Output:**

```
10 20 30
```

---


### JavaScript Traversal Code

```javascript
function traverse(head) {
    let temp = head;

    while (temp !== null) {
        console.log(temp.data);
        temp = temp.next;
    }
}
```

### JavaScript Traversal Code (With Deep Explanation)

```javascript
// Node structure
class Node {
    constructor(data) {
        this.data = data;   // stores value
        this.next = null;   // points to next node
    }
}

// Traversal function
function traverse(head) {
    // temp pointer to protect head
    let temp = head;

    // Traverse until end of list
    while (temp !== null) {

        // Print current node data
        console.log(temp.data);

        // Move to next node
        temp = temp.next;
    }
}

// Main execution
// Creating linked list: 1 -> 2 -> 3 -> null
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);

// Traversing the linked list
traverse(head);
```

---

### Dry Run (JavaScript)

```
head → 1 → 2 → 3 → null
temp → moves node by node
```

Printed sequence:

```
1
2
3
```

---

### Time & Space Complexity (Very Important)

#### Time Complexity (TC)

* Each node is visited **exactly once**
* If there are `n` nodes:

```
Time Complexity = O(n)
```

#### Space Complexity (SC)

* Only **one extra pointer (`temp`)** is used
* No extra data structures

```
Space Complexity = O(1)
```

---

### Common Mistakes to Avoid

1. ❌ Using `head` directly for traversal
2. ❌ Forgetting to move `temp = temp->next`
3. ❌ Infinite loop due to wrong condition
4. ❌ Assuming linked list has fixed size like array

---

### Key Interview Insight

> Traversal is the **base skill** of Linked List.
> If traversal is weak → insert, delete, search will all break.
---

## 9. Length of a Linked List

---

### Idea

**Traversal + Counter**

We walk through the linked list **once** and count how many nodes we visit.

---

### Rule (Very Important)

> Never move `head` directly.
> Always use a temporary pointer.

**Why:**

* `head` is the only entry point to the linked list.
* If you change it, the list reference is lost.
* Length calculation is a **read-only** operation → no reason to touch `head`.

---

### Traversal Logic (Thinking Process)

1. Start from `head`
2. Maintain a counter `count`
3. For every node visited:

   * Increase `count`
   * Move to next node
4. Stop when pointer becomes `null`
5. Return `count`

---

### Pseudocode (Before Writing Code)

```
LENGTH_OF_LL(head):
    count ← 0
    temp ← head

    WHILE temp is not NULL:
        count ← count + 1
        temp ← temp.next

    RETURN count
```

---

### C++ Code

#### Version 1 — Simple / Clean (Only Required Function, No Comments)

```cpp
int lengthOfLL(Node* head) {
    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    return count;
}
```

---

#### Version 2 — Deep / Explained (Complete Program)

```cpp
#include <iostream>
using namespace std;

// Node structure for Linked List
class Node {
public:
    int data;        // value stored in node
    Node* next;      // pointer to next node

    // constructor
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to calculate length of linked list
int lengthOfLL(Node* head) {

    // Counter to store number of nodes
    int count = 0;

    // Temporary pointer for traversal
    // Using temp ensures head remains unchanged
    Node* temp = head;

    // Traverse until end of list
    while (temp != nullptr) {

        // One node visited, so increase count
        count++;

        // Move to next node
        temp = temp->next;
    }

    // After traversal, count holds total nodes
    return count;
}

int main() {
    /*
        Creating linked list:
        5 -> 10 -> 15 -> 20 -> NULL
    */

    Node* head = new Node(5);
    head->next = new Node(10);
    head->next->next = new Node(15);
    head->next->next->next = new Node(20);

    // Calling length function
    int length = lengthOfLL(head);

    // Printing result
    cout << "Length of Linked List: " << length << endl;

    return 0;
}
```

---

### Dry Run (C++)

Linked List:

```
5 -> 10 -> 15 -> 20 -> NULL
```

| Step  | temp points to | count |
| ----- | -------------- | ----- |
| Start | 5              | 0     |
| 1     | 5              | 1     |
| 2     | 10             | 2     |
| 3     | 15             | 3     |
| 4     | 20             | 4     |
| End   | NULL           | Stop  |

**Output:**

```
Length of Linked List: 4
```

---

### JavaScript Code

#### Version 1 — Simple / Clean (Only Required Function)

```javascript
function lengthOfLL(head) {
    let count = 0;
    let temp = head;

    while (temp !== null) {
        count++;
        temp = temp.next;
    }

    return count;
}
```

---

#### Version 2 — Deep / Explained (Complete Code)

```javascript
// Node structure
class Node {
    constructor(data) {
        this.data = data;   // value of node
        this.next = null;   // reference to next node
    }
}

// Function to calculate length of linked list
function lengthOfLL(head) {

    // Counter to track number of nodes
    let count = 0;

    // Temporary pointer for traversal
    let temp = head;

    // Traverse the entire list
    while (temp !== null) {

        // One node counted
        count++;

        // Move to next node
        temp = temp.next;
    }

    // Return final count
    return count;
}

// Main execution
// Creating linked list: 1 -> 2 -> 3 -> null
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);

// Calling length function
console.log("Length of Linked List:", lengthOfLL(head));
```

---

### Dry Run (JavaScript)

```
head → 1 → 2 → 3 → null
```

| Iteration | temp.data | count |
| --------- | --------- | ----- |
| 1         | 1         | 1     |
| 2         | 2         | 2     |
| 3         | 3         | 3     |
| End       | null      | stop  |

**Output:**

```
Length of Linked List: 3
```

---

### Time & Space Complexity (Deep Explanation)

#### Time Complexity — **O(n)**

**Why O(n):**

* The loop runs **once for each node**
* If the list has `n` nodes, the `while` loop executes exactly `n` times
* Each iteration does **constant work**:

  * increment counter
  * move pointer

There is **no way** to know the length of a singly linked list without visiting nodes, because:

* Nodes are not stored contiguously (unlike arrays)
* There is no built-in size property

So the minimum required work is visiting all nodes → **O(n)**.

---

#### Space Complexity — **O(1)**

**Why O(1):**

* Only two extra variables are used:

  * `count`
  * `temp`
* Their size does **not depend on number of nodes**
* No recursion
* No extra data structures (array, stack, map)

**Important clarification:**

* Memory used by the linked list itself is **not counted**
* Space complexity measures **extra memory**, not input size

Hence, constant extra space → **O(1)**.

---

### Interview Insight

> Length calculation is the **foundation** for:

* Finding middle node
* Checking even / odd length
* K-th node problems
* Validating positions for insert/delete
---

## 10. Searching in a Linked List

---

### Problem

Check whether a given **target value** exists in a linked list.

Return:

* `true` → if value is found
* `false` → if value is not found

---

### Rule (Do Not Break)

> Never traverse using `head` directly.
> Always use a temporary pointer.

**Why this rule matters here:**

* Search is a **read-only** operation
* Moving `head` will destroy access to the list
* We may need `head` again after search (insert, delete, print)

So:

* `head` → fixed reference
* `temp` → moving pointer

---

### Intuition (How to Think)

* Linked list has **no index**
* You **cannot jump** to any position
* Only option → start from beginning and move step-by-step

So we:

1. Start from head
2. Compare each node’s data with target
3. If match found → stop early
4. If list ends → target does not exist

---

### Traversal Logic (Step-by-Step)

1. Assign `temp = head`
2. While `temp` is not `null`

   * If `temp->data == target` → return `true`
   * Else move to next node
3. If loop finishes → return `false`

---

### Pseudocode (Before Code)

```
SEARCH(head, target):
    temp ← head

    WHILE temp is not NULL:
        IF temp.data == target:
            RETURN true
        temp ← temp.next

    RETURN false
```

---

### C++ Code

### Version 1 — Simple / Clean (Only Required Function, No Comments)

```cpp
bool search(Node* head, int target) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == target)
            return true;
        temp = temp->next;
    }

    return false;
}
```

---

#### Version 2 — Deep / Explained (Complete Program)

```cpp
#include <iostream>
using namespace std;

// Node structure
class Node {
public:
    int data;        // value stored
    Node* next;      // pointer to next node

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to search target in linked list
bool search(Node* head, int target) {

    // Temporary pointer to traverse list
    // We do NOT move head directly
    Node* temp = head;

    // Traverse the list node by node
    while (temp != nullptr) {

        // Compare current node's data with target
        if (temp->data == target) {
            // Target found, no need to continue
            return true;
        }

        // Move to next node
        temp = temp->next;
    }

    // Traversal finished and target not found
    return false;
}

int main() {
    /*
        Creating linked list:
        10 -> 20 -> 30 -> 40 -> NULL
    */

    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);

    int target = 30;

    // Searching for target
    bool found = search(head, target);

    if (found)
        cout << "Value found in linked list" << endl;
    else
        cout << "Value not found in linked list" << endl;

    return 0;
}
```

---

### Dry Run (C++)

Linked List:

```
10 -> 20 -> 30 -> 40 -> NULL
```

Target = `30`

| Step | temp->data | Comparison | Result     |
| ---- | ---------- | ---------- | ---------- |
| 1    | 10         | 10 == 30   | No         |
| 2    | 20         | 20 == 30   | No         |
| 3    | 30         | 30 == 30   | Yes → stop |

**Output:**

```
Value found in linked list
```

---

### JavaScript Code

#### Version 1 — Simple / Clean (Only Required Function)

```javascript
function search(head, target) {
    let temp = head;

    while (temp !== null) {
        if (temp.data === target)
            return true;
        temp = temp.next;
    }

    return false;
}
```

---

#### Version 2 — Deep / Explained (Complete Code)

```javascript
// Node structure
class Node {
    constructor(data) {
        this.data = data;   // value stored
        this.next = null;   // pointer to next node
    }
}

// Function to search value in linked list
function search(head, target) {

    // Temporary pointer for traversal
    let temp = head;

    // Traverse list one node at a time
    while (temp !== null) {

        // Compare node value with target
        if (temp.data === target) {
            // Target found, stop traversal
            return true;
        }

        // Move to next node
        temp = temp.next;
    }

    // Target not found after full traversal
    return false;
}

// Main execution
// Creating linked list: 5 -> 15 -> 25 -> null
let head = new Node(5);
head.next = new Node(15);
head.next.next = new Node(25);

let target = 15;

console.log(search(head, target)); // true
```

---

### Dry Run (JavaScript)

```
head → 5 → 15 → 25 → null
```

Target = `15`

| Iteration | temp.data | Match      |
| --------- | --------- | ---------- |
| 1         | 5         | No         |
| 2         | 15        | Yes → stop |

**Output:**

```
true
```

---

### Time & Space Complexity (Deep Explanation)

#### Time Complexity

##### Best Case — **O(1)**

**Why:**

* If target is present in the **first node (head)**
* Only **one comparison** is done
* Loop stops immediately

This is the **fastest possible scenario**.

---

##### Worst Case — **O(n)**

**Why:**

* Target is **not present**
  OR
* Target is present at **last node**

In both cases:

* We must visit **all `n` nodes**
* Each node requires one comparison

So total work grows linearly with list size → **O(n)**.

---

##### Average Case — **O(n)** (not O(n/2) in interviews)

**Important Interview Insight:**

* Although on average target may be found halfway (`n/2`),
* Big-O notation **drops constants**

So:

```
O(n/2) → O(n)
```

Hence average case is also **O(n)**.

---

#### Space Complexity — **O(1)**

**Why:**

* Only one extra pointer `temp`
* No recursion
* No auxiliary data structure

Memory usage does **not grow** with input size.

**Important clarification:**

* Linked list nodes are input data
* Space complexity counts only **extra memory used by algorithm**

So extra space is constant → **O(1)**.

---

### Interview Insight

> Searching in a linked list is always **linear**.
> If interviewer asks “can we do better?”
> Correct answer: **Not in a normal singly linked list**.

Better search requires:

* Sorted list + binary search (not possible directly)
* Extra structure (hashing, tree, skip list)

---

## 11. Q&A Synthesis (Mental Clarity)

### Q1. Why can’t we use indexes like arrays?

Because nodes are not stored contiguously.

---

### Q2. Why always return head?

Because the entire list is reachable from head.

---

### Q3. Why not modify head during traversal?

You lose the starting point permanently.

---

### Q4. Why traversal is used everywhere?

Linked List has **sequential access only**.

---

### Q5. Why Linked List fits stacks and queues?

Because size grows and shrinks dynamically.
