#include <bits/stdc++.h>
using namespace std;

// Function to find minimum coins
vector<int> minCoins(int V)
{

    // Indian currency denominations
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
    int n = sizeof(coins) / sizeof(coins[0]);

    vector<int> result;

    // Start from largest denomination
    for (int i = n - 1; i >= 0; i--)
    {

        // Take as many coins[i] as possible
        while (V >= coins[i])
        {
            V -= coins[i];
            result.push_back(coins[i]);
        }
    }

    return result;
}

int main()
{
    int V = 121;

    vector<int> ans = minCoins(V);

    cout << "Minimum number of coins = " << ans.size() << endl;
    cout << "Coins used: ";

    for (int coin : ans)
    {
        cout << coin << " ";
    }

    cout << endl;
    return 0;
}
