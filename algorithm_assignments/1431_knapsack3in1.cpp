#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, W; // numbers of things, capacility of knapsack
    cin >> n >> W;
    vector<int> weight;
    vector<int> value;
    vector<int> quantity;
    for(int i=1;i<=n;i++) {
        int w, v, c;
        cin >> w >> v >> c;
        if(c == 1 || c > 10000) {
            weight.push_back(w);
            value.push_back(v);
            quantity.push_back(c);
        }else {
            int k=1;
            while (c > k) {
                weight.push_back(w*k);
                value.push_back(v*k);
                quantity.push_back(k);
                c -= k;
                k *= 2;
            }
            weight.push_back(w*c);
            value.push_back(v*c);
            quantity.push_back(c);
        }
        
    }
    n = weight.size();

    for(int i=0;i<n;i++) {
        cout << weight[i] << ", " << value[i] << ", " << quantity[i] << endl;
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
        }else{
            for(int j=W;j>=weight[i];j--) {
                if(i==0 || j==0) {
                    dp[j] = 0;
                }else {
                    dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
                }
            }
        }
    }

    std::cout << dp[W] << endl;
    
    return 0;
}

// https://cp-algorithms.com/dynamic_programming/knapsack.html