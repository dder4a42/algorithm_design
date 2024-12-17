#include<iostream>
#include<vector>
using namespace std;

void one_index();
void two_index();

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k, 0)));

    dp[0][0][0] = 0;
    dp[0][1][0] = -prices[0];
    for(int i=1;i<k;i++) {
        dp[0][0][i] = 0;
        dp[0][1][i] = -prices[0];
    }

    for(int i=1;i<n;i++) {
        dp[i][0][0] = max(dp[i-1][0][0], dp[i-1][1][0] + prices[i]);
        dp[i][1][0] = max(dp[i-1][1][0], -prices[i]);
        for(int j=1;j<k;j++) {
            dp[i][0][j] = max(dp[i-1][0][j], dp[i-1][1][j] + prices[i]);
            dp[i][1][j] = max(dp[i-1][1][j], dp[i-1][0][j-1] - prices[i]);
        }
    }

    int max_one = 0;
    for(int i=0;i<k;i++) {
        max_one = max(dp[n-1][0][i], max_one);
    }
    cout << max_one << endl;

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
    for(int i=2;i<2*k;i+=2) {
        dp[k] = 0;
        dp[k+1] = -prices[0];
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

void two_index() {
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
}