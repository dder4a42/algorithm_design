#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prices(n+1, 0);
    for(int i=1;i<=n;i++) {
        cin >> prices[i];
    }

    

    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (3, vector<int> (n/2+1, 0)));
    int k = n/2+1;
    // dp[0][0][0] = -1E7;
    // dp[0][1][0] = -1E7;
    // dp[0][2][0] = 0;
    // for(int i=1;i<=n/2;i++) {
    //     dp[0][0][i] = -1E7;
    //     dp[0][1][i] = -1E7;
    // }

    // 0 buy, 1 sell, 2 none
    dp[1][0][0] = -prices[1];
    dp[1][2][0] = 0;
    for(int i=2;i<=n;i++) {
        dp[i][2][0] = std::max({dp[i-1][1][1], dp[i-1][2][0]});
        // dp[i][1][0] = -1E7;
        dp[i][0][0] = dp[i][2][0] - prices[i];
        for(int j=1;j<n/2;j++) {
            dp[i][2][j] = max({dp[i-1][2][j], dp[i-1][0][j-1], dp[i-1][1][j+1]});
            dp[i][1][j] = dp[i][2][j] + prices[i];
            dp[i][0][j] = dp[i][2][j] - prices[i];
        }
        dp[i][2][n/2] = max({dp[i-1][2][n/2], dp[i-1][0][n/2-1]});
        dp[i][1][n/2] = dp[i][2][n/2] + prices[i];
        dp[i][0][n/2] = dp[i][2][n/2] - prices[i];
    }

    int max_one = 0;
    for(int i=0;i<n/2+1;i++) {
        max_one = max({dp[n-1][0][i], dp[n-1][2][i], max_one});
    }
    cout << max_one << endl;
    
    return 0;
}