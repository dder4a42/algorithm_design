#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> price(n, 0);
    for(int i=0;i<n;i++) {
        cin >> price[i];
    }

    vector<bool> is_used(n, false);
    int gain=0;
    for(int j=0;j<n/2;j++) {
        int min_price = 0;
        int max_price = 0;
        int max_gain = 0;
        for(int k=0;k<n;k++) {
            if(!is_used[k]) {
                min_price = k, max_price = k;
                break;
            }
        }
        for(int i=0;i<n;i++) {
            if(!is_used[i] && price[i] < price[min_price]) {
                min_price = i;
            }
            if(!is_used[i] && max_gain < price[i] - price[min_price]) {
                max_price = i;
                max_gain = price[i] - price[min_price];
            }
        }
        if(price[max_price] - price[min_price] > 0) {
            is_used[max_price] = is_used[min_price] = true;
            gain += price[max_price] - price[min_price];
            cout << "buy in day " << min_price << " and sale in day " << max_price << endl;
            cout << "buy in " << price[min_price] << " and sale in " << price[max_price] << endl;
        }else {
            break;
        }
    }
    cout << gain << endl;
    
    return 0;
}