#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(n, vector<int> (2*k, 0));
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    dp[0][1] = -prices[0];
    for(int i=2;i<2*k;i+=2) {
        dp[0][k] = 0;
        dp[0][k+1] = -prices[0];
    }
    
    for(int i=1;i<n;i++) {
        for(int j=2*k-2;j>0;j-=2) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j+1] + prices[i]);
            dp[i][j+1] = max(dp[i-1][j+1], dp[i-1][j-2] - prices[i]);
        }
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
        dp[i][1] = max(dp[i-1][1], -prices[i]);
    }

    cout << dp[n-1][2*k-2] << endl;

    return 0;
}

void one_index() {
    int n, k;
    cin >> n >> k;
    vector<int> dp(2*k, 0);
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    dp[1] = -prices[0];
    for(int i=3;i<2*k;i+=2) {
        dp[k-1] = 0;
        dp[k] = -prices[0];
    }
    
    for(int i=1;i<n;i++) {
        for(int j=k-1;j>0;j--) {
            dp[2*j] = max(dp[2*j], dp[2*j+1] + prices[i]);
            dp[2*j+1] = max(dp[2*j+1], dp[2*j-2] - prices[i]);
        }
        dp[0] = max(dp[0], dp[1] + prices[i]);
        dp[1] = max(dp[1], -prices[i]);
    }

    cout << dp[2*k-2] << endl;
}