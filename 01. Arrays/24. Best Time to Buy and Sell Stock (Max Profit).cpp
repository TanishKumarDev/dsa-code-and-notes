#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : Best Time to Buy and Sell Stock
// We are given an array `prices[]` where prices[i] is the stock price on day i.
// Task: Find the maximum profit by choosing one day to buy and a later day to sell.
// If no profit is possible, return 0.

// Example :
// Input  : prices = [7, 1, 5, 3, 6, 4]
// Output : 5
// Explanation: Buy on day 1 (price = 1), sell on day 4 (price = 6).

// Constraints :
// 1. Only one buy and one sell allowed
// 2. Sell must happen after buy
// 3. If prices always decrease, answer = 0
// 4. 1 <= n <= 10^5

// 🔴 Approach 1 Brute Force
// Intuition :
// Try all possible pairs (i, j) where i < j. Calculate profit = prices[j] - prices[i].
// Track maximum profit.
//
// Algo :
// For i from 0 to n-1:
//     For j from i+1 to n-1:
//          profit = prices[j] - prices[i]
//          maxProfit = max(maxProfit, profit)
//
// TC : O(n^2)  (two nested loops)
// SC : O(1)
//
// Edge cases :
// 1. n < 2 → no transaction possible, return 0
// 2. All decreasing prices → return 0
int brute(vector<int>& prices) {
    int maxP = 0;
    int n = prices.size();

    for (int i = 0; i < n; i++) {                 // choose buy day
        for (int j = i + 1; j < n; j++) {        // choose sell day
            if (prices[j] > prices[i]) {         // profit possible?
                maxP = max(maxP, prices[j] - prices[i]);
            }
        }
    }
    return maxP;
}

// 🔵 Approach 2 Better (Tracking Minimum Price)
// Intuition :
// Maintain minimum price seen so far, and at each price[i], calculate potential
// profit if sold today. Keep track of best profit.
//
// Algo :
// minPrice = +inf, maxProfit = 0
// For each price in prices:
//      minPrice = min(minPrice, price)
//      maxProfit = max(maxProfit, price - minPrice)
// return maxProfit
//
// TC : O(n)
// SC : O(1)
//
// Edge cases :
// 1. Works for n = 1, returns 0
// 2. Works for decreasing prices
// 3. Only 1 pass, efficient
int better(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;

    for(int price : prices) {

        minPrice = min(minPrice, price);         // if lower price found, update buy point
        int profit = price - minPrice;           // profit if sold today
        maxProfit = max(maxProfit, profit);      // track best profit
    }
    return maxProfit;
}

// 🟢 Approach 3 Optimal (Kadane Style Interpretation)
// Intuition :
// Instead of thinking buy-sell difference directly, think in terms of
// daily changes: profit[i] = prices[i] - prices[i-1].
// This becomes a Maximum Subarray Sum problem.
//
// Algo :
// Convert prices to diff array (profit for each day).
// Apply Kadane to find max subarray sum.
//
// TC : O(n)
// SC : O(1)
//
// Edge cases :
// 1. All decreasing prices → Kadane returns 0
// 2. Equivalent to Better approach in simpler form.
int optimal(vector<int>& prices) {

    int maxCurr = 0;           // current running profit
    int maxProfit = 0;        // best profit found

    for(int i = 1; i < prices.size(); i++) {

        // difference between today and yesterday
        int diff = prices[i] - prices[i - 1];

        // include this diff or restart new profit segment
        maxCurr = max(0, maxCurr + diff);

        // update best profit seen so far
        maxProfit = max(maxProfit, maxCurr);
    }
    return maxProfit;
}

// main() to test all approaches
int main() {

    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Brute Force Profit:  " << brute(prices) << endl;
    cout << "Better Approach Profit: " << better(prices) << endl;
    cout << "Optimal Kadane Profit: " << optimal(prices) << endl;

    return 0;
}
/*
Dry Run Examples for Best Time to Buy and Sell Stock

Test Case 1:
prices = [7, 1, 5, 3, 6, 4]
Expected Profit = 5
Buy at 1, Sell at 6

Better / Optimal Approach Detailed Walkthrough:
minPrice = +inf, maxProfit = 0

Day 0: price=7
minPrice = 7
profit = 0
maxProfit = 0

Day 1: price=1
minPrice = 1
profit = 0
maxProfit = 0

Day 2: price=5
minPrice = 1
profit = 5 - 1 = 4
maxProfit = 4

Day 3: price=3
minPrice = 1
profit = 3 - 1 = 2
maxProfit = 4

Day 4: price=6
minPrice = 1
profit = 6 - 1 = 5
maxProfit = 5   (best)

Day 5: price=4
profit = 4 - 1 = 3
maxProfit = 5

Final Answer = 5

-------------------------------------------------------------

Test Case 2:
prices = [8, 7, 6, 5, 4, 3]
Expected Profit = 0
No profit possible (monotonically decreasing)

Better Approach:
minPrice gradually becomes: 8 → 7 → 6 → 5 → 4 → 3
profit always = price - minPrice = 0
maxProfit = 0

-------------------------------------------------------------

Test Case 3:
prices = [2, 4, 1]
Expected Profit = 2 (Buy at 2, Sell at 4)

Walkthrough:
Day 0: price=2 → minPrice=2, profit=0
Day 1: price=4 → profit = 4 - 2 = 2 → maxProfit=2
Day 2: price=1 → minPrice=1
Result = 2

-------------------------------------------------------------

Test Case 4:
prices = [3, 2, 6, 5, 0, 3]
Expected Profit = 4 (Buy at 2, Sell at 6)

Walkthrough:
Day0 price=3 → minPrice=3
Day1 price=2 → minPrice=2
Day2 price=6 → profit=6-2=4 → maxProfit=4
Day3 price=5 → profit=5-2=3
Day4 price=0 → minPrice=0
Day5 price=3 → profit=3-0=3
Answer = 4

-------------------------------------------------------------

Test Case 5:
prices = [1]
Expected Profit = 0 (cannot sell)

-------------------------------------------------------------

Test Case 6 (Large Spike):
prices = [1, 100]
Expected Profit = 99

-------------------------------------------------------------

Kadane Interpretation Example:
Convert prices to diff array:
prices = [7, 1, 5, 3, 6, 4]
diff = [-6, 4, -2, 3, -2]

Apply Kadane:
curr=0, maxSum=0

i0: diff=-6 → curr=0 (reset)
i1: diff=4  → curr=4 maxSum=4
i2: diff=-2 → curr=2
i3: diff=3  → curr=5 maxSum=5
i4: diff=-2 → curr=3

Final Max Profit = 5

*/
