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

    // dp[i][j], the maximal profit we can get in the i-th day, if there are j stocks in hand. 
    int k = n/2;
    vector<int> dp(k+5, -INF);
    vector<int> tmp(k+5, -INF);

    dp[0] = 0;
    dp[1] = -prices[0];

    for(int i=1;i<n;i++) {
        std::fill(tmp.begin(), tmp.end(), -INF);
        tmp[0] = max(dp[0], dp[1]+prices[i]);
        if(i <= n/2) {
            for(int j=1;j<=i+1;j++) {
                tmp[j] = std::max(dp[j], dp[j-1] - prices[i]);
                tmp[j] = std::max(tmp[j], dp[j+1] + prices[i]);
            }
        }else {
            for(int j=1;j<=n-i-1;j++) {
                tmp[j] = std::max(dp[j], dp[j-1] - prices[i]);
                tmp[j] = std::max(tmp[j], dp[j+1] + prices[i]);
            }
        }
        tmp[k] = std::max(dp[k], dp[k-1] - prices[i]);
        std::swap(dp, tmp);
    }

    std::cout << dp[0] << endl;

    return 0;
}