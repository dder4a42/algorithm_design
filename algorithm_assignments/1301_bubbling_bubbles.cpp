#include<iostream>
#include<vector>
#include<map>
using namespace std;

int n;
int* origin;
vector<int> arr;
vector<int> table;

void solve(int l, int r) {
    // solve arr[l,r]
    if(l >= r) return ;
    int mid = (r-l) / 2 + l;
    solve(l, mid);
    solve(mid+1, r);

    for(int i=l, j=mid+1;i<=mid;i++) {
        while(j<=r && arr[j] < arr[i]) {
            j++;
        }
        table[arr[i]] += (j-mid-1);
    }
    for(int i=mid, j=r;j>mid;j--) {
        while(i>=l && arr[j] < arr[i]) {
            i--;
        }
        table[arr[j]] += (mid-i);
    }

    int i=l, j=mid+1, k=0;
    int* tmp = new int [r-l+1];
    while(i<=mid && j<=r) {
        if(arr[i] <= arr[j]) {
            tmp[k] = arr[i];
            i++;
        }else {
            tmp[k] = arr[j];
            j++;
        }
        k++;
    }
    while(i<=mid) {
        tmp[k] = arr[i];
        i++, k++;
    }
    while (j<=r) {
        tmp[k] = arr[j];
        j++, k++;
    }
    for(int i=l;i<=r;i++) {
        arr[i] = tmp[i-l];
    }
    delete [] tmp;
    
    // cout << "arr[" << l << ":" << r << "] is ";
    // for(int i=l;i<=r;i++) cout << arr[i] << " \n"[i == r];
    // cout << "number count is ";
    // for(int i=0;i<n;++i) cout << table[origin[i]] << " \n"[i==n-1];
}

void bubble_sort(int a[], int n) {
    vector<int> ret(n+1, 0);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ret[a[j]]++;
                ret[a[j+1]]++;
            }
        } // after i-th inner iteration, a[n - i] is correct
    }
    for(int i=1;i<=n;i++) cout << ret[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    cin >> n;
    origin = new int [n];
    table.resize(n+1);
    for(int i=0;i<n;++i) {
        int x;
        cin >> x;
        arr.push_back(x);
        table[i+1]=0;
        origin[i] = x;
    }

    // cout << "arr[" << 0 << ":" << n-1 << "] is ";
    // for(int i=0;i<n;i++) cout << arr[i] << " \n"[i == n-1];
    // cout << "number count is ";
    // for(int i=0;i<n;++i) cout << table[origin[i]] << " \n"[i==n-1];

    solve(0, arr.size()-1);
    // bubble_sort(origin, n);
    for(int i=1;i<=n;++i) {
        cout << table[i] << " \n"[i==n];
    }
    delete [] origin;
    return 0;
}