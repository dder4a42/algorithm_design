#include<iostream>
#include<vector>
using namespace std;

bool subset_sum(int k, vector<int>& T) {
    int n = T.size();
    vector<vector<bool>> dp(n, vector<bool> (k+1, false));

    dp[0][0] = true;
    if(T[0] <= k) dp[0][T[0]] = true;
    for(int i=1;i<n;i++) {
        for(int j=0;j<=k;j++) {
            if(dp[i-1][j] || (j >= T[i] && dp[i-1][j-T[i]])) dp[i][j] = true;
        }
        if(dp[i][k]) return true;
    }
    return false;
}

bool subset_sum_space_save(int k, vector<int>& T) {
    int n = T.size();
    vector<bool> dp(k+1, false);
    
    dp[0] = true;  // Sum of 0 is always possible (by taking no elements)
    
    for (int i = 0; i < n; i++) {
        // Traverse the dp array backwards to avoid overwriting values from the same iteration
        for (int j = k; j >= T[i]; j--) {
            if (dp[j - T[i]]) {
                dp[j] = true;
            }
        }
        if (dp[k]) return true; // Early exit if we can make the sum k
    }
    
    return dp[k];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    vector<int> T(n);
    cin >> k;
    for(int i=0;i<n;i++) {
        int x;
        cin >> x;
        T[i] = x;
    }
    bool is_sum_k = false;
    is_sum_k = subset_sum(k, T);
    if(is_sum_k) cout << "Yes!\n";
    else cout << "No!\n";
    
    return 0;
}