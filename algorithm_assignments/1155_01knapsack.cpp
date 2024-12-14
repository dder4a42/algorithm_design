#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> weight(n+1, 0);
    vector<int> value(n+1, 0);
    for(int i=1;i<=n;i++) {
        int w, v;
        cin >> w >> v;
        weight[i] = w;
        value[i] = v;
    }

    vector<ll> dp(m+1, 0);
    for(int i=0;i<=n;i++) {
        for(int j=m;j>=weight[i];j--) {
            if(i == 0 || j == 0) {
                dp[j] = 0;
            }else {
                dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
            }
        }
        // for(int j=0;j<=m;j++) {
        //     cout << dp[j] << "\t";
        // }
        // cout << endl;
    }
    cout << dp[m] << endl;

    
        
    return 0;
}