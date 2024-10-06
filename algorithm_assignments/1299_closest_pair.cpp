#include <bits/stdc++.h>
#include<algorithm>
using namespace std;
typedef long long int ll;
const long long INF = 1e18;


/* 
   NOTE:
   std::pow is for floating point numbers.
   For integers, it's better to implement one.
*/

// FIXME: reimplement with long long int
ll pow_2 (ll x) {
    return x * x;
}

struct point {
    ll x, y;
    point (ll _x, ll _y) : x(_x), y(_y) {}
    long long distance_2 (const point & other) const {
        return pow_2(x - other.x) + pow_2(y - other.y);
    }
};

long long solve (vector <point> &a, int l, int r) {
    if(l+1 >= r) {
        return INF;
    }
    int mid = (l+r) / 2;
    ll ret = min(solve(a, l, mid), solve(a, mid, r));
    vector<point> strip;
    for(int i=l; i<r; ++i) {
        if( pow_2(a[i].x-a[mid].x) < ret ) strip.push_back(a[i]);
    }
    sort(strip.begin(), strip.end(), [](point &a, point &b) {return a.y < b.y;});
    for(int i=0;i<strip.size();i++) {
        int j=i+1;
        while(j <= i+6 && j < strip.size()) {
            if( pow_2(strip[i].y-strip[j].y) >= ret ) break;
            ret = min(ret, strip[i].distance_2(strip[j]));
            j++;
        }
    }
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector <point> a;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto &u, auto &v) {
        return u.x < v.x;
    });
    cout << solve (a, 0, n) << endl;
}