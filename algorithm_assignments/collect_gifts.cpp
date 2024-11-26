#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int collect_gifts_grids_based(int m, vector<int>& value, vector<vector<int>>& gift_location) {
    vector<vector<int>> grids(m, vector<int> (m, 0));
    vector<vector<int>> gain(m, vector<int> (m, 0));
    int n = value.size();
    for(int i=0;i<n;i++) {
        gain[gift_location[i][0]][gift_location[i][1]] = value[i];
    }

    int max_profit = gain[0][0];
    grids[0][0] = gain[0][0];
    for(int i=1;i<m;i++) {
        grids[0][i] = gain[0][i] + grids[0][i-1] - 1;
        grids[i][0] = gain[i][0] + grids[i-1][0] - 1;
        max_profit = max(grids[0][i], max_profit);
        max_profit = max(grids[i][0], max_profit);
    }
    for(int i=1;i<m;i++) {
        for(int j=1;j<m;j++) {
            grids[i][j] = gain[i][j] + max(grids[i-1][j]-1, grids[i][j-1]-1);
            max_profit = max(grids[i][j], max_profit);
        }
    }
    return max_profit;
}



int collect_gifts_gift_based(int m, vector<int>& value, vector<vector<int>>& gift_location) {
    int n = value.size();
    struct gift {
        int value;
        int x, y;
    };
    vector<gift> gifts(n);
    for(int i=0;i<n;i++) {
        gifts[i].value = value[i];
        gifts[i].x = gift_location[i][0];
        gifts[i].y = gift_location[i][1];
    }
    sort(gifts.begin(), gifts.end(), [](gift &a, gift &b) {return a.x <= b.x && a.y <= b.y;});
    vector<int> profits(n, 0);
    for(int i=0;i<n;i++) {
        profits[i] = gifts[i].value - gifts[i].x - gifts[i].y;
        for(int j=i-1;j>=0;j--) {
            if(gifts[j].x <= gifts[i].x && gifts[j].y <= gifts[i].y) {
                profits[i] = max(profits[i], gifts[i].value + profits[j] - (gifts[i].x-gifts[j].x) - (gifts[i].y - gifts[j].y));
            }
        }
    }
    int max_profit = 0;
    for(auto profit: profits) {
        max_profit = max(profit, max_profit);
    }
    return max_profit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    vector<int> value;
    vector<vector<int>> location;
    cin >> m >> n;
    for(int i=0;i<n;i++) {
        int v, x, y;
        cin >> v >> x >> y;
        value.push_back(v);
        location.push_back({x, y});
    }
    cout << "start running!" << endl;
    int p1, p2;
    p1 = collect_gifts_grids_based(m, value, location);
    cout << "algorithm 1 output " << p1 << endl;

    p2 = collect_gifts_gift_based(m, value, location);
    cout << "algorithm 2 output " << p2 << endl;
    
    return 0;
}