#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int V, n;
    cin >> V >> n;
    vector<int> weight(n+1, 0);
    for(int i=1;i<=n;i++) {
        int w;
        cin >> w;
        weight[i] = w;
    }

    vector<vector<ll>> dp(n+1, vector<ll> (V+1, 0));
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=V;j++) {
            if(i==0 || j ==0) {
                dp[i][j] = 0;
            }else {
                dp[i][j] = dp[i-1][j];
                if(j >= weight[i]) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-weight[i]] + weight[i]);
                }
            }
            
        }
        // for(int j=0;j<=V;j++) {
        //     cout << dp[i][j] << "\t";
        // }
        // cout << endl;
    }
    cout << V - dp[n][V] << endl;

    // for(int i=0;i<=n;i++) {
    //     for(int j=0;j<=V;j++) {
    //         cout << dp[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    
    return 0;
}