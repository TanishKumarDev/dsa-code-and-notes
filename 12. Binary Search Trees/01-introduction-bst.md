# INTRODUCTION TO BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. What a Binary Search Tree (BST) is
2. Core BST property (the rule that defines everything)
3. Why **every subtree** is also a BST
4. Difference between Binary Tree and BST
5. Why we need BST (problem with Binary Tree)
6. Height intuition: why BST is faster
7. How searching works in BST (step-by-step thinking)
8. Relation between BST and Binary Search on arrays
9. Important notes about duplicate values
10. Interview mindset & common confusions

---

## 1. What Is a Binary Search Tree?

A **Binary Search Tree (BST)** is a **special type of Binary Tree** where:

> The tree is arranged in a way that makes **searching efficient**.

It is **not just about having two children** —
it is about **how values are placed**.

---

## 2. The Core BST Rule (MOST IMPORTANT)

For **every node** in a BST:

```
Left Subtree Values  <  Node Value  <  Right Subtree Values
```

This rule must be true:

* at the root
* at every internal node
* inside every subtree

If this rule breaks **anywhere**, it is **not a BST**.

---

## 3. Visual Understanding of the Rule

Example BST:

```
            8
          /   \
         3     10
        / \      \
       1   6      14
          / \     /
         4   7   13
```

Check one node (say `6`):

* Left child (`4`) < 6
* Right child (`7`) > 6

✔ Rule satisfied

This same check works for **every node**.

---

## 4. Very Important Insight (Interview Gold)

> **Every subtree of a BST is itself a BST**

Why?

Because:

* Left subtree still follows `< root`
* Right subtree still follows `> root`
* And the rule applies recursively

This recursive property is what enables:

* fast search
* fast insert
* fast delete

---

## 5. Binary Tree vs Binary Search Tree (Clear Difference)

| Feature     | Binary Tree       | Binary Search Tree |
| ----------- | ----------------- | ------------------ |
| Value order | No rule           | Strict ordering    |
| Search      | O(N)              | O(log N) (avg)     |
| Structure   | Any shape         | Ordered            |
| Purpose     | General hierarchy | Fast search        |

⚠️ **Every BST is a Binary Tree**
❌ **Not every Binary Tree is a BST**

---

## 6. Why Do We Need BST? (Core Motivation)

Problem with a **normal Binary Tree**:

* No ordering
* To search an element → may need to visit **all nodes**
* Worst case time = **O(N)**

---

### Example (Binary Tree Search)

```
            10
           /  \
          5    20
         / \
        15  1
```

Searching `1`:

* No rule
* You may need to check **every node**

---

## 7. Why BST Is Faster (Key Advantage)

In a BST, we **discard half of the tree at every step**.

That’s the game changer.

---

### BST Search Example

```
            10
          /    \
         5      20
        / \       \
       2   8       30
```

Search for `30`:

1. Compare with `10` → greater → go right
2. Compare with `20` → greater → go right
3. Found `30`

You **never touch the left subtree**.

---

## 8. Height Intuition (Very Important)

In an **average BST**:

```
Height ≈ log₂(N)
```

That means:

* Search
* Insert
* Delete

All take **O(log N)** time (average case).

---

### Worst Case (Important to Know)

If BST becomes **skewed**:

```
1
 \
  2
   \
    3
     \
      4
```

Height = `N`
Time = **O(N)**

That’s why **balanced BSTs** exist (AVL, Red-Black).

---

## 9. BST and Binary Search (Connection)

BST works on the **same principle** as Binary Search in arrays:

| Binary Search    | BST                 |
| ---------------- | ------------------- |
| Middle element   | Root                |
| Left half        | Left subtree        |
| Right half       | Right subtree       |
| Divide & conquer | Recursive branching |

That’s why it’s called **Binary Search Tree**.

---

## 10. Duplicate Values in BST (Important Note)

In **standard BST**:

* ❌ Duplicate values are **not allowed**

But in some implementations:

* Duplicates can go:

  * always to left
  * always to right
  * handled via frequency count

👉 **Interview default assumption**:
**BST has unique values unless stated otherwise**

---

## 11. Common Beginner Confusions (Clear Them Now)

❌ “BST means sorted tree”
✔ No — **inorder traversal** of BST gives sorted order

❌ “Root must be middle value”
✔ No — depends on insertion order

❌ “BST is always balanced”
✔ No — only balanced BSTs guarantee log N height

---

## 12. Interview Mindset (Lock This)

When interviewer says **BST**, immediately think:

* Ordered structure
* Left < Node < Right
* Logarithmic search (average)
* Inorder traversal = sorted sequence

---

## Key Takeaway (VERY IMPORTANT)

> **BST is not about shape — it’s about order**
> If order is respected at every node, operations become fast.

---
