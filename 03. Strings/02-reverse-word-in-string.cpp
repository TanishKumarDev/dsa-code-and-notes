// https://leetcode.com/problems/reverse-words-in-a-string/description/

#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Example :
// Constraint :

// 🔴 Approach 1 Brute Force :
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
// Code :
string reverseWordsBrute(string s)
{
    vector<string> words; // To store extracted words
    string word = "";     // Current word builder

    // Step 1: Extract words manually
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != ' ')
        {
            // If char is not space, add to current word
            word += s[i];
        }
        else if (!word.empty())
        {
            // If space occurs and word is ready
            words.push_back(word);
            word = ""; // reset word buffer
        }
    }

    // Push last collected word (if exists)
    if (!word.empty())
    {
        words.push_back(word);
    }

    // Step 2: Reverse list of words
    reverse(words.begin(), words.end());

    // Step 3: Build final answer
    string result = "";
    for (int i = 0; i < words.size(); i++)
    {
        result += words[i];
        if (i < words.size() - 1)
            result += " "; // add space only between words
    }

    return result;
}

// 🔵 Approach 2 Better :
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
// Code :

// 🟢 Approach 3 Optimal:
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
// Code :
string reverseWordsOptimal(string s)
{
    string result = "";
    int i = s.size() - 1;

    while (i >= 0)
    {

        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ')
            i--;

        if (i < 0)
            break; // no more words

        int end = i; // end index of current word

        // Move to the start of the word
        while (i >= 0 && s[i] != ' ')
            i--;

        // Extract the word
        string word = s.substr(i + 1, end - i);

        // If result not empty, add space before appending next word
        if (!result.empty())
            result += " ";

        // Append the word
        result += word;
    }

    return result;
}
int main()
{
    
    return 0;
}

// ✍️ DRY RUN
// 🤔 Followup Q/A
// 1.