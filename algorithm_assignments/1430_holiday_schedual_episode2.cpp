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

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<edge>> holiday(n);
    for(int i=0;i<m;i++) {
        int s, t, a;
        cin >> s >> t >> a;
        s--, t--;
        holiday[t].push_back({s, a});
    }

    int max_money=0;
    vector<vector<int>> money(n, vector<int> (3, 0));
    vector<vector<int>> play_days(n, vector<int> (3, 0));
    for(int i=0;i<n;i++) {
        if(i>0) {
            money[i][0] = max(money[i-1][0], money[i-1][1]);
            play_days[i][0] = max(play_days[i-1][0], play_days[i-1][2]);
        }
        for(auto u: holiday[i]) {
            int s = u.start, a = u.pay;
            money[i][1] = max(money[i][1], money[s][0]+a);
        }
        if(money[i][0] > x) {
            money[i][2] = money[i][0] - x;
            play_days[i][2] = play_days[i][0]+1;
        }
        cout << money[i][0] << " " << money[i][1] << " " << money[i][2] << endl;
        cout << play_days[i][0] << " " << play_days[i][2] << endl;
    }
    if(play_days[n-1][0] > play_days[n-1][2]) {
        cout << money[n-1][0] << endl;
    }else {
        cout << money[n-1][2] << endl;
    }
    

    // for(int i=0;i<n;i++) {
    //     cout << max(money[i][0], money[i][1]) << " ";
    // }
    // cout << endl;
    return 0;
}