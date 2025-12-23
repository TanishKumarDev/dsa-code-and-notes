#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {

        int minOpen = 0; // minimum possible '(' count
        int maxOpen = 0; // maximum possible '(' count

        for (char c : s)
        {

            if (c == '(')
            {
                minOpen++;
                maxOpen++;
            }
            else if (c == ')')
            {
                minOpen--;
                maxOpen--;
            }
            else
            {              // '*'
                minOpen--; // treat as ')'
                maxOpen++; // treat as '('
            }

            // Too many closing brackets
            if (maxOpen < 0)
                return false;

            // Clamp minOpen
            minOpen = max(minOpen, 0);
        }

        return minOpen == 0;
    }
};

int main()
{
    string s = "(*))";

    Solution sol;
    if (sol.isValid(s))
        cout << "Valid string\n";
    else
        cout << "Invalid string\n";

    return 0;
}
