#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
const int INF = 1E9;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    if(n < 2) {
        cout << 0 << endl;
        return 0;
    }

    priority_queue<ll, vector<ll>, greater<ll>> buy;
    buy.push(prices[0]);
    ll money = 0;
    for(int i=1;i<prices.size();i++) {
        ll stock = buy.top();
        if(stock < prices[i]) {
            buy.pop();
            money += prices[i] - stock;
            buy.push(prices[i]);
        }
        buy.push(prices[i]);
    }
    cout << money << endl;
    return 0;
}

void dp_method() {
    int n;
    cin >> n;
    vector<int> prices(n, 0);
    for(int i=0;i<n;i++) {
        cin >> prices[i];
    }

    // dp[i][j], the maximal profit we can get in the i-th day, if there are j stocks in hand. 
    int k = 2;
    vector<vector<int>> dp(2, vector<int> (n, -INF));

    dp[0][0] = 0;
    dp[0][1] = -prices[0];

    int current = 1;
    int pre = 0;

    for(int i=1;i<n;i++) {
        // cout << "k is " << k << endl;
        dp[current][0] = max(dp[pre][0], dp[pre][1]+prices[i]);
        for(int j=1;j<=k;j++) {
            dp[current][j] = std::max(dp[pre][j], dp[pre][j-1] - prices[i]);
            dp[current][j] = std::max(dp[current][j], dp[pre][j+1] + prices[i]);
        }
        if(i < n/2) k++;
        else k--;
        current = 1 - current;
        pre = 1 - pre;
    }

    std::cout << dp[pre][0] << endl;
}