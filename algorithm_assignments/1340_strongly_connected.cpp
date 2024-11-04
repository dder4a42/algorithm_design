#include<iostream>
#include<vector>
#include<stack>
#include<set>
#include<algorithm>
using namespace std;
typedef long long ll;

int travel_time=0;

struct node_end_time {
    int vertex;
    int end_time;
    node_end_time(int _ver=0, int _end=0): vertex(_ver), end_time(_end) {}
    // bool operator > (const node_end_time & b) const {
    //     return end_time > b.end_time;
    // }
    // bool operator < (const node_end_time & b) const {
    //     return end_time < b.end_time;
    // }
};

void dfs(int vertex, vector<set<int> >& graph, vector<bool>& is_visited, vector<node_end_time>& end_time) {
    // if(is_visited[vertex]) return ;
    is_visited[vertex] = true;
    ++travel_time;
    for (auto iter = graph[vertex].begin(); iter != graph[vertex].end(); ++iter) {
        if (is_visited[*iter] == false) {
            dfs(*iter, graph, is_visited, end_time);
        }
    }
    ++travel_time;
    end_time[vertex].vertex = vertex;
    end_time[vertex].end_time = travel_time;
    // cout << "end a vertex " << vertex << " with time " << travel_time << endl;
}

void dfs_twice(int vertex, vector<set<int> >& graph, vector<bool>& is_visited, ll& num_vertex) {
    // if(is_visited[vertex]) return ;
    is_visited[vertex] = true;
    ++num_vertex;
    for (auto iter = graph[vertex].begin(); iter != graph[vertex].end(); ++iter) {
        if (is_visited[*iter] == false) {
            dfs_twice(*iter, graph, is_visited, num_vertex);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector< set<int> > graph(n+1);
    vector< set<int> > re_graph(n+1);
    for(int i=0;i<m;++i) {
        int u, v;
        cin >> u >> v;
        if(u == v) continue;
        graph[u].insert(v);
        re_graph[v].insert(u);
    }

    vector<node_end_time> end_time(n+1);
    vector<bool> is_visited(n+1, false);

    for(int i=1;i<=n;++i) {
        if(is_visited[i] == false) {
            dfs(i, re_graph, is_visited, end_time);
        }
    }

    sort(end_time.begin()+1, end_time.end(), [](node_end_time& a, node_end_time& b) {return a.end_time > b.end_time;});
    
    // for(auto x: end_time) {
    //     cout << x.vertex << "'s end time is " << x.end_time << endl;
    // }
    // cout << endl;

    vector<bool> is_visited_twice(n+1, false);
    ll num_pairs=0;
    for(int i=1;i<=n;++i) {
        int u = end_time[i].vertex;
        if(is_visited_twice[u] == false) {
            ll num_vertices=0;
            dfs_twice(u, graph, is_visited_twice, num_vertices);
            // cout << "This SCC has " << num_vertices << " vertices." << endl;
            num_pairs += num_vertices * (num_vertices-1) / 2;
        }
    }
    cout << num_pairs << endl;
    
    // stack<int> tmp;
    // for(int i=1;i<=n;++i) {
    //     if(is_visited[i] == false) {
    //         tmp.push(i);
    //         while(tmp.empty() == false) {
    //             int u = tmp.top();
    //             tmp.pop();
    //             is_visited[u] = true;
    //             for(auto iter = re_graph[u].begin(); iter != re_graph[u].end(); ++iter) {
    //                 if(is_visited[*iter] == false) {
    //                     tmp.push(*iter);
    //                 }
    //             }
    //         }
    //     }
    // }

    
    return 0;
}