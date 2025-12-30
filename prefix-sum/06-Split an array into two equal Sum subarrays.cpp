#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Approach 1: Brute Force
------------------------------------------------------------
Idea:
- Har possible split point try karo
- Left part ka sum nikalo
- Right part ka sum nikalo
- Agar dono equal ho jaayein → split mil gaya

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
int findSplitPointBruteForce(int arr[], int n)
{
    int leftSum = 0;

    // Iterate till n-1 because split ke baad
    // right subarray empty nahi hona chahiye
    for (int i = 0; i < n - 1; i++)
    {
        // Current element ko left sum me add karo
        leftSum += arr[i];

        // Right sum ko har baar fresh calculate karna
        int rightSum = 0;
        for (int j = i + 1; j < n; j++)
        {
            rightSum += arr[j];
        }

        // Agar left aur right sum equal ho
        // to i+1 right subarray ka starting index hoga
        if (leftSum == rightSum)
        {
            return i + 1;
        }
    }

    // Agar koi valid split nahi mila
    return -1;
}

/*
------------------------------------------------------------
Approach 2: Optimal (Prefix Sum / Total Sum idea)
------------------------------------------------------------
Idea:
- Pehle poore array ka total sum nikaal lo
- Left sum ko gradually build karo
- Right sum = totalSum - leftSum
- Agar left == right → split mil gaya

Time Complexity: O(n)
Space Complexity: O(1)
*/
int findSplitPointOptimal(int arr[], int n)
{
    int totalSum = 0;

    // Step 1: Calculate total sum of array
    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    int leftSum = 0;

    // Step 2: Traverse and check split point
    for (int i = 0; i < n - 1; i++)
    {
        // Add current element to left sum
        leftSum += arr[i];

        // Right sum is remaining part
        int rightSum = totalSum - leftSum;

        // Agar dono equal ho jaayein
        if (leftSum == rightSum)
            return i + 1; // right subarray starts here
    }

    // Agar split possible nahi
    return -1;
}

/*
------------------------------------------------------------
Common Print Function
------------------------------------------------------------
- Dono approaches ke liye same printing logic
- useOptimal = true  → optimal approach
- useOptimal = false → brute force approach
*/
void printTwoParts(int arr[], int n, bool useOptimal)
{
    int splitPoint;

    // Decide which approach to use
    if (useOptimal)
        splitPoint = findSplitPointOptimal(arr, n);
    else
        splitPoint = findSplitPointBruteForce(arr, n);

    // Agar split possible nahi
    if (splitPoint == -1 || splitPoint == n)
    {
        cout << "Not Possible" << endl;
        return;
    }

    // Print array in two parts
    for (int i = 0; i < n; i++)
    {
        // New line jab right subarray start ho
        if (i == splitPoint)
            cout << endl;

        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Brute Force Result:\n";
    printTwoParts(arr, n, false);

    cout << "\nOptimal Result:\n";
    printTwoParts(arr, n, true);

    return 0;
}
