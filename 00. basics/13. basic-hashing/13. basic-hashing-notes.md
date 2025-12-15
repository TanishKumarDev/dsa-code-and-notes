# HASHING – Basics
---

## 1. WHAT IS HASHING?

### Concept

Hashing is a technique to store and retrieve data in **constant time** by using a special structure called a **hash table**.

It follows two main steps:

1. Pre-store (build / preprocess)
2. Fetch (answer queries in O(1))

Think of hashing as:

> Instead of searching again and again, store the answer once and reuse it instantly.

---

## 2. WHY DO WE NEED HASHING? (Motivation)

Array: `[1, 2, 1, 3, 2]`
Queries: `[1, 3, 4, 2, 10]`

### Brute Force Approach

For each query, scan the whole array.

Time Complexity = O(Q * N)
If N = 10^5 and Q = 10^5 → Total = 10^10 operations ❌ (Too Slow)

### Hashing Approach

Precompute frequency once, answer in O(1).

Time Complexity = O(N + Q) ✅ Efficient

---

## 3. NUMBER HASHING USING ARRAY

### Approach

* Create frequency array
* Index represents the number
* Value represents frequency

### Example

Array = [1,2,1,3,2]

Hash array after pre-store:
index: 0 1 2 3 4
value: 0 2 2 1 0

Query result = hash[number]

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    unordered_map<int, int> freq;

    // Count frequencies
    for(int x : arr)
        freq[x]++;

    // Print frequencies
    for(auto it : freq)
        cout << it.first << " " << it.second << endl;

    return 0;
}
```

```md
Dry Run

Input:

5
1 2 1 2 1


Frequency map:

1 → 3
2 → 2


Output:

1 3
2 2
```
### When to use

✅ Small range numbers
❌ Very large numbers like 10^9

---

## 4. CHARACTER HASHING

### Lowercase letters

#### Problem

Given a lowercase string, count the frequency of each character.

---

#### Concept

* Characters `'a'` to `'z'` → total **26**
* Map characters to indices:

  ```
  'a' → 0
  'b' → 1
  ...
  'z' → 25
  ```
* Use:

  ```cpp
  index = c - 'a'
  ```

---

#### Complete C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    // Hash array for lowercase letters
    int hash[26] = {0};

    // Pre-store frequencies
    for(char c : s)
        hash[c - 'a']++;

    // Print frequency of each character that appears
    for(int i = 0; i < 26; i++)
    {
        if(hash[i] > 0)
        {
            char ch = i + 'a';
            cout << ch << " -> " << hash[i] << endl;
        }
    }

    return 0;
}
```

---

#### Input

```
abcdabefc
```

---

#### Dry Run (VERY IMPORTANT)

String:

```
a b c d a b e f c
```

Initial hash array:

```
[0 0 0 0 0 0 ... 0]   // size = 26
```

Step-by-step updates:

| Character | Index (`c-'a'`) | Hash Array Change |
| --------- | --------------- | ----------------- |
| a         | 0               | hash[0] = 1       |
| b         | 1               | hash[1] = 1       |
| c         | 2               | hash[2] = 1       |
| d         | 3               | hash[3] = 1       |
| a         | 0               | hash[0] = 2       |
| b         | 1               | hash[1] = 2       |
| e         | 4               | hash[4] = 1       |
| f         | 5               | hash[5] = 1       |
| c         | 2               | hash[2] = 2       |

Final hash:

```
a → 2
b → 2
c → 2
d → 1
e → 1
f → 1
```

---

#### Output

```
a -> 2
b -> 2
c -> 2
d -> 1
e -> 1
f -> 1
```

---

#### Time & Space Complexity

* **Time:** O(N)
* **Space:** O(1) (fixed 26 size array)

---

## Important Notes (Interview Gold)

* Works **only for lowercase letters**
* Fastest possible method for character frequency
* If uppercase also present → size 52 or 256
* If full ASCII → `int hash[256]`

---

#### When to Use This

Use this approach when:

* Input is guaranteed lowercase letters
* You need maximum speed
* Frequency matters (anagrams, duplicates, unique chars)

---

### All ASCII characters

#### Concept

* ASCII has **256 possible characters**
* Each character’s ASCII value is already an integer `0–255`
* So we can directly use the character as an index

Key idea:

```cpp
hash[c]++
```

No mapping (`- 'a'`) needed.

This works for:

* lowercase
* uppercase
* digits
* symbols
* spaces (if handled carefully)

---

####  Complete C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    getline(cin, s);   // use getline to also include spaces

    // Hash array for all ASCII characters
    int hash[256] = {0};

    // Pre-store frequencies
    for(char c : s)
        hash[(unsigned char)c]++;

    // Print characters that appear
    for(int i = 0; i < 256; i++)
    {
        if(hash[i] > 0)
        {
            cout << "'" << (char)i << "' -> " << hash[i] << endl;
        }
    }

    return 0;
}
```

---

####  Input

```
aAbB@1a#
```

---

#### Dry Run (Step-by-step)

String:

```
a A b B @ 1 a #
```

ASCII values:

| Character | ASCII | Action         |
| --------- | ----- | -------------- |
| 'a'       | 97    | hash[97]++ → 1 |
| 'A'       | 65    | hash[65]++ → 1 |
| 'b'       | 98    | hash[98]++ → 1 |
| 'B'       | 66    | hash[66]++ → 1 |
| '@'       | 64    | hash[64]++ → 1 |
| '1'       | 49    | hash[49]++ → 1 |
| 'a'       | 97    | hash[97]++ → 2 |
| '#'       | 35    | hash[35]++ → 1 |

Final important entries in hash array:

```
'#' → 1
'1' → 1
'@' → 1
'A' → 1
'B' → 1
'a' → 2
'b' → 1
```

---

### Output

```
'#' -> 1
'1' -> 1
'@' -> 1
'A' -> 1
'B' -> 1
'a' -> 2
'b' -> 1
```

(Order depends on ASCII order, not input order.)

---

### Time & Space Complexity

* **Time:** O(N + 256) ≈ O(N)
* **Space:** O(1) (fixed size array)

---

### Important Notes (Very Important)

1. **Use `unsigned char`**

   ```cpp
   hash[(unsigned char)c]++;
   ```

   Prevents negative indexing for special characters.

2. This method:

   * Is faster than `unordered_map`
   * Uses fixed memory
   * Is safest for character problems

3. Use this when:

   * Character set is known (ASCII)
   * Performance matters
   * You don’t need ordering logic

---

### Comparison (Quick)

| Case           | Best Approach             |
| -------------- | ------------------------- |
| Only lowercase | `int hash[26]`            |
| Upper + lower  | `int hash[52]` or `256`   |
| Any character  | `int hash[256]`           |
| Unicode        | `unordered_map<char,int>` |


---

## 5. Hashing Large Numbers (Using Maps)

#### Why `map` / `unordered_map`?

* When values are very large (e.g. `10^9`)
* We **cannot create an array** of that size
* So we use **hash tables (maps)** to store only required keys

---

### Basic Syntax

```cpp
unordered_map<int, int> freq;

for(int x : arr)
    freq[x]++;
```

* **Key**   → array element
* **Value** → frequency of that element

---

### `map` vs `unordered_map`

| Structure       | Time     | Ordered | Worst Case  |
| --------------- | -------- | ------- | ----------- |
| `map`           | O(log N) | Yes     | Safe        |
| `unordered_map` | O(1) avg | No      | O(N) (rare) |

#### Rule of Thumb

* Use **`unordered_map` by default**
* If it gives **TLE**, switch to **`map`**

---

### Complete Example Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {1000000000, 5, 1000000000, 10, 5};

    unordered_map<int, int> freq;

    // Pre-store frequencies
    for(int x : arr)
        freq[x]++;

    // Print frequencies
    for(auto it : freq)
        cout << it.first << " -> " << it.second << endl;

    return 0;
}
```

---

### Dry Run

Array:

```
[1000000000, 5, 1000000000, 10, 5]
```

Frequency map:

```
1000000000 → 2
5 → 2
10 → 1
```

---

### Output

```
1000000000 -> 2
5 -> 2
10 -> 1
```

---

### Important Notes (Interview Gold)

* `unordered_map` stores **only needed keys**
* Memory efficient for sparse large numbers
* Order is **not guaranteed**
* Collision may cause O(N) in worst case (very rare)

---

### When to Use What

| Situation           | Use           |
| ------------------- | ------------- |
| Small range (≤10⁵)  | Array hashing |
| Large numbers (10⁹) | unordered_map |
| Need sorted output  | map           |
| Fastest solution    | unordered_map |

---

## 6. Time Complexity Selection Guide

| Scenario               | Best Choice     | Reason               |
| ---------------------- | --------------- | -------------------- |
| Small value range      | Array Hash      | O(1) access, fastest |
| Large values           | `unordered_map` | No size limit        |
| Sorted output required | `map`           | Maintains order      |
| Performance critical   | `unordered_map` | O(1) average         |

**Rule:**
Use `unordered_map` by default. Switch to `map` only if ordering or worst-case safety is required.

---


## 7. COLLISION EXPLAINED SIMPLY
#### Why Hashing Exists (Recall the Goal)

We want:

* **Fast lookup**
* Ideally **O(1)** time

Example:

```
Find frequency of 28
```

Array scan → O(N) ❌
Hashing → O(1) ✅

But hashing needs:

```
index = something(key)
```

---

#### The Core Problem (Why Collision Is Inevitable)

##### Suppose keys are large:

```
28, 38, 48, 139, 1008
```

If we directly use:

```
hash[28], hash[38], hash[48] ...
```

We need an array of size **1009** ❌
Not practical.

So we **compress** keys using a formula.

---

#### Compression Step (Where Collision Is Born)

We say:

```
Let hash table size = 10
index = key % 10
```

This is called the **Division Method**.

Now compute:

| Key | key % 10 |
| --- | -------- |
| 28  | 8        |
| 38  | 8        |
| 48  | 8        |

👉 **Problem appears here**

Different keys → **same index**

This is **NOT a mistake**
This is **MATHEMATICALLY UNAVOIDABLE**

Why?

Because:

* Infinite keys
* Finite table size

So collisions **must exist**.

---

#### What Exactly Is a Collision?

> **Collision = Two or more different keys want to live at the same index**

Index `8` says:

```
I can store only ONE value
But 28, 38, 48 all want index 8
```

Now what?

---

#### The Human Thinking (How Solution Was Invented)

A human thinks:

> “Okay… index 8 is popular.
> Instead of forcing ONE element,
> why not store **ALL of them together**?”

This is the birth of **Linear Chaining**.

---

#### Linear Chaining (Idea, Not Code)

Instead of:

```
hash[8] = ?
```

We change meaning to:

```
hash[8] = list of values
```

So index 8 becomes:

```
8 → [28, 38, 48]
```

Now:

* No data loss
* All values stored
* Still fast access

---

#### Why Is This a Good Solution?

##### To find 38:

1. Compute index → `38 % 10 = 8`
2. Go to hash[8]
3. Search inside small list `[28, 38, 48]`

This list is **usually very small**.

So:

* Average case → O(1)
* Worst case → O(N) (rare)

---

#### When Does Worst Case Happen?

Worst case happens if:

```
ALL keys map to SAME index
```

Example:

```
[8, 18, 28, 38, 48, 58, 68, ...]
```

Then:

```
hash[8] = [8,18,28,38,48,58,68,...]
```

Searching becomes:

```
O(N)
```

This is called **collision explosion**.

---

#### Why This Rarely Happens in Practice

Because:

* Hash table size is large
* Hash function is good
* Keys are usually random
* Table resizes automatically (in unordered_map)

That’s why:

> **Worst case exists in theory, but rarely in reality**

---

How `unordered_map` Handles This (Big Picture)

Internally:

* It uses **hash function**
* Then **chaining or probing**
* Automatically resizes table
* Rehashes elements

You **don’t see this**, but it happens.

That’s why you can safely write:

```cpp
unordered_map<int,int> mp;
mp[x]++;
```

---

#### Mental Model (Remember This)

```
Hashing = Compress big keys → small indices
Compression ⇒ Collision
Collision ⇒ Store multiple keys together
Solution ⇒ Linear Chaining
```

---
Perfect.
Now we will **IMPLEMENT collision handling**, but in the **right DSA way**:

**Thinking → intuition → problem → solution idea → algorithm → code → dry run**

No shortcuts.

---

#### COLLISION IMPLEMENTATION (LINEAR CHAINING)

##### Problem (Why we need this)

You are given **large numbers**, but you are allowed to use a **small hash table**.

Example input:

```
[28, 38, 48, 18, 8]
```

Constraint:

```
Hash table size = 10
```

So we **cannot** do:

```
hash[28], hash[38] ...
```

We must **compress** values.

---

##### Step 1: Intuition (DSA Thinking)

Ask yourself:

* I want fast lookup → hashing
* But my table is small
* Many numbers may map to the same index
* I must **not lose data**

So instead of:

```
One index → one value
```

I change the rule to:

```
One index → multiple values
```

This idea is called **Linear Chaining**.

---

##### Step 2: Hash Function (Very Important)

We choose a **simple hash function**:

```
index = value % table_size
```

Here:

```
table_size = 10
```

---

##### Step 3: See Where Collision Happens

Compute indices:

| Value | value % 10 |
| ----- | ---------- |
| 28    | 8          |
| 38    | 8          |
| 48    | 8          |
| 18    | 8          |
| 8     | 8          |

👉 All values want to go to **index 8**
👉 This is a **collision**

---

##### Step 4: Solution Idea (Human Logic)

Index 8 says:

> “I cannot store only one number.
> I will store a **list** of numbers.”

So:

```
hash[8] = [28, 38, 48, 18, 8]
```

This is **Linear Chaining**.

---

##### Step 5: Data Structure Choice

We need:

```
Array of lists
```

In C++:

```cpp
vector<vector<int>> hashTable;
```

* Outer vector → hash table
* Inner vector → chain (list of colliding elements)

---

##### Step 6: Algorithm

```
Create hash table of size 10 (each index is an empty list)

For each value in array:
    index = value % 10
    push value into hashTable[index]
```

---

##### Step 7: Pseudocode

```
hashTable = array of size 10 (each element is empty list)

for each value x:
    index = x % 10
    hashTable[index].append(x)
```

---

##### Step 8: Complete C++ Code (Collision Implemented)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Given array
    vector<int> arr = {28, 38, 48, 18, 8};

    int tableSize = 10;

    // Hash table with chaining
    vector<vector<int>> hashTable(tableSize);

    // Insert elements using division method
    for(int x : arr)
    {
        int index = x % tableSize;   // hash function
        hashTable[index].push_back(x);
    }

    // Print hash table
    for(int i = 0; i < tableSize; i++)
    {
        cout << "Index " << i << ": ";
        for(int val : hashTable[i])
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
```

---

##### Step 9: Dry Run (MOST IMPORTANT)

Initial:

```
hashTable = [ [], [], [], [], [], [], [], [], [], [] ]
```

Insert step-by-step:

###### Insert 28

```
28 % 10 = 8
hashTable[8] = [28]
```

###### Insert 38

```
38 % 10 = 8
hashTable[8] = [28, 38]
```

###### Insert 48

```
48 % 10 = 8
hashTable[8] = [28, 38, 48]
```

###### Insert 18

```
18 % 10 = 8
hashTable[8] = [28, 38, 48, 18]
```

###### Insert 8

```
8 % 10 = 8
hashTable[8] = [28, 38, 48, 18, 8]
```

---

##### Step 10: Output

```
Index 0:
Index 1:
Index 2:
Index 3:
Index 4:
Index 5:
Index 6:
Index 7:
Index 8: 28 38 48 18 8
Index 9:
```

---

##### Step 11: Time Complexity Analysis

* **Insertion (average):** O(1)
* **Search (average):** O(1)
* **Worst case:** O(N)
  (when all values collide into one index)

Worst case is **rare** with good hashing.

---

##### Step 12: Key Takeaway (VERY IMPORTANT)

```
Collision is NOT an error
Collision is expected
Solution = store multiple values at same index
This is Linear Chaining
```

This is **exactly** how:

* `unordered_map`
* hash tables
* real-world systems work internally

---

#### VERY IMPORTANT INTERVIEW LINE


> “What is collision and how do you handle it?”

Answer:

> Collision occurs when multiple keys map to the same hash index due to compression.
> It is handled using techniques like **linear chaining**, where each index stores a list of keys instead of a single value.

---

# PRACTICAL PROBLEM PATTERNS

## 8. COUNT FREQUENCY OF ARRAY ELEMENTS

### Problem

Given array, print frequency of each element

### Code

```cpp
vector<int> arr = {1,2,1,3,2,4};
unordered_map<int,int> freq;

for(int x : arr)
    freq[x]++;

for(auto it : freq)
    cout << it.first << " -> " << it.second << endl;
```

---

## 9. FIND HIGHEST FREQUENCY ELEMENT

```cpp
int maxFreq = 0, element;
for(auto it : freq)
{
    if(it.second > maxFreq)
    {
        maxFreq = it.second;
        element = it.first;
    }
}
```

---

## 10. FIND LOWEST FREQUENCY ELEMENT

```cpp
int minFreq = INT_MAX, element;
for(auto it : freq)
{
    if(it.second < minFreq)
    {
        minFreq = it.second;
        element = it.first;
    }
}
```

---

## 11. CHECK IF ELEMENT EXISTS

```cpp
if(freq.find(x) != freq.end())
    cout << "Exists";
else
    cout << "Does not exist";
```

---

## 12. UNIQUE ELEMENTS COUNT

```cpp
cout << freq.size();
```

---

## 13. REMOVE DUPLICATES USING HASHING

```cpp
unordered_set<int> s;
for(int x : arr)
    s.insert(x);
```

---

## 14. FIRST NON-REPEATING ELEMENT

```cpp
for(int x : arr)
{
    if(freq[x] == 1)
    {
        cout << x;
        break;
    }
}
```

---

## 15. MOST COMMON INTERVIEW QUESTIONS

1. Count frequency of characters
2. Find most frequent number
3. Find first unique element
4. Check if two strings are anagrams
5. Remove duplicates
6. Group anagrams
7. Subarray sum using hashmap
8. Longest substring without repetition

---

# DECISION LOGIC (INTERVIEW READY)

| Problem              | Use           |
| -------------------- | ------------- |
| Frequency            | unordered_map |
| Small range          | Array hash    |
| Sorted output        | map           |
| Strings              | char hash     |
| Performance critical | unordered_map |

---

## FINAL TAKEAWAYS

* Hashing converts O(N^2) → O(N)
* Best friend for frequency problems
* Always think: Can I pre-store?
* Use unordered_map unless ordering * needed
* Understand collision but don’t overthink it

---


## Note! 🚀
This is introductory material. For deeper understanding and implementations, refer to dedicated HASHING folders : `17. Hasshing`. 