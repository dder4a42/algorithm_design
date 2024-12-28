#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct edge
{
    int v, c;
    edge(int _v=0, int _c=0) {
        v = _v, c = _c;
    }
};


int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // vector<vector<int>> graph(n+1);
    vector<vector<int>> capacility(n+1, vector<int> (n+1, 0));
    for(int i=0;i<m;i++) {
        int u, v, c;
        bool is_multiple = false;
        cin >> u >> v >> c;
        if(u == v) continue;
        // for(auto e: graph[u]) {
        //     if(e == v) {
        //         is_multiple = true;
        //         break;
        //     }
        // }
        // if(is_multiple == false) {
        //     graph[u].push_back(v);
        // }
        capacility[u][v] += c;
    }

    int max_flow = 0;
    while(true) {
        queue<int> child;
        vector<bool> is_visited(n+1, false);
        vector<int> pre(n+1, 0);
        child.push(1);
        is_visited[1] = true;
        while(child.empty() == false) {
            int p = child.front();
            child.pop();
            if(p == n) break;
            for(int v=1;v<=n;v++) {
                if(capacility[p][v] > 0 && is_visited[v] == false) {
                    child.push(v);
                    pre[v] = p;
                    is_visited[v] = true;
                }
            }
        }
        if(pre[n] > 0) {
            int min_capacility = 250;
            int p = n;
            while(pre[p] > 0) {
                min_capacility = min(min_capacility, capacility[pre[p]][p]);
                p = pre[p];
            }
            max_flow += min_capacility;

            p = n;
            while(pre[p] > 0) {
                capacility[pre[p]][p] -= min_capacility;
                capacility[p][pre[p]] += min_capacility;
                p = pre[p];
            }
        }else {
            break;
        }
    }
    cout << max_flow << endl;
    


    
    return 0;
}