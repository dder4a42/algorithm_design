#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t, m;
    cin >> t >> m;

    if(t == 0 || m == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> cost(m+1, 0);
    vector<int> value(m+1, 0);
    for(int i=1;i<=m;i++) {
        int c, v;
        cin >> c >> v;
        cost[i] = c;
        value[i] = v;
    }

    // for(int i=0;i<m;i++) {
    //     cout << cost[i] << ", " << value[i] << endl;
    // }


    vector<vector<int>> dp(m+1, vector<int> (t+1, 0)); // dp[i][j], the maximal value we can get by choosing from first i things with totally cost less than j. 
    if(cost[1] <= t)
        dp[1][cost[1]] = value[1];
    for(int i=1;i<=m;i++) {
        for(int j=0;j<=t;j++) {
            dp[i][j] = dp[i-1][j];
            if(j>=cost[i] && dp[i-1][j-cost[i]] + value[i] > dp[i][j]) {
                dp[i][j] = dp[i-1][j-cost[i]] + value[i];
            }
        }
    }
    cout << dp[m][t] << endl;

    // for(int i=0;i<m;i++) {
    //     for(int j=0;j<t;j++) {
    //         cout << dp[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    
    return 0;
}