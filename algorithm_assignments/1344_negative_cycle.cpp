#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>

using namespace std;
typedef long long ll;
const ll INF = 1E15+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // vector< unordered_map<int, ll> > graph(n+1);
    vector<vector<pair<int, ll>>> graph(n+1);
    for(int i=0;i<m;++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // graph[u][v] = w;
        graph[u].push_back(pair<int, ll> (v, w));
    }

    vector<ll> dist(n+1, 0);
    vector<int> pre(n+1, 0);
    
    for(int round=0; round < n; ++round) {
        vector<ll> tmp(dist);
        for(int i=1;i<=n;++i) {
            for(auto iter=graph[i].begin(); iter != graph[i].end(); ++iter) {
                int v = iter->first;
                ll weight = iter->second;
                // cout << "check u(" << i << ")=" << tmp[i] << " v(" << v << ")=" << dist[v] << " with w=" << weight << endl;
                if(dist[v] > tmp[i] + weight) {
                    pre[v] = i;
                    dist[v] = tmp[i] + weight;
                }
            }
        }
        // cout << "after " << round << " update, dist[] is ";
        // for(auto x: dist) cout << x << " ";
        // cout << endl;
    }

    // cout << "dist are ";
    // for(auto x: dist) cout << x << " ";
    // cout << endl;

    int start=0;
    bool is_cycle = false;
    for(int i=1;i<=n;++i) {
        for(auto iter=graph[i].begin(); iter != graph[i].end(); ++iter) {
            int v = iter->first;
            ll weight = iter->second;
            if(dist[v] > dist[i] + weight) {
                pre[v] = i;
                start = v;
                is_cycle = true;
                break;
            }
        }
    }

    if(is_cycle) cout << "Yes" << endl;
    else {cout << "No" << endl; return 0;}

    
    int length=1;
    vector<int> path;
    vector<bool> is_visited(n+1, false);
    int p = pre[start];
    while(is_visited[p] == false) {
        is_visited[p] = true;
        p = pre[p];
    }
    start = p;
    path.push_back(start);
    p = pre[p];
    while(p != start) {
        path.push_back(p);
        ++length;
        p = pre[p];
    }
    
    cout << length << endl;
    for(int i=path.size()-1; i>=0; --i) cout << path[i] << " ";
    cout << endl;
    return 0;
}