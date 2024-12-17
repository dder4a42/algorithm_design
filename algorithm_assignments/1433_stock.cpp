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

    vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (n/2, 0)));
    
    
    return 0;
}