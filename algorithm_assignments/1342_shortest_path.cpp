#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
typedef long long ll;
ll INF = 1E15 + 7;

struct min_distance {
    int vertex;
    ll distance_to_s;
    min_distance(int _ver=0, ll _dis=INF) {vertex=_ver, distance_to_s=_dis;}
    bool operator< (const min_distance& b)const {
        return distance_to_s < b.distance_to_s;
    }
    bool operator> (const min_distance& b)const {
        return distance_to_s > b.distance_to_s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector< vector<ll> > graph(n+1, vector<ll> (n+1, INF));
    // cout << "set edges' weights:" << endl;
    for(int i=0;i<m;i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if(w < graph[u][v]) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }
    // cout << "dijkstra:" << endl;
    priority_queue<min_distance, vector<min_distance>, greater<min_distance>> nodes_to_be_added;

    for(int i=1;i<=n;i++) {
        if(i == s) nodes_to_be_added.push(min_distance{s, 0});
        else nodes_to_be_added.push(min_distance{i, INF});
    }
    vector<ll> min_distance_to_s(n+1, INF);
    min_distance_to_s[s]=0;
    vector<bool> is_added(n+1, 0);
    nodes_to_be_added.push(min_distance{s, 0});
    while(nodes_to_be_added.empty() == false) {
        min_distance tmp = nodes_to_be_added.top();
        int u = tmp.vertex;
        nodes_to_be_added.pop();
        if(is_added[u]) continue;
        is_added[u]=true;
        //update distance
        for(int j=1;j<=n;j++) {
            if(graph[u][j] < INF && is_added[j] == false) {
                if(min_distance_to_s[u]+graph[u][j] < min_distance_to_s[j]) {
                    min_distance_to_s[j] = min_distance_to_s[u]+graph[u][j];
                    nodes_to_be_added.push( min_distance{j, min_distance_to_s[j]} );
                }
            }
        }
    }
    cout << min_distance_to_s[t] << endl;
    return 0;
}

void dijkstra1() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector< vector<ll> > graph(n+1, vector<ll> (n+1, INF));
    // cout << "set edges' weights:" << endl;
    for(int i=0;i<m;i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if(w < graph[u][v]) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }
    // cout << "dijkstra:" << endl;
    int u=s;
    int cnt=1;
    vector<ll> min_distance_to_s(n+1, INF);
    min_distance_to_s[s]=0;
    vector<bool> is_added(n+1, 0);
    is_added[s]=true;
    while(true) {
        //update distance
        for(int j=1;j<=n;j++) {
            if(graph[u][j] < INF && is_added[j] == false) {
                min_distance_to_s[j] = min(min_distance_to_s[j], min_distance_to_s[u]+graph[u][j]);
            }
        }
        int next_add=u;
        ll min_distance_once=INF;
        int i=1;
        for(;i<=n;i++) {
            if(is_added[i] == false &&  min_distance_to_s[i] < min_distance_once) {
                min_distance_once = min_distance_to_s[i];
                next_add = i;
            }
        }
        if(cnt >= n || is_added[t]) break;
        is_added[next_add] = true;
        u = next_add;
        cnt++;
    }
    cout << min_distance_to_s[t] << endl;
}