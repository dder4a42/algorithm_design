#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int b,t,n;
    cin >> b >> t >> n;
    vector<int> special(n, 0);
    for(int i=0;i<n;i++) {
        cin >> special[i];
    }
    // special.push_back(b-1);
    special.push_back(t+1);

    make_heap(special.begin(), special.end(), greater<int>());

    // for(int num: special) {
    //     cout << num << " ";
    // }cout << endl;

    int p = b-1;
    int interval = 0;
    for(int i=0;i<n;i++) {
        int top = special.front();
        interval = max(interval, top-p);
        pop_heap(special.begin(), special.end(), greater<int>());
        special.pop_back();
        cout << top << "-" << p << "="  << interval << endl;
        p = top;
    }

    cout << interval-1 << endl;
    
    return 0;
}