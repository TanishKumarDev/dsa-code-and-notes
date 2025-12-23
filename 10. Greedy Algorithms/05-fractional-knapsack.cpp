#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double fractionalKnapsack(int W, vector<int> &val, vector<int> &wt)
    {

        int n = val.size();

        // Store items as (ratio, value, weight)
        vector<pair<double, pair<int, int>>> items;

        for (int i = 0; i < n; i++)
        {
            double ratio = (double)val[i] / wt[i];
            items.push_back({ratio, {val[i], wt[i]}});
        }

        // Sort items by descending value/weight ratio
        sort(items.begin(), items.end(), greater<>());

        int currentWeight = 0;
        double totalValue = 0.0;

        // Fill the knapsack greedily
        for (auto &item : items)
        {
            int value = item.second.first;
            int weight = item.second.second;

            if (currentWeight + weight <= W)
            {
                // Take full item
                currentWeight += weight;
                totalValue += value;
            }
            else
            {
                // Take fraction of item
                int remaining = W - currentWeight;
                totalValue += value * ((double)remaining / weight);
                break; // knapsack is full
            }
        }

        return totalValue;
    }
};

int main()
{
    vector<int> value = {60, 100, 120};
    vector<int> weight = {10, 20, 30};
    int W = 50;

    Solution obj;
    double ans = obj.fractionalKnapsack(W, value, weight);

    cout << fixed << setprecision(2);
    cout << "Maximum value = " << ans << endl;

    return 0;
}
