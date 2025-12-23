#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findContentChildren(vector<int> &student, vector<int> &cookie)
    {

        // Sort students by greed
        sort(student.begin(), student.end());

        // Sort cookies by size
        sort(cookie.begin(), cookie.end());

        int i = 0; // student index
        int j = 0; // cookie index

        while (i < student.size() && j < cookie.size())
        {

            // If cookie can satisfy student
            if (cookie[j] >= student[i])
            {
                i++; // student satisfied
            }

            // Cookie is used or discarded
            j++;
        }

        // Number of satisfied students
        return i;
    }
};

int main()
{
    Solution s;

    vector<int> student = {1, 2, 3}; // student greed factors
    vector<int> cookie = {1, 1};     // cookie sizes

    cout << s.findContentChildren(student, cookie);

    return 0;
}
