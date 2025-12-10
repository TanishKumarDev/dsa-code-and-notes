// 01-remove-outermost-parentheses.cpp
// https://leetcode.com/problems/remove-outermost-parentheses/submissions/1849169513/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        // 'balance' will track current depth of parentheses.
        // balance == 0  -> we are outside any current primitive.
        // balance >= 1  -> we are inside some primitive.
        int balance = 0;

        // Result string to store answer.
        string result;

        // Traverse each character in the input string.
        for (char ch : s) {
            if (ch == '(') {
                // If balance > 0, means we are already inside
                // some primitive, so this '(' is NOT the outermost.
                // Hence, we should keep it.
                if (balance > 0) {
                    result.push_back(ch);
                }

                // Now we go one level deeper.
                balance++;
            } else {
                // For ')', we first move one level back (decrease depth).
                balance--;

                // After decreasing, if balance > 0,
                // this ')' is not closing the outermost primitive.
                // So we should keep it.
                if (balance > 0) {
                    result.push_back(ch);
                }
            }
        }

        // Finally, 'result' contains the string with
        // all outermost parentheses removed.
        return result;
    }
};

// You can use this main for quick local testing.
int main() {
    Solution sol;

    cout << sol.removeOuterParentheses("(()())(())") << endl;           // Output: ()()()
    cout << sol.removeOuterParentheses("(()())(())(()(()))") << endl;   // Output: ()()()()(())
    cout << sol.removeOuterParentheses("()()") << endl;                 // Output: (empty line)

    return 0;
}
