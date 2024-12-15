#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, W; // numbers of things, capacility of knapsack
    cin >> n >> W;
    vector<int> weight(n+1, 0);
    vector<int> value(n+1, 0);
    vector<int> quantity(n+1, 0);
    for(int i=1;i<=n;i++) {
        int w, v, c;
        cin >> w >> v >> c;
        weight[i] = w;
        value[i] = v;
        quantity[i] = c;
    }

    vector<ll> dp(W+1, 0);
    for(int i=0;i<=n;i++) {
        if(quantity[i] > 10000) {
            for(int j=0;j<=W;j++) {
                if(i==0 || j==0) {
                    dp[j] = 0;
                }else if(j >= weight[i]) {
                    dp[j] = max(dp[j-weight[i]] + value[i], dp[j]);
                }
            }
        }else {
            for(int j=W;j>=weight[i];j--) {
                if(i==0 || j==0) {
                    dp[j] = 0;
                }else {
                    for(int k=1;j >= k*weight[i] && k <= quantity[i];k++) {
                        dp[j] = max(dp[j], dp[j-k*weight[i]] + k * value[i]);
                    }
                }
            }
        }
        
    }

    std::cout << dp[W] << endl;
    
    return 0;
}

// https://cp-algorithms.com/dynamic_programming/knapsack.html