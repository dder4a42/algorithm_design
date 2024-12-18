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

    // 0 nothing, 1 play, 2 work
    // find max play days, and record money at the same time
    int max_money=0;
    vector<vector<int>> money(n, vector<int> (3, 0));
    vector<vector<int>> play_days(n, vector<int> (3, 0));

    play_days[0][0] = play_days[0][1] = play_days[0][2] = 0;
    money[0][0] = money[0][1] = 0;
    if(holiday[0].empty() == false) {
        for(auto &e: holiday[0]) {
            money[0][1] = max(money[0][1], e.pay);
        }
    }
    cout << money[0][0] << " " << money[0][1] << " " << money[0][2] << endl;
    cout << play_days[0][0] << " " << play_days[0][1] << " " << play_days[0][2] << endl;

    for(int i=1;i<n;i++) {
        // nothing
        if(play_days[i-1][0] > play_days[i-1][1]) {
            play_days[i][0] = play_days[i-1][0];
            money[i][0] = money[i-1][0];
        }else if(play_days[i-1][1] > play_days[i-1][2]) {
            play_days[i][0] = play_days[i-1][1];
            money[i][0] = money[i-1][1];
        }else if(play_days[i-1][2] > play_days[i-1][1]) {
            play_days[i][0] = play_days[i-1][2];
            money[i][0] = money[i-1][2];
        }else if(play_days[i-1][2] == play_days[i-1][1] && play_days[i-1][1] > play_days[i-1][0]) {
            play_days[i][0] = play_days[i-1][2];
            money[i][0] = max(money[i-1][0], money[i-1][2]);
        }else {
            play_days[i][0] = play_days[i-1][1];
            money[i][0] = max(money[i-1][0], money[i-1][1]);
            money[i][0] = max(money[i][0], money[i-1][2]);
        }
        // work
        for(auto &u: holiday[i]) {
            int s = u.start, a = u.pay;
            if(play_days[i][2] < play_days[s][0]) {
                play_days[i][2] = play_days[s][0];
                money[i][2] = money[s][0] + a;
            }else if(play_days[i][2] == play_days[s][0]) {
                money[i][2] = max(money[s][0] + a, money[i][2]);
            }
        }
        // play
        if(money[i][0] >= x) {
            play_days[i][1] = play_days[i][0]+1;
            money[i][1] = money[i][0] - x;
        }
        cout << "money: ";
        cout << money[i][0] << " " << money[i][1] << " " << money[i][2] << endl;
        cout << "play days: ";
        cout << play_days[i][0] << " " << play_days[i][1] << " " << play_days[i][2] << endl;
    }
    if(play_days[n-1][0] > play_days[n-1][1]) {
        cout << money[n-1][0] << endl;
    }else if(play_days[n-1][1] > play_days[n-1][2]){
        cout << money[n-1][1] << endl;
    }else if(play_days[n-1][2] > play_days[n-1][1]) {
        cout << money[n-1][2] << endl;
    }else if(play_days[n-1][2] == play_days[n-1][1] && play_days[n-1][1] > play_days[n-1][0]) {
        cout << max(money[n-1][2], money[n-1][2]) << endl;
    }else {
        cout << max(money[n-1][0], money[n-1][2]) << endl;
    }
    

    // for(int i=0;i<n;i++) {
    //     cout << max(money[i][0], money[i][1]) << " ";
    // }
    // cout << endl;
    return 0;
}