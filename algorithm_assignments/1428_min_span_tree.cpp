#include<iostream>
#include<vector>
#include<algorithm>
// #include<queue>
using namespace std;

struct edge{
    int w, u, v;
    edge(int _w=0, int _u=0, int _v=0): w(_w), u(_u), v(_v) {}
    bool operator < (const edge& a)const {
        return w < a.w;
    }
};

class union_find
{
private:
    int size;
    int* parent;
    int* rank;
public:
    union_find(int _size);
    ~union_find();

    int find(int node) {
        if(node != parent[node]) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    bool merge(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if(pa == pb) return false;
        if(rank[pa] > rank[pb]) {
            parent[pb] = pa;
        }else if(rank[pa] < rank[pb]) {
            parent[pa] = pb;
        }
        else {
            parent[pa] = pb;
            rank[pb]++;
        }
        return true;
    }
};

union_find::union_find(int _size): size(_size) {
    parent = new int [size];
    rank = new int [size];
    for(int i=0;i<size;i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

union_find::~union_find() {
    delete parent;
    delete rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<edge> edges;
    for(int i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(u == v) continue;
        edges.push_back({w, u-1, v-1});
    }

    sort(edges.begin(), edges.end(), [](edge &a, edge &b){return a.w < b.w;});

    int weights_sum=0;
    // int cnt=0;
    union_find cycle_detect(n);
    for(auto &e: edges) {
        if(cycle_detect.merge(e.u, e.v)) {
            weights_sum += e.w;
            // cnt++;
        }
    }
    // if(cnt == n-1)
    //     cout << weights_sum << endl;
    // else
    //     cout << "orz" << endl;
    cout << weights_sum << endl;
    return 0;
}