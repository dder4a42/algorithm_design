#include<iostream>
#include<vector>
#include <random>
#include <chrono>
using namespace std;

// use precise time as random seed
const int RANDOM_SEED = chrono::system_clock::now().time_since_epoch().count();
mt19937 rng(RANDOM_SEED); // random number generator


int n, k;
vector <int> a;
void read_input_data_vector()
{
 int m;
 cin >> n >> k >> m; a.resize(n);
 for (int i = 0; i < m; i++)
 {
     cin >> a[i];
 }
 unsigned int z = a[m - 1];
 for (int i = m; i < n; i++)
 {
     z ^= z << 13;
     z ^= z >> 17;
     z ^= z << 5;
     a[i] = z & 0x7fffffff;
 }
}

pair<int, int> partition(vector <int> &a, int pivot) {
    int i=0, j=0;
    int l=0, r=0;
    while (j<a.size()) {
        if(a[j] < pivot) {
            swap(a[j], a[i]);
            ++i;
        }
        ++j;
    }
    l = i;
    j = i;
    while (j<a.size()) {
        if(a[j] == pivot) {
            swap(a[j], a[i]);
            ++i;
        }
        ++j;
    }
    r = i;
    return {l, r};
}

int choose_pivot(vector<int>& arr, int l, int r) {
    // int index = dist(rng) % (r-l+1) + l;
    uniform_int_distribution<int> dist(l, r);
    int index = dist(rng);
    // cout << "pivot index is " << index << "\n";
    return arr[ index ];
}

int quick_select(vector<int>& arr, int l, int r, int k) {
    if(l >= r) return arr[l];
    int pivot = choose_pivot(arr, l, r);
    // cout << "pivot is " << pivot << "\n";
    auto [nl, nr] = partition(arr, pivot);
    // cout << "arr is ";
    // for(auto x: a) cout << x << " ";
    // cout << "\n";
    // cout << "new left and new right is " << nl << " " << nr << "\n";
    if(nl > k) {
        return quick_select(arr, l, nl, k);
    }else if(nl <= k && nr > k) {
        return pivot;
    }else {
        return quick_select(arr, nr, r, k);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input_data_vector();
    // for(auto x: a) cout << x << " ";
    // cout << "\n";
    int result = quick_select(a, 0, a.size()-1, k-1);
    cout << result << "\n";
    return 0;
}