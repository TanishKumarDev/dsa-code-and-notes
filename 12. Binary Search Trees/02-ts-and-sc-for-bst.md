# TIME & SPACE COMPLEXITY ANALYSIS OF BST

*(All Operations · All Cases · Interview-Ready)*

---

## What We Covered Here

1. What time and space complexity in BST actually depend on
2. Height of BST — the **single most important factor**
3. Best, Average, and Worst case analysis
4. Complexity of core BST operations (Search / Insert / Delete)
5. Balanced vs Skewed BST complexity comparison
6. Recursive vs Iterative space complexity
7. Why BST can degrade to O(N)
8. Interview traps and correct wording
9. One-glance summary table

---

## 1. The One Rule That Controls Everything in BST

> **Time and Space Complexity of BST = O(height of tree)**

Not number of nodes directly.
**Height decides everything.**

Let:

```
N = number of nodes
H = height of BST
```

Then:

```
Time Complexity ≈ O(H)
Space Complexity ≈ O(H)
```

---

## 2. Height of BST in Different Scenarios

### Case 1: Balanced BST (Ideal Case)

```
Height H ≈ log₂(N)
```

Example:

```
            8
          /   \
         4     12
        / \    / \
       2   6  10  14
```

This is what interviewers **expect by default** unless stated otherwise.

---

### Case 2: Skewed BST (Worst Case)

```
Height H = N
```

Example (Right Skewed):

```
1
 \
  2
   \
    3
     \
      4
```

This behaves like a **linked list**.

---

## 3. Time Complexity of BST Operations

We analyze **Search, Insert, Delete** together because:

> They all follow **one downward path** from root to leaf.

---

### 🔹 Best Case — **O(1)**

When:

* Target element is at the **root**

Example:

```
Search(10)
Root = 10
→ Found immediately
```

So:

```
Best Case Time = O(1)
```

---

### 🔹 Average Case — **O(log N)**

When:

* BST is **reasonably balanced**
* Random insertion order
* Most practical scenarios

Why?

* At each comparison, **half of the tree is discarded**

So:

```
Average Case Time = O(log N)
```

This is the **expected interview answer**.

---

### 🔹 Worst Case — **O(N)**

When:

* BST is **completely skewed**
* Sorted insertion order (ascending / descending)

Example:

```
Insert: 1,2,3,4,5
```

Tree becomes:

```
1 → 2 → 3 → 4 → 5
```

So:

```
Worst Case Time = O(N)
```

---

## 4. Time Complexity Summary (Operations)

| Operation | Best | Average  | Worst |
| --------- | ---- | -------- | ----- |
| Search    | O(1) | O(log N) | O(N)  |
| Insert    | O(1) | O(log N) | O(N)  |
| Delete    | O(1) | O(log N) | O(N)  |

⚠️ Insert/Delete **do not rebalance** in a normal BST.

---

## 5. Space Complexity of BST (Very Important)

Space complexity comes from **recursion stack or iteration path**, not data storage.

---

### Recursive BST Operations

* Recursive calls go down one path
* Stack depth = height of tree

So:

```
Space Complexity = O(H)
```

Which becomes:

| Tree Type    | Space    |
| ------------ | -------- |
| Balanced BST | O(log N) |
| Skewed BST   | O(N)     |

---

### Iterative BST Operations

* No recursion
* Only one pointer moving down

So:

```
Auxiliary Space = O(1)
```

But still:

* Call stack avoided
* Tree height still affects **time**, not space

---

## 6. Balanced BST vs Normal BST (Interview Comparison)

| Feature  | Normal BST | Balanced BST        |
| -------- | ---------- | ------------------- |
| Height   | Can be N   | Always log N        |
| Search   | O(N) worst | O(log N) guaranteed |
| Insert   | O(N) worst | O(log N) guaranteed |
| Delete   | O(N) worst | O(log N) guaranteed |
| Examples | Simple BST | AVL, Red-Black      |

---

## 7. Why Interviewers Stress This Topic

Because they want to test:

* Do you know **why BST can fail**
* Do you understand **height dependency**
* Do you know when to suggest **balanced BST**

Correct interview statement:

> “BST operations are O(log N) on average, but degrade to O(N) in the worst case if the tree becomes skewed.”

---

## 8. Common Interview Traps (Avoid These)

❌ “BST operations are always O(log N)”
✔ Only for **balanced** or **average case**

❌ “Space complexity is O(N)”
✔ It is **O(H)** (height)

❌ “BST is always better than array”
✔ Sorted array + binary search also gives O(log N)

❌ “BST is self-balancing”
✔ Only AVL / Red-Black Trees are

---

## 9. One-Line Mental Model (Lock This)

> **BST complexity = length of the path you travel**

Short path → fast
Long path → slow

---

## 10. Final Summary Table (Exam + Interview Ready)

```
BST Time Complexity:
Best Case     → O(1)
Average Case  → O(log N)
Worst Case   → O(N)

BST Space Complexity:
Recursive    → O(H)
Iterative    → O(1)

Where:
H = height of tree
```

---

## Key Takeaway (VERY IMPORTANT)

> **BST performance depends on shape, not just size**
> Balanced shape → fast
> Skewed shape → slow

If you understand this, **you understand BST completely**.
