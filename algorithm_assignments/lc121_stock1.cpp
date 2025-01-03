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
        dp[i][0] = max(dp[i-1][1] + prices[i], dp[i-1][0]); // 卖出手中的股票 或 继续观望，不买股票
        dp[i][1] = max(-prices[i], dp[i-1][1]); // （重新）开始购入股票（只能做一笔交易） 或 保留手中的股票
    }

    cout << dp[n-1][0] << endl;
    
    return 0;
}