#include <bits/stdc++.h>
#include<algorithm>
using namespace std;
const long long INF = 1e18;


/* 
   NOTE:
   std::pow is for floating point numbers.
   For integers, it's better to implement one.
*/

// FIXME: reimplement with long long int


struct point {
    double x, y;
    point (double _x, double _y) : x(_x), y(_y) {}
};
double dist(point a, point b) {
    return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) );
}

double solve (vector <point> &a, int l, int r) {
    if(l+1 >= r) {
        return INF;
    }
    int mid = (l+r) / 2;
    double ret = min(solve(a, l, mid), solve(a, mid, r));
    vector<point> strip;
    for(int i=l; i<r; ++i) {
        if( abs(a[i].x- a[mid].x) < ret/2 ) strip.push_back(a[i]);
    }
    sort(strip.begin(), strip.end(), [](point &a, point &b) {return a.y < b.y;});
    for(int i=0;i<strip.size();i++) {
        int j=i+1;
        while(j <= i+6 && j < strip.size()) {
            int k=j+1;
            double edge=dist(strip[i], strip[j]);
            while(k <= j+6 && k < strip.size()) {
                if( abs(strip[i].y-strip[j].y) >= ret ) break;
                ret = min(ret, dist(strip[i], strip[k])+dist(strip[j], strip[k])+edge);
                k++;
            }
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
    cout << fixed << solve (a, 0, n) << endl;
}