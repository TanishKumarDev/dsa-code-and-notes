#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count frequency of each element in array
Approach: Use hashing with unordered_map
Time Complexity: O(N)
Space Complexity: O(N)
*/
void countFrequency(vector<int> &arr) {
    map<int, int> freq;
    // unordered_map<int, int> freq; // frequencies printed sorted by element

    // Step 1: Pre-store frequencies
    for(int i = 0; i < arr.size(); i++) {
        freq[arr[i]]++; 
    }
    // Step 2: Fetch the frequencies
    for(auto it : freq) {
        cout << it.first << " occurs -> " << it.second << " times"<< endl; // key -> value
    }
}

/*
Problem : Find the element with highest frequency
Approach: Hashing + maximum comparison
TC      : O(N)
SC      : O(N)
*/
pair<int,int> highestFrequency(vector<int> &arr) {
    unordered_map<int, int> freq;

    for(int x : arr) {
        freq[x]++;
    }

    int maxFreq = 0; // maximum frequency
    int maxElement = -1; // element with maximum frequency

    for(auto it : freq) {
        if(it.second > maxFreq) {
            maxFreq = it.second;
            maxElement = it.first;
        }
    }

    return {maxElement, maxFreq};
}

/*
Problem : Find element with lowest frequency
Approach: Hashing + minimum comparison
TC      : O(N)
SC      : O(N)
*/
pair<int,int> lowestFrequency(vector<int> &arr)
{
    unordered_map<int, int> freq;

    for(int x : arr) {
        freq[x]++;
    }

    int minFreq = INT_MAX;
    int minElement = -1;

    for(auto it : freq) {
        if(it.second < minFreq) {
            minFreq = it.second;
            minElement = it.first;
        }
    }

    return {minElement, minFreq};

}

/*
Problem : First non-repeating element
Approach: Hashing + order traversal
TC      : O(N)
SC      : O(N)
*/
int firstNonRepeating(vector<int> &arr)
{
    unordered_map<int, int> freq;

    for(int x : arr) {
        freq[x]++;
    }

    for(int x : arr) {
        if(freq[x] == 1) {
            return x;
        }
    }

    return -1; // No non-repeating element
}

/*
Problem : Remove duplicates from array while preserving order
Approach: Hash set to track visited elements
Time Complexity: O(N)
Space Complexity: O(N)
*/

vector<int> removeDuplicates(vector<int> &arr) {
    unordered_set<int> seen; // hash set to track visited elements
    vector<int> result; // result vector

    for(int x : arr) {
        if(seen.find(x) == seen.end()) { // if element is not in hash set
            seen.insert(x); // add element to hash set
            result.push_back(x); // add element to result
        }
    }

    return result;
}


/*
Problem : Check if two arrays are equal by frequency
Approach: Single hash map difference method
TC      : O(N)
SC      : O(N)
*/

bool areArraysEqual(vector<int> &arr1, vector<int> &arr2) {
    
    // if arrays have different sizes, they are not equal
    if(arr1.size() != arr2.size()) {
        return false;
    }

    // create two frequency maps
    unordered_map<int, int> freq;

    // count frequencies of elements in arr1
    for(int x : arr1) {
        freq[x]++;
    }

    // subtract frequencies of elements in arr2
    for(int x : arr2) {
        freq[x]--;
    }

    // check if all frequencies are 0
    for(auto it : freq) {
        if(it.second != 0) {
            return false;
        }
    }

    // if all frequencies are 0, arrays are equal
    return true;
}

/*
Problem : Check if two strings are anagrams
Approach: Character hashing
TC      : O(N)
SC      : O(1) [because fixed 26 size array]
*/
bool areAnagrams(string &s1, string &s2) {
    if(s1.size() != s2.size()) {
        return false;
    }

    int freq[26] = {0};

    for(char c : s1) {
        freq[c - 'a']++;
    }

    for(char c : s2) {
        freq[c - 'a']--;
    }

    for(int i=0; i < 26; i++) {
        if(freq[i] != 0) {
            return false;
        }
    }

    return true;
}

/*
Problem : First repeating element
Approach: Hash set to track seen elements
TC      : O(N)
SC      : O(N)
*/

int firstRepeating(vector<int> &arr)
{
    unordered_set<int> seen;

    for(int x : arr)
    {
        if(seen.find(x) != seen.end()) // If already seen, it's the first repeating element
        {
            return x;
        }
        else
        {
            seen.insert(x);
        }
    }

    return -1;
}

/*
Problem : Count distinct elements in array
Approach: Use unordered_set
Time Complexity: O(N)
Space Complexity: O(N)
*/
int countDistinct(vector<int> &arr)
{
    unordered_set<int> distinct;

    for(int x : arr){
        distinct.insert(x);
    } 

    return distinct.size();
}

/*
Problem : Find elements appearing exactly K times
Approach: Hashing + conditional filtering
TC      : O(N)
SC      : O(N)
*/

vector<int> elementsExactlyK(vector<int> &arr, int K)
{
    unordered_map<int, int> freq;
    vector<int> result;

    // Step 1: build frequency table
    for(int x : arr){
        freq[x]++;
    }

    // Step 2: check condition
    // Push elements with frequency exactly equal to K
    for(auto it : freq){
        if(it.second == K){
            result.push_back(it.first);
        }
    }

    return result;
}

int main() {
    vector<int> arr = {1, 2, 1, 3, 2, 2, 4};

    // Problem 1: Count frequency of each element in array
    cout << "✅ Problem 1: Count frequency of each element in array\n";
    countFrequency(arr);
    
    // Problem 2: Find the element with highest frequency
    cout << "\n✅ Problem 2: Find the element with highest frequency\n";
    auto highestFrequencyResult = highestFrequency(arr);
    
    cout << "Element with highest frequency: " << highestFrequencyResult.first << endl;
    cout << "Frequency: " << highestFrequencyResult.second << endl;

    // Problem 3: Find the element with lowest frequency
    cout << "\n ✅ Problem 3: Find the element with lowest frequency\n";
    auto lowestFrequencyResult = lowestFrequency(arr);
    
    cout << "Element with lowest frequency: " << lowestFrequencyResult.first << endl;
    cout << "Frequency: " << lowestFrequencyResult.second << endl;
    
    // Problem 4: First non-repeating element
    cout << "\n ✅ Problem 4: First non-repeating element\n";
    auto firstNonRepeatingResult = firstNonRepeating(arr);

    cout << "First non-repeating element: " << firstNonRepeatingResult << endl;

    // Problem 5: Remove duplicates from array while preserving order
    cout << "\n ✅ Problem 5: Remove duplicates from array while preserving order\n";
    auto removeDuplicatesResult = removeDuplicates(arr);

    cout << "Array with after removing duplicates: ";
    for(int x : removeDuplicatesResult) {
        cout << x << " ";
    }
    cout << endl;

    // Problem 6: Check if two arrays are equal by frequency
    cout << "\n ✅ Problem 6: Check if two arrays are equal by frequency\n";
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {1, 2, 3, 4, 5};
    bool areEqual = areArraysEqual(arr1, arr2);

    cout << "Are arrays equal by frequency? " << (areEqual ? "Yes" : "No") << endl;
    
    // Problem 7: Check if two strings are anagrams
    cout << "\n ✅ Problem 7: Check if two strings are anagrams\n";
    string s1 = "listesn";
    string s2 = "silent";

    bool areAnagramsResult = areAnagrams(s1, s2);

    cout << "Are strings anagrams? " << (areAnagramsResult ? "Yes" : "No") << endl;
    
    // Problem 8: First repeating element
    cout << "\n ✅ Problem 8: First repeating element\n";
    auto firstRepeatingResult = firstRepeating(arr);

    cout << "First repeating element: " << firstRepeatingResult << endl;
    
    // Problem 9: Count distinct elements in array
    cout << "\n ✅ Problem 9: Count distinct elements in array\n";
    auto countDistinctResult = countDistinct(arr);

    cout << "Number of distinct elements: " << countDistinctResult << endl;
    
    // Problem 10: Find elements appearing exactly K times
    cout << "\n ✅ Problem 10: Find elements appearing exactly K times\n";
    int K = 3;
    auto elementsExactlyKResult = elementsExactlyK(arr, K);

    cout << "Elements appearing exactly " << K << " times: ";
    for(int x : elementsExactlyKResult) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
