#include <bits/stdc++.h>
using namespace std;

// ⭐ Approach 1:
vector<int> findMeanBruteForce(vector<int> &arr, vector<vector<int>> &queries)
{
    int n = arr.size();
    int q = queries.size();

    vector<int> result;

    for (int i = 0; i < q; i++)
    {
        int l = queries[i][0] - 1;
        int r = queries[i][1] - 1;

        int sum = 0, count = 0;

        for (int j = l; j <= r; j++)
        {
            sum += arr[j];
            count++;
        }

        result.push_back(sum / count);
    }

    return result;
}

// ⭐ Approach 2:
// ⭐ Approach 3:

void printArr(vector<int> &arr)
{
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> arr = {3, 7, 2, 8, 5};
    vector<vector<int>> queries = {{1, 3}, {2, 5}};

    vector<int> result = findMeanBruteForce(arr, queries);

    printArr(result);
}