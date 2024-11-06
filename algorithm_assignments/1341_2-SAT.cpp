#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;

int n, m;
int travel_time = 0;
int num_evalue_propositon = 0;
bool is_satisfiable = true;

struct node_end_time {
    int vertex;
    int end_time;
    node_end_time(int _ver=0, int _end=0): vertex(_ver), end_time(_end) {}
};

//odd index p=1, even index p=0
inline int get_vertex(int x, int truth) {
    return 2*x-truth;
}

inline int get_reverse_vertex(int p) {
    if(p%2) return p+1;
    else return p-1;
}

inline bool is_contradict(int p, int q) {
    return (p == q+1 && q%2 == 1) || (q == p+1 && p%2 == 1);
}

inline int get_proposition(int index) {
    if(index % 2 == 1) {
        return (index+1) / 2;
    }else return index / 2;
}

inline int get_truth_value(int index) {
    return index % 2 == 1;
}

void dfs(int vertex, vector<vector<int> >& graph, vector<bool>& is_visited, vector<node_end_time>& end_time) {
    // if(is_visited[vertex]) return ;
    is_visited[vertex] = true;
    ++travel_time;
    for (auto iter : graph[vertex]) {
        if (is_visited[iter] == false) {
            dfs(iter, graph, is_visited, end_time);
        }
    }
    ++travel_time;
    end_time[vertex].vertex = vertex;
    end_time[vertex].end_time = travel_time;
    // cout << "end a vertex " << vertex << " with time " << travel_time << endl;
}

void shrink_vertex(int vertex, vector<vector<int> >& graph, vector<bool>& is_visited, int representative_element, vector<int>& scc, vector<int>& solution, vector<bool>& is_evaluated) {
    if(!is_satisfiable || num_evalue_propositon >= n) return ;
    is_visited[vertex] = true;
    scc[vertex] = representative_element;
    int propositon = get_proposition(vertex);
    if(is_evaluated[propositon] == false) {
        is_evaluated[propositon] = true;
        num_evalue_propositon++;
        solution[propositon] = get_truth_value(vertex);
        // cout << "evalue " << propositon << " to " << solution[propositon] << endl;
    }else if(scc[vertex] == scc[get_reverse_vertex(vertex)]) is_satisfiable = false;
    for (auto iter : graph[vertex]) {
        if (is_visited[iter] == false) {
            shrink_vertex(iter, graph, is_visited, representative_element, scc, solution, is_evaluated);
        }
    }
}



void create_graph(vector<vector<int>>& graph, vector<vector<int>>& re_graph) {
    for(int index=0;index<m;++index) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        if(i == j && a != b) continue; // self-loop
        if(a && b) {
            graph[2*i].push_back(2*j-1);
            graph[2*j].push_back(2*i-1);
            re_graph[2*j-1].push_back(2*i);
            re_graph[2*i-1].push_back(2*j);
        }else if(!a && b) {
            graph[2*i-1].push_back(2*j-1);
            graph[2*j].push_back(2*i);
            re_graph[2*j-1].push_back(2*i-1);
            re_graph[2*i].push_back(2*j);
        }else if(a && !b) {
            graph[2*i].push_back(2*j);
            graph[2*j-1].push_back(2*i-1);
            re_graph[2*j].push_back(2*i);
            re_graph[2*i-1].push_back(2*j-1);
        }else {
            graph[2*i-1].push_back(2*j);
            graph[2*j-1].push_back(2*i);
            re_graph[2*j].push_back(2*i-1);
            re_graph[2*i].push_back(2*j-1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 2-SAT
    // int n, m;
    cin >> n >> m;
    // create graph
    vector<vector<int> > graph(2*n+1);
    vector<vector<int> > re_graph(2*n+1);
    create_graph(graph, re_graph);
    // cout << "create graph" << endl;

    // find SCC
    vector<node_end_time> end_time(2*n+1);
    vector<bool> is_visited(2*n+1, false);

    for(int i=1;i<=2*n;++i) {
        if(is_visited[i] == false) {
            dfs(i, re_graph, is_visited, end_time);
        }
    }

    // cout << "mark end time" << endl;

    sort(end_time.begin()+1, end_time.end(), [](node_end_time& a, node_end_time& b) {return a.end_time > b.end_time;});
    
    // treat vertices in the same SCC a super vertex
    fill(is_visited.begin(), is_visited.end(), false);
    vector<int> belong_to_scc(2*n+1, 0);
    vector<bool> is_envalue(n+1, false);
    vector<int> solution(n+1, 0);
    for(int i=1;i<=2*n;++i) {
        int u = end_time[i].vertex;
        if(is_visited[u] == false) {
            // dag[u] = {};
            // in_degree[u] = 0;
            shrink_vertex(u, graph, is_visited, u, belong_to_scc, solution, is_envalue);
        }
    }
    // cout << "shrink vertex" << endl;

    vector<vector<int>>().swap(re_graph);
    // vector<node_end_time>().swap(end_time);
    // vector<bool>().swap(is_visited);

    // check if contradict
    if(is_satisfiable) cout << "Yes" << endl;
    else {
        cout << "No" << endl; return 0;
    }

    // cout << "check satisfiable" << endl;

    for(int i=1;i<=n;++i) {
        cout << solution[i] << " ";
    }
    cout << endl;

    return 0;
}