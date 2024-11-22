#include<iostream>
#include<vector>
using namespace std;

int num_cover_vertex = 0;
vector<int> solution;

void dfs(int root, vector<vector<int>>& adj_list, vector<bool>& is_visited, vector<bool>& is_covered, vector<bool>& is_cover_vertex, int parent) {
    is_visited[root] = true;
    if(adj_list[root].size() == 1 && root != 0) {
        // cout << "find leaf " << root << endl;
        // cout << "add cover vertex " << parent << endl;
        is_cover_vertex[parent] = true;
    }
    for(auto child: adj_list[root]) {
        if(is_visited[child] == false) {
            dfs(child, adj_list, is_visited, is_covered, is_cover_vertex, root);
        }
    }
    if(is_cover_vertex[root]) {
        is_covered[root] = true;
        num_cover_vertex++;
        solution.push_back(root);
        for(auto be_covered: adj_list[root]) {
            is_covered[be_covered] = true;
        }
    }
    if(is_covered[root] == false) {
        // cout << "find uncovered vertex " << root << endl;
        if(root == 0) {
            num_cover_vertex++;
            solution.push_back(root);
        }else {
            is_cover_vertex[parent] = true;
        }
    }
    is_covered[root] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj_list(n);
    vector<bool> is_visited(n, false);
    vector<bool> is_covered(n, false);
    vector<bool> is_cover_vertex(n, false);
    for(int i=0;i<n-1;++i) {
        int u, v;
        cin >> u >> v;
        adj_list[u-1].push_back(v-1);
        adj_list[v-1].push_back(u-1);
    }
    dfs(0, adj_list, is_visited, is_covered, is_cover_vertex, 0);

    // for(auto x: solution) {
    //     cout << x << " ";
    // }
    // cout << endl;
    cout << num_cover_vertex << endl;

    return 0;
}