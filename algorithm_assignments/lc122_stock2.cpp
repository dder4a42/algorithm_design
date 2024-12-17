#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    vector<int> prices;
    cin >> n;
    prices.resize(n, 0);
    for(auto &x: prices) {
        cin >> x;
    }

    vector<vector<int>> dp(n, vector<int> (2, 0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];

    for(int i=1;i<n;i++) {
        dp[i][0] = max(dp[i-1][1] + prices[i], dp[i-1][0]); // 卖出股票 或 继续观望
        dp[i][1] = max(dp[i-1][0]-prices[i], dp[i-1][1]); // 购入新股票 或 继续持有股票
    }

    cout << dp[n-1][0] << endl;
    
    return 0;
}