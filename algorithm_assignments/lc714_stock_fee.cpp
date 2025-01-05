#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, fee;
    cin >> n >> fee;
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    vector<vector<int>> dp(n, vector<int> (2, 0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0] - fee;

    for(int i=1;i<n;i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee);
    }
    cout << dp[n-1][0] << endl;
    
    return 0;
}