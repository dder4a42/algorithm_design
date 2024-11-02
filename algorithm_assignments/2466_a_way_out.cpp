#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    int cnt=0;
    string neighbour;

    cin >> n;
    vector<bool> visited(n+1, 0);
    vector<int> pre(n+1, 0);
    visited[1] = true;
    int u=1;
    while(cnt < 2*n) {
        if(u == n) {
            cout << "yes" << endl;
            break;
        }
        int j=1;
        cin >> neighbour;
        for(;j<=n;j++) {
            if(neighbour[j-1] - '0' == 1 && visited[j] == false) {
                visited[j] = true;
                pre[j]=u;
                u=j;
                break;
            }
        }
        if(j > n) {
            u = pre[u];
        }
        if(u == 0) break;
        cout << u << endl;
        cnt++;
    }
    if(cnt >= 2*n || u == 0) cout << "no" << endl;
    
    return 0;
}