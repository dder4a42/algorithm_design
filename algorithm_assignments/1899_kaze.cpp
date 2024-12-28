#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void disp_bipart(vector<int>& side) {
    int n = side.size()-2;
    cout << "left node is ";
    for(int i=1;i<=n;i++) {
        if(side[i]<0) cout << i << " ";
    }
    cout << endl;
    cout << "right node is ";
    for(int i=1;i<=n;i++) {
        if(side[i]>0) cout << i << " ";
    }
    cout << endl;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> bipartite(n+2, vector<int> (n+2, 0));
    for(int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        bipartite[u][v] = bipartite[v][u] = 1;
    }

    vector<int> side(n+2, 0);
    for(int i=1;i<=n;i++) {
        if(side[i] == 0) {
            vector<int> neighbor;
            neighbor.push_back(i);
            side[i] = -1;
            while(neighbor.empty() == false) {
                int p = neighbor.front();
                neighbor.pop_back();
                for(int j=1;j<=n;j++) {
                    if(side[j] == 0 && bipartite[p][j] > 0) {
                        side[j] = -side[p];
                        neighbor.push_back(j);
                    }
                }
            }
        }
    }

    // disp_bipart(side);

    for(int i=1;i<=n;i++) {
        if(side[i] < 0) {
            bipartite[0][i] = 1;
        }else {
            for(int j=1;j<=n;j++) bipartite[i][j] = 0;
            bipartite[i][n+1] = 1;
        }
    }

    int max_flow = 0;
    while(true) {
        queue<int> child;
        vector<bool> is_visited(n+2, false);
        vector<int> pre(n+2, 0);
        child.push(0);
        is_visited[0] = true;
        while(child.empty() == false) {
            int p = child.front();
            child.pop();
            if(p == n+1) break;
            for(int v=1;v<=n+1;v++) {
                if(bipartite[p][v] > 0 && is_visited[v] == false) {
                    child.push(v);
                    pre[v] = p;
                    is_visited[v] = true;
                }
            }
        }
        if(pre[n+1] > 0) {
            int p = n+1;
            max_flow += 1;
            while(pre[p] > 0) {
                bipartite[pre[p]][p] -= 1;
                bipartite[p][pre[p]] += 1;
                p = pre[p];
            }
        }else {
            break;
        }
    }
    cout << n - max_flow << endl;
    
    for(int i=1;i<=n;i++) {
        if(side[i]<0) {
            cout << i << " ";
        }else if(bipartite[i][n+1] > 0) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    return 0;
}