#include <bits/stdc++.h>
using namespace std;

class LemonadeStand
{
public:
    bool lemonadeChange(vector<int> &bills)
    {

        int five = 0; // number of $5 bills
        int ten = 0;  // number of $10 bills

        for (int bill : bills)
        {

            // Case 1: customer pays $5
            if (bill == 5)
            {
                five++;
            }

            // Case 2: customer pays $10
            else if (bill == 10)
            {
                if (five == 0)
                    return false; // cannot give $5 change

                five--;
                ten++;
            }

            // Case 3: customer pays $20
            else
            {
                // Prefer $10 + $5
                if (ten > 0 && five > 0)
                {
                    ten--;
                    five--;
                }
                // Else use three $5
                else if (five >= 3)
                {
                    five -= 3;
                }
                else
                {
                    return false; // no valid change
                }
            }
        }
        return true;
    }
};

int main()
{
    vector<int> bills = {5, 5, 5, 10, 20};

    LemonadeStand stand;
    bool result = stand.lemonadeChange(bills);

    if (result)
        cout << "Change can be provided to all customers.\n";
    else
        cout << "Change cannot be provided.\n";

    return 0;
}
