#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }


    if(n == 1) return 0;
    vector<vector<int>> dp(n, vector<int> (2, 0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    dp[1][0] = max(0, prices[1]-prices[0]);
    dp[1][1] = max(-prices[0], -prices[1]);
    
    for(int i=2;i<n;i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i]); // two cases when no stock in hand in i-1 day, 1. no buy, dp[i-1][0] = dp[i-2][0]; 2. sell, then we can not transilate from i-1 day, but i-2 day. 
    }
    cout << dp[n-1][0] << endl;
    
    return 0;
}