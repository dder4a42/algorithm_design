#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// struct edge {
//     int end, flow;
//     edge *next_neighbor, *v;
//     edge(int _e=0, int _f=0, edge* _n=nullptr, edge* _v=nullptr) {
//         end = _e, flow = _f, next_neighbor = _n, v = _v;
//     }
// };


int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    // vector<vector<int>> matrix(n, vector<int> (n, 0));
    // vector<edge**> adj_list(2*n+2);
    vector<vector<int>> adj(2*n+2, vector<int> (2*n+2, 0));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            int x;
            cin >> x;
            if(x) {
                adj[i][j+n] = 1;
            }
        }
    }

    for(int i=1;i<=n;i++) {
        adj[0][i] = 1;
        adj[i+n][2*n+1] = 1;
    }

    int max_flow = 0;
    while(true) {
        queue<int> child;
        vector<bool> is_visited(2*n+2, false);
        vector<int> pre(2*n+2, -1);
        child.push(0);
        is_visited[0] = true;
        while(child.empty() == false) {
            int p = child.front();
            child.pop();
            if(p == 2*n+1) break;
            for(int v=1;v<=2*n+1;v++) {
                if(adj[p][v] > 0 && is_visited[v] == false) {
                    child.push(v);
                    pre[v] = p;
                    is_visited[v] = true;
                }
            }
        }
        if(pre[2*n+1] > 0) {
            int p = 2*n+1;
            max_flow += 1;
            while(pre[p] >= 0) {
                adj[pre[p]][p] -= 1;
                adj[p][pre[p]] += 1;
                p = pre[p];
            }
        }else {
            break;
        }
    }
    // cout << "max flow is " << max_flow << endl;
    if(max_flow < n) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;

    for(int i=1;i<=n;i++) {
        for(int j=n+1;j<=2*n;j++) {
            if(adj[j][i]) cout << 1 << " ";
            else cout << 0 << " ";
        }
        cout << endl;
    }
    
    return 0;
}