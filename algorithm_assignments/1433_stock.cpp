#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 1E9;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }
    int k = n/2;
    vector<vector<int>> dp(n, vector<int> (k+1, 0));

    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for(int j=2;j<=k;j++) {
        dp[0][j] = -INF;
    }

    for(int i=1;i<n;i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
        for(int j=1;j<k;j++) {
            // nothing to do
            //dp[i][j] = dp[i-1][j];
            // buy stock
            //dp[i][j] = dp[i-1][j-1] - prices[i];
            // sell stock
            //dp[i][j] = dp[i-1][j+1] + prices[i];
            dp[i][j] = std::max({dp[i-1][j], dp[i-1][j-1] - prices[i], dp[i-1][j+1] + prices[i]});
        }
        dp[i][k] = std::max(dp[i-1][k], dp[i-1][k-1] - prices[i]);
    }

    cout << dp[n-1][0] << endl;

    
    
    return 0;
}