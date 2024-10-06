#include <bits/stdc++.h>
using namespace std;

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

int main() {
    int n, pivot;
    cin >> n >> pivot;
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    auto [l, r] = partition(arr, pivot);
    for (auto i : arr) cout << i << ' ';
    cout << '\n' << l << ' ' << r << '\n';
}