# HASHING – Basics Practice (Beginner Friendly)

This practice set helps you **apply hashing correctly** instead of memorizing patterns.

👉 Rule:  
**Always ask** → “Can I pre-store this?”

---

## PRACTICE QUESTIONS

---

### Q1. Frequency Query (Simple)

You are given an array and multiple queries.  
For each query, print how many times the number appears.

Example:
```
Array: 1 2 3 2 1 2
Query: 2 → Output: 3
```

---

### Q2. Count Distinct Elements

Given an array, count how many **unique elements** it contains.

---

### Q3. Check Element Presence

Given an array and a number `x`, check whether `x` exists in the array.

---

### Q4. Character Frequency (Lowercase Only)

Given a lowercase string, print frequency of each character **in input order**.

Example:
```
Input: abac
Output:
a -> 2
b -> 1
c -> 1
```

---

### Q5. Count Vowels Using Hashing

Given a string, count how many times each vowel appears.

---

### Q6. First Repeating Element

Given an array, print the **first element that repeats**.

Example:
```
Input: 1 2 3 2 1
Output: 2
```

---

### Q7. First Non-Repeating Character

Given a string, print the **first character that appears only once**.

Example:
```
Input: aabbcdde
Output: c
```

---

### Q8. Check If Two Arrays Are Equal (Order Doesn’t Matter)

Two arrays are given.  
Check if both contain **same elements with same frequencies**.

---

### Q9. Count Digits Using Hashing

Given a number, count frequency of each digit.

Example:
```
Input: 120312
Output:
1 -> 2
2 -> 2
0 -> 1
3 -> 1
```

---

### Q10. Remove Duplicates (Preserve Order)

Given an array, remove duplicates but keep first occurrence order.

---

---

# SOLUTIONS  
(Thinking → Code → Dry Run)

---

## Q1 Solution: Frequency Query

### Thinking
- Queries repeat
- Pre-store frequency once
- Answer in O(1)

### Code
```cpp
unordered_map<int,int> freq;

for(int x : arr)
    freq[x]++;

cout << freq[query];
```

### Dry Run
```
arr = [1 2 3 2 1 2]
freq:
1 -> 2
2 -> 3
3 -> 1
query = 2 → answer = 3
```

---

## Q2 Solution: Count Distinct Elements

### Thinking
- Unique elements = number of keys
- Hashing auto removes duplicates

### Code
```cpp
unordered_set<int> s;

for(int x : arr)
    s.insert(x);

cout << s.size();
```

### Dry Run
```
arr = [1 2 2 3]
set = {1,2,3}
size = 3
```

---

## Q3 Solution: Check Presence

### Thinking
- Hash table lookup is fast

### Code
```cpp
unordered_map<int,int> freq;

for(int x : arr)
    freq[x]++;

if(freq.find(x) != freq.end())
    cout << "Exists";
else
    cout << "Does not exist";
```

---

## Q4 Solution: Character Frequency (Lowercase)

### Thinking
- Fixed range (a–z)
- Array hashing fastest

### Code
```cpp
int hash[26] = {0};

for(char c : s)
    hash[c - 'a']++;

for(char c : s)
{
    if(hash[c - 'a'] > 0)
    {
        cout << c << " -> " << hash[c - 'a'] << endl;
        hash[c - 'a'] = 0; // avoid repeat print
    }
}
```

### Dry Run
```
s = abac
hash:
a=2 b=1 c=1
printed in input order
```

---

## Q5 Solution: Count Vowels

### Thinking
- Only vowels matter
- Hash only vowels

### Code
```cpp
unordered_map<char,int> freq;

for(char c : s)
{
    if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
        freq[c]++;
}

for(auto it : freq)
    cout << it.first << " -> " << it.second << endl;
```

---

## Q6 Solution: First Repeating Element

### Thinking
- First repeating = first element with frequency > 1
- Must scan original array

### Code
```cpp
unordered_map<int,int> freq;

for(int x : arr)
    freq[x]++;

for(int x : arr)
{
    if(freq[x] > 1)
    {
        cout << x;
        break;
    }
}
```

---

## Q7 Solution: First Non-Repeating Character

### Thinking
- Frequency first
- Then order scan

### Code
```cpp
unordered_map<char,int> freq;

for(char c : s)
    freq[c]++;

for(char c : s)
{
    if(freq[c] == 1)
    {
        cout << c;
        break;
    }
}
```

---

## Q8 Solution: Arrays Equality (Order Independent)

### Thinking
- Frequency of each element must match

### Code
```cpp
unordered_map<int,int> freq;

for(int x : a) freq[x]++;
for(int x : b) freq[x]--;

bool same = true;
for(auto it : freq)
{
    if(it.second != 0)
        same = false;
}

cout << (same ? "Equal" : "Not Equal");
```

---

## Q9 Solution: Digit Frequency

### Thinking
- Digits range = 0–9
- Perfect for array hashing

### Code
```cpp
int hash[10] = {0};

while(n > 0)
{
    hash[n % 10]++;
    n /= 10;
}

for(int i = 0; i < 10; i++)
{
    if(hash[i] > 0)
        cout << i << " -> " << hash[i] << endl;
}
```

---

## Q10 Solution: Remove Duplicates (Preserve Order)

### Thinking
- Need fast check + order
- Use set + array scan

### Code
```cpp
unordered_set<int> seen;

for(int x : arr)
{
    if(seen.find(x) == seen.end())
    {
        cout << x << " ";
        seen.insert(x);
    }
}
```

---

## FINAL HASHING MINDSET (CRITICAL)

Before coding, ask:

1. **Do queries repeat?** → Hash
2. **Small fixed range?** → Array hash
3. **Large values?** → unordered_map
4. **Need order?** → map or original array scan
5. **Collision fear?** → Ignore, STL handles it

