#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct edge {
    int start, pay;
    edge(int _s, int _a) {
        start = _s, pay = _a;
    }
};

struct profit {
    int play_days, money;
    profit(int _p=0, int _m=0) {
        play_days = _p;
        money = _m;
    }
};

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<edge>> jobs(n);
    for(int i=0;i<m;i++) {
        int s, t, a;
        cin >> s >> t >> a;
        s--, t--;
        jobs[t].push_back({s, a});
    }

    // 0 nothing, 1 play, 2 work
    // find max play days, and record money at the same time
    int max_money=0;
    vector<vector<profit>> dp(n, vector<profit> (3, 0));

    for(auto &e: jobs[0]) {
        dp[0][2].money = max(dp[0][2].money, e.pay);
    }

    for(int i=1;i<n;i++) {
        // nothing
        
        // work
        for(auto &u: jobs[i]) {
            int s = u.start, a = u.pay;
            
        }
        // play
        
    }
    
    return 0;
}