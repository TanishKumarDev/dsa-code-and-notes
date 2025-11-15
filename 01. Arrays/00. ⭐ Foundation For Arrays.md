# PART 1: ARRAY BASICS

---

## 1. What is an Array?

An array is a **contiguous block of memory** where elements are stored at consecutive indexes and all have the same data type.

Example:

```
Index:  0  1  2  3  4
Value: 10 20 30 40 50
```

### Properties

* Fixed size
* Fast indexing (O(1))
* Stored sequentially in memory
* Can be accessed using `arr[index]`

### Time Complexities

| Operation              | TC   |
| ---------------------- | ---- |
| Access                 | O(1) |
| Traversal              | O(n) |
| Searching              | O(n) |
| Insert at end          | O(1) |
| Insert at start/middle | O(n) |
| Delete at index        | O(n) |

### Space Complexity

* SC = O(n) for storing n elements.

---

## 2. CRUD Operations in Array

CRUD = Create, Read, Update, Delete

### Create

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

### Read (access)

```cpp
cout << arr[2]; // prints 3
```

### Update

```cpp
arr[1] = 10;  // now arr = {1,10,3,4,5}
```

### Delete (shift elements left)

```cpp
int pos = 2;
for(int i = pos; i < n-1; i++){
    arr[i] = arr[i+1];
}
n--;
```

---

# PART 2: IMPORTANT TECHNIQUES USED IN ARRAY PROBLEMS


* Two Pointers
* Hashing
* Frequency Map
* Set / unordered_set
* XOR
* Sum Accumulation
* Prefix Sum (important for negatives)
* continue...

---

# 3. TWO POINTER TECHNIQUE

---

## Intuition

Use two indexes that move in some direction to reduce time complexity.

Most used when:

* Arrays are sorted
* You need to compare two elements
* You need a window (sliding window)

### Example Problem

Find if two numbers in sorted array sum to target K.

### Code

```cpp
bool twoPointer(vector<int>& arr, int k){
    int left = 0;
    int right = arr.size() - 1;

    while(left < right){
        int sum = arr[left] + arr[right];

        if(sum == k) return true;
        else if(sum < k) left++;
        else right--;
    }
    return false;
}
```

### Dry Run

arr = [1,2,4,7,11], k=9

| Step | left | right | sum     | Action          |
| ---- | ---- | ----- | ------- | --------------- |
| 1    | 0    | 4     | 1+11=12 | sum>k → right-- |
| 2    | 0    | 3     | 1+7=8   | sum<k → left++  |
| 3    | 1    | 3     | 2+7=9   | Found           |

### TC: O(n)

### SC: O(1)

Used in:

* Remove duplicates
* Intersection
* Merge sorted arrays
* Sliding window
* Longest subarray with sum K (positive only)

---

# 4. HASHING TECHNIQUE

---

## Intuition

Store elements in a hash table for **fast lookup** (O(1)).

### Example Problem

Check if an element exists in array.

### Code

```cpp
unordered_set<int> s;
for(int x : arr) s.insert(x);

if(s.count(10)) cout << "present";
```

### Dry run

arr = [4,1,2,1,2]

Set = {4,1,2}

### TC: O(n)

### SC: O(n)

Used in:

* Missing number
* Single number
* Union / intersection
* Subarray sum
* Duplicate detection

---

# 5. FREQUENCY MAP (unordered_map)

---

## Intuition

Store how many times each element appears.

### Example Problem

Find number appearing once (others twice)

### Code

```cpp
unordered_map<int,int> freq;
for(int x: arr) freq[x]++;

for(auto p: freq){
    if(p.second == 1) return p.first;
}
```

### Dry run

arr = [4,1,2,1,2]

Map = {4:1, 1:2, 2:2}

Answer = 4

### TC: O(n)

### SC: O(n)

Used in:

* Single number
* Intersection with frequency
* Count frequency of characters
* Majority element

---

# 6. SET / UNORDERED_SET

---

### set = sorted + unique

### unordered_set = unsorted + unique (O(1) avg)

Used heavily in:

* Union (avoid duplicates)
* Missing numbers
* Keep track of seen prefix sums

### Code

```cpp
set<int> s;              // sorted unique
unordered_set<int> us;   // faster, unique
```

---

# 7. XOR TECHNIQUE

---

## Intuition

XOR cancels out duplicates.

Important rules:

* x ^ x = 0
* x ^ 0 = x

### Example Problem

Find single number when all others appear twice.

### Code

```cpp
int ans = 0;
for(int x : arr) ans ^= x;
return ans;
```

### Dry Run

arr = [4,1,2,1,2]

| Step | ans       |
| ---- | --------- |
| 0    | 0         |
| 1    | ans^4 = 4 |
| 2    | ans^1 = 5 |
| 3    | ans^2 = 7 |
| 4    | ans^1 = 6 |
| 5    | ans^2 = 4 |

Answer = 4

### TC: O(n)

### SC: O(1)

Used in:

* Missing number (xor version)
* Single number
* Find two numbers appearing once

---

# 8. SUM ACCUMULATION

---

## Intuition

Grow sum step by step instead of recalculating.

### Example

Longest subarray with sum K (better approach)

### Code

```cpp
int sum = 0;
for(int j=i;j<n;j++){
    sum += arr[j];
}
```

Used in:

* Better O(n²) subarray sum
* Kadane’s algorithm

---

# 9. PREFIX SUM (My WEAKNESS)

---

## 1. Meaning of Prefix Sum

Prefix Sum means:

Sum of all elements **from index 0 to index i**.

Formula:

```cpp
prefix[i] = arr[0] + arr[1] + ... + arr[i]
```

Example array:

```cpp
arr     = [2,   3,   -1,   4]
index    0    1     2     3
```

Prefix sum array:

```cpp
prefix = [2,  5,   4,    8]
```

Explanation:

* prefix[0] = 2
* prefix[1] = 2 + 3 = 5
* prefix[2] = 2 + 3 - 1 = 4
* prefix[3] = 2 + 3 - 1 + 4 = 8

---

## 2. Why Prefix Sum Exists (Purpose)

The main goal:

To quickly find **sum of any subarray** in O(1) time.

Without prefix sum:

* sum of arr[l..r] = O(n)

With prefix sum:

* sum of arr[l..r] = prefix[r] - prefix[l-1]
* Time = O(1)

Example:
Find sum of index 1 to 3:

```cpp
prefix[3] - prefix[0] = 8 - 2 = 6
```

---

## 3. How to Build Prefix Sum Array

Code:

```cpp
vector<int> prefix(n);
prefix[0] = arr[0];

for(int i = 1; i < n; i++){
    prefix[i] = prefix[i-1] + arr[i];
}
```

---

## 4. Use-Case 1: Quick Range Sum Query

Sum of arr[l..r] instantly.

Formula:

```cpp
if l == 0:
    sum = prefix[r]
else:
    sum = prefix[r] - prefix[l-1]
```

Example:
arr = [2,3,-1,4]
prefix = [2,5,4,8]

Query: sum of arr[1..3]

```cpp
prefix[3] - prefix[0] = 8 - 2 = 6
```

---

## 5. Use-Case 2: Longest Subarray with Sum K (NEGATIVES INCLUDED)

This is the most important use-case in DSA.

You are using this in:

```cpp
15. Longest Subarray with Sum K (Positives + Negatives)
```

Why prefix sum needed here?

Because if:

```cpp
prefix[i] - prefix[j] = k
```

Then:
Sum of subarray (j+1 to i) is k.

Rearrange:

```cpp
prefix[j] = prefix[i] - k
```

Meaning:

If at index i,
we find that some earlier prefix value equals prefix[i] - k,
then the subarray between them gives sum k.

---

## 6. Prefix Sum + Hash Map (Core Logic)

We keep a map:

```cpp
prefixSum → earliest index where it occurred
```

Why earliest index?

Because earliest gives **longest possible** subarray.

---

## 7. Full Code

```cpp
int getLongestSubarray(vector<int>& arr, int k) {
    unordered_map<int,int> mp;   // prefixSum -> first index
    int sum = 0;
    int maxLen = 0;

    for(int i = 0; i < arr.size(); i++){
        sum += arr[i];

        // Case 1: subarray from 0..i
        if(sum == k){
            maxLen = max(maxLen, i+1);
        }

        // Case 2: sum-k exists earlier
        if(mp.count(sum - k)){
            maxLen = max(maxLen, i - mp[sum-k]);
        }

        // Store earliest occurrence
        if(mp.find(sum) == mp.end()){
            mp[sum] = i;
        }
    }

    return maxLen;
}
```

---

## 8. Detailed Dry Run (Very Important)

arr = [1, 2, -1, 2, 3]
k = 3
sum = 0
mp = {}

---

i = 0 → arr[0] = 1
sum = 1

Case: sum != k
Case: sum-k = 1-3 = -2 not in map
Add sum=1 → index 0
mp: {1:0}

---

i = 1 → arr[1] = 2
sum = 1 + 2 = 3

Case: sum == k
maxLen = 2 (subarray 0..1)

Add sum=3 → index 1
mp: {1:0, 3:1}

---

i = 2 → arr[2] = -1
sum = 3 - 1 = 2

Case: sum != k
Case: sum-k = 2-3 = -1 not in map
Add sum=2 at index 2
mp: {1:0, 3:1, 2:2}

---

i = 3 → arr[3] = 2
sum = 2 + 2 = 4

Check sum-k = 4 - 3 = 1
1 is in map at index 0
Length = 3 - 0 = 3
maxLen = 3

Add sum=4 at index 3
mp: {1:0,3:1,2:2,4:3}

---

i = 4 → arr[4] = 3
sum = 4 + 3 = 7

Check sum-k = 7-3 = 4
4 exists at index 3
Length = 4 - 3 = 1
maxLen remains 3

---

Final answer = 3

---

## 9. Summary (Your Quick Reference)

| Concept                     | Meaning                                  |
| --------------------------- | ---------------------------------------- |
| Prefix sum                  | cumulative sum from 0 to i               |
| Range sum                   | prefix[r] - prefix[l-1]                  |
| Longest subarray with sum k | prefix[i] - prefix[j] = k                |
| Use of map                  | stores earliest index of each prefix sum |
| Handles negatives           | yes                                      |
| TC                          | O(n)                                     |
| SC                          | O(n)                                     |
---

# PART 3 SUMMARY

| Concept             | When Used              | TC    | SC   |
| ------------------- | ---------------------- | ----- | ---- |
| Two Pointer         | sorted arrays, windows | O(n)  | O(1) |
| Hashing             | fast lookup            | O(n)  | O(n) |
| Freq map            | count elements         | O(n)  | O(n) |
| Set / unordered_set | unique elements        | O(n)  | O(n) |
| XOR                 | find single number     | O(n)  | O(1) |
| Sum accumulation    | improve brute force    | O(n²) | O(1) |
| Prefix sum          | negatives allowed      | O(n)  | O(n) |

---