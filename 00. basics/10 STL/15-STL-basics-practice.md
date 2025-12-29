# 10. STL – Basics Practice (Beginner Friendly)

This practice file builds confidence in **STL fundamentals**:

* Containers
* Iterators
* Algorithms
* Basic operations

👉 Rule:
**Attempt first → then check solutions**

---

## PRACTICE QUESTIONS

### SECTION A — SEQUENCE CONTAINERS

---

### Q1. Vector Basics

**Problem**
Create a vector, insert 5 integers, and print them.

---

### Q2. Find Size of Vector

**Problem**
Given a vector, print its size.

---

### Q3. Access Elements in Vector

**Problem**
Print the first and last element of a vector.

---

### Q4. Reverse a Vector

**Problem**
Reverse a vector using STL.

---

---

### SECTION B — STRING (STL)

---

### Q5. String Length

**Problem**
Input a string and print its length using STL.

---

### Q6. Reverse a String

**Problem**
Reverse a string using STL.

---

---

### SECTION C — ASSOCIATIVE CONTAINERS

---

### Q7. Set Basics

**Problem**
Insert elements into a set and print them.

---

### Q8. Check Element in Set

**Problem**
Check if a number exists in a set.

---

---

### SECTION D — MAP

---

### Q9. Map Insert & Print

**Problem**
Store roll number → name mapping and print all entries.

---

### Q10. Frequency Count Using Map

**Problem**
Count frequency of elements in an array.

---

---

### SECTION E — UNORDERED CONTAINERS

---

### Q11. Unordered Set

**Problem**
Insert elements into unordered_set and print them.

---

---

### SECTION F — STL ALGORITHMS

---

### Q12. Sort an Array

**Problem**
Sort a vector using STL.

---

### Q13. Find an Element

**Problem**
Check if an element exists using `find()`.

---

### Q14. Count Occurrences

**Problem**
Count how many times an element appears.

---

---

### SECTION G — ITERATORS

---

### Q15. Iterator Basics

**Problem**
Print vector elements using iterators.

---

---

### SECTION H — STACK & QUEUE (ADAPTORS)

---

### Q16. Stack Operations

**Problem**
Push elements into stack and print top.

---

### Q17. Queue Operations

**Problem**
Push elements into queue and pop one.

---

---

### SECTION I — PRIORITY QUEUE

---

### Q18. Max Heap

**Problem**
Insert elements into priority_queue and print top.

---

### Q19. Min Heap

**Problem**
Create a min heap using priority_queue.

---

---

### SECTION J — MIXED PRACTICE

---

### Q20. Vector + Algorithm

**Problem**
Given a vector, find the maximum element using STL.

---

---

# SOLUTIONS (WITH THINKING + CODE)

---

## Q1 Solution — Vector Basics

**Thinking**

* Vector is dynamic array
* Use `push_back()`

```cpp
vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);
v.push_back(4);
v.push_back(5);

for(int x : v)
    cout << x << " ";
```

---

## Q2 Solution — Vector Size

**Thinking**

* `.size()` gives number of elements

```cpp
cout << v.size();
```

---

## Q3 Solution — First & Last Element

```cpp
cout << v.front() << endl;
cout << v.back();
```

---

## Q4 Solution — Reverse Vector

```cpp
reverse(v.begin(), v.end());
```

---

## Q5 Solution — String Length

```cpp
string s;
cin >> s;
cout << s.length();
```

---

## Q6 Solution — Reverse String

```cpp
reverse(s.begin(), s.end());
cout << s;
```

---

## Q7 Solution — Set Basics

**Thinking**

* Set stores unique sorted elements

```cpp
set<int> s;
s.insert(3);
s.insert(1);
s.insert(2);

for(int x : s)
    cout << x << " ";
```

---

## Q8 Solution — Check Element in Set

```cpp
if(s.find(2) != s.end())
    cout << "Found";
else
    cout << "Not Found";
```

---

## Q9 Solution — Map Insert & Print

```cpp
map<int, string> mp;
mp[1] = "A";
mp[2] = "B";

for(auto it : mp)
    cout << it.first << " " << it.second << endl;
```

---

## Q10 Solution — Frequency Count

```cpp
int arr[] = {1,2,2,3,1};
map<int,int> freq;

for(int x : arr)
    freq[x]++;

for(auto p : freq)
    cout << p.first << " -> " << p.second << endl;
```

---

## Q11 Solution — Unordered Set

```cpp
unordered_set<int> us;
us.insert(10);
us.insert(20);
us.insert(30);

for(int x : us)
    cout << x << " ";
```

---

## Q12 Solution — Sort Vector

```cpp
sort(v.begin(), v.end());
```

---

## Q13 Solution — Find Element

```cpp
if(find(v.begin(), v.end(), 3) != v.end())
    cout << "Found";
```

---

## Q14 Solution — Count Occurrence

```cpp
int cnt = count(v.begin(), v.end(), 2);
cout << cnt;
```

---

## Q15 Solution — Iterator Basics

```cpp
for(auto it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
```

---

## Q16 Solution — Stack

```cpp
stack<int> st;
st.push(10);
st.push(20);

cout << st.top();
```

---

## Q17 Solution — Queue

```cpp
queue<int> q;
q.push(1);
q.push(2);
q.pop();

cout << q.front();
```

---

## Q18 Solution — Max Heap

```cpp
priority_queue<int> pq;
pq.push(10);
pq.push(5);
pq.push(20);

cout << pq.top();
```

---

## Q19 Solution — Min Heap

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
pq.push(10);
pq.push(5);
pq.push(20);

cout << pq.top();
```

---

## Q20 Solution — Max Element

```cpp
cout << *max_element(v.begin(), v.end());
```

---

## FINAL STL CHEAT RULES

* Vector → dynamic array
* Set → unique + sorted
* Unordered → fast, no order
* Map → key-value
* Algorithms → reduce manual loops
* Iterators → pointer-like access

