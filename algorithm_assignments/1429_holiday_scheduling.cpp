#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<int>> holiday(n);
    for(int i=0;i<m;i++) {
        int s, t, a;
        cin >> s >> t >> a;
        s--, t--;
        holiday[t].push_back(s);
    }

    int max_money=0;
    vector<vector<int>> money(n, vector<int> (2, 0));
    for(int i=0;i<n;i++) {
        if(i>0)
            money[i][0] = max(money[i-1][0], money[i-1][1]);
        for(auto u: holiday[i]) {
            money[i][1] = max(money[i][1], money[u][0]+1);
        }
        max_money = max(max_money, money[i][0]);
        max_money = max(max_money, money[i][1]);
    }
    cout << max_money << endl;

    // for(int i=0;i<n;i++) {
    //     cout << max(money[i][0], money[i][1]) << " ";
    // }
    // cout << endl;
    return 0;
}

void date_base() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<int>> holiday(n);
    for(int i=0;i<m;i++) {
        int s, t, a;
        cin >> s >> t >> a;
        s--, t--;
        holiday[t].push_back(s);
    }

    int max_money=0;
    vector<int> money(n, 0);
    for(int i=0;i<n;i++) {
        money[i] = 0;
        for(auto u: holiday[i]) {
            money[i] = max(money[i], money[u]+1);
        }
        max_money = max(max_money, money[i]);
    }
    cout << max_money << endl;

    for(int i=0;i<n;i++) {
        cout << money[i] << " ";
    }
    cout << endl;
}

struct job
{
    int start_time, end_time, pay;
    job(int _s=0, int _t=0, int _pay=0) {start_time=_s, end_time=_t, pay=_pay;}
    void set_job(int _s=0, int _t=0, int _pay=0) {
        start_time=_s, end_time=_t, pay=_pay;
    }
};

void jobs_base() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<job> jobs(m+1);
    for(int i=1;i<=m;i++) {
        int s, t, a;
        cin >> s >> t >> a;
        jobs[i].set_job(s, t, a);
    }

    sort(jobs.begin(), jobs.end(), [](job& a, job& b) {return a.start_time < b.start_time;});

    int max_money=0;
    vector<int> money(m+1, 0);
    for(int i=1;i<=m;i++) {
        money[i] = 1;
        for(int j=i-1;j>0;j--) {
            if(jobs[j].end_time < jobs[i].start_time) {
                money[i] = max(money[i], money[j]+1);
            }
        }
        max_money = max(max_money, money[i]);
    }
    cout << max_money << endl;
}