# Reverse Words in a String

*(TUF + LeetCode Standard)*

---

## 1. Problem Statement

**English:**
Given a string `s` containing letters, digits, and spaces. A **word** is a sequence of non-space characters. Words are separated by **one or more spaces**.

Your job:
Return a **new string where the words appear in reverse order**, joined by **exactly one space**, with **no leading or trailing spaces**.

**Hinglish:**
String mein words diye hain, aur beech mein extra spaces bhi ho sakte hain.
Tumhe **words ka order reverse** karna hai, but:

* Extra spaces hatao
* Words ke beech **sirf ek space** rakho
* Start/end mein koi space nahi hona chahiye

---

## 2. Input / Output / Constraints

### Input Example:

`s = "  amazing   coding skills  "`

### Output:

`"skills coding amazing"`

### Constraints:

* `1 ≤ |s| ≤ 10^5`
* May contain multiple spaces
* Must handle uppercase/lowercase/digits

---

## 3. Examples

| Input                | Output              |
| -------------------- | ------------------- |
| `"the sky is blue"`  | `"blue is sky the"` |
| `"  hello world  "`  | `"world hello"`     |
| `"a good   example"` | `"example good a"`  |
| `"  "`               | `""`                |
| `"one"`              | `"one"`             |

---

## 4. Intuition & Core Thinking

This is a **string formatting + word extraction + reverse** problem.

### Main Challenges:

1. Extra spaces in between words
2. Leading & trailing spaces
3. Word extraction without losing characters
4. Efficient reversal for large input

### Two Possible Strategies:

#### Approach 1 (Brute / Simple):

* Extract words using traversal
* Store in vector
* Reverse vector
* Join with single spaces

#### Approach 2 (Optimal):

* Start scanning **from the back**
* Extract words one by one in reversed order
* Append directly to output (no need to reverse again)

---

## 5. Approach 1 (Brute – Using word collection)

### Intuition:

* Build each word manually (ignore extra spaces)
* Store words
* Reverse list
* Join them with one space

### Why acceptable?

* Easy and clean
* Perfect for understanding
* Time O(n), Space O(n)

---

### C++ Code (Brute) – With Detailed Comments

```cpp
// 02-reverse-words-brute.cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        vector<string> words;   // To store extracted words
        string word = "";       // Current word builder

        // Step 1: Extract words manually
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                // If char is not space, add to current word
                word += s[i];
            }
            else if (!word.empty()) {
                // If space occurs and word is ready
                words.push_back(word);
                word = ""; // reset word buffer
            }
        }

        // Push last collected word (if exists)
        if (!word.empty()) {
            words.push_back(word);
        }

        // Step 2: Reverse list of words
        reverse(words.begin(), words.end());

        // Step 3: Build final answer
        string result = "";
        for (int i = 0; i < words.size(); i++) {
            result += words[i];
            if (i < words.size() - 1) result += " ";  // add space only between words
        }

        return result;
    }
};
```

---

## 6. Approach 2 (Optimal – Scan from Backwards)

### Intuition:

Instead of storing all words and reversing later,
we **scan from the right** and directly append words to result.

Steps:

1. Move pointer `i` from end → start
2. Skip spaces
3. Identify word end
4. Move left to get word start
5. Append word to result
6. Add space *only if* something already added

### Why faster?

* No array/vector needed
* We avoid separate reversing step
* Still O(n) time, O(1) extra space (excluding result)

---

### C++ Code (Optimal)

```cpp
// 02-reverse-words-optimal.cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string result = "";
        int i = s.size() - 1;

        while (i >= 0) {

            // Skip trailing spaces
            while (i >= 0 && s[i] == ' ') i--;

            if (i < 0) break;  // no more words

            int end = i;  // end index of current word

            // Move to the start of the word
            while (i >= 0 && s[i] != ' ') i--;

            // Extract the word
            string word = s.substr(i + 1, end - i);

            // If result not empty, add space before appending next word
            if (!result.empty()) result += " ";

            // Append the word
            result += word;
        }

        return result;
    }
};
```

---

## 7. Dry Run (Optimal)

### Input:

`" amazing   coding skills "`

Start from right:

| Step                        | Char            | Action        |
| --------------------------- | --------------- | ------------- |
| i=23                        | ' '             | skip spaces   |
| i=22                        | 's'             | word end = 22 |
| move left to i=17           | word = "skills" |               |
| append `"skills"` to result |                 |               |

Next word:

* Skip spaces
* Find `"coding"`
* Append → `"skills coding"`

Next word:

* Skip spaces
* Find `"amazing"`
* Append → `"skills coding amazing"`

Done.

Final output: `"skills coding amazing"`

---

## 8. Edge Cases

| Case              | Input               | Output          |
| ----------------- | ------------------- | --------------- |
| Empty/Spaces Only | `"     "`           | `""`            |
| Single Word       | `"hello"`           | `"hello"`       |
| Multiple Spaces   | `"a   b   c"`       | `"c b a"`       |
| Leading/Trailing  | `"  hello world  "` | `"world hello"` |

All handled cleanly.

---

## 9. Complexity

| Approach    | Time     | Space                       |
| ----------- | -------- | --------------------------- |
| Brute       | O(N)     | O(N)                        |
| **Optimal** | **O(N)** | **O(1)** (excluding output) |

---

## 10. Interview Strategy

What to say:

1. “Words may have multiple spaces between them.
   I will extract words and reverse their order.”

2. “Optimal approach: scanning from the back avoids extra storage.”

3. “Edge cases like leading/trailing/multiple spaces are handled naturally.”

4. “Time is O(n) because each character is read at most twice.”

5. “Space is O(1) (ignoring output).”

---

## 11. JavaScript Version (Optimal)

```javascript
function reverseWords(s) {
    let i = s.length - 1;
    let result = [];

    while (i >= 0) {

        // Skip spaces
        while (i >= 0 && s[i] === ' ') i--;

        if (i < 0) break;

        let end = i;

        // Move left until space or start
        while (i >= 0 && s[i] !== ' ') i--;

        // Extract word
        let word = s.substring(i + 1, end + 1);
        result.push(word);
    }

    // Join reversed words with single space
    return result.join(' ');
}
```

---
