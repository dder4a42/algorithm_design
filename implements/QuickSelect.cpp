#include<iostream>
#include<vector>
#include<cstdlib>
#include<cassert>
using namespace std;

enum PIVOT_MODE{PIVOT, PIVOT_INDEX};
PIVOT_MODE pivot_mod;

void print_arr(vector<int>& arr) {
    cout << "arr is ";
    for(auto x: arr) {
        cout << x << " ";
    }
    cout << "\n";
}

int partition(vector<int>& arr, int left, int right, int pivot_index) {
    int smaller=left, i=left, x;
    if(pivot_mod == PIVOT_INDEX) {
        x = arr[pivot_index];
        // swap(arr[pivot_index], arr[right]);
        cout << "partiton start, pivot index is " << pivot_index << "\n";
    }else
        x = pivot_index;
    while (i<right) {
        if(arr[i] <= x) {
            swap(arr[smaller], arr[i]);
            smaller++;
        }
        i++;
    }
    // swap(arr[smaller], arr[right]);
    print_arr(arr);
    return smaller;
}

int quick_select(vector<int>& arr, int left, int right, int k, int (*choose_pivot)(vector<int>&, int, int)) {
    if(left == right) return arr[left];

    int pivot = choose_pivot(arr, left, right);
    int pivot_index = partition(arr, left, right, pivot);

    if(pivot_index > k) {
        return quick_select(arr, left, pivot_index-1, k, choose_pivot);
    }else if(k == pivot_index) {
        return arr[pivot_index];
    }else {
        return quick_select(arr, pivot_index+1, right, k, choose_pivot);
    }
    return 0;
}

int random_choose(vector<int>& arr, int left, int right) {
    pivot_mod = PIVOT_INDEX;
    return left + rand()%(right-left+1);
}

int select_median_of_group(vector<int>& arr, int left, int right) {
    pivot_mod = PIVOT;
    const int len = right-left+1;
    for(int i=left;i<right+1;i++) {
        int x = arr[i], j;
        for(j=i-1;j>=left;j--) {
            if(arr[j] > x) arr[j+1] = arr[j];
            else break;
        }
        arr[j+1] = x;
    }
    return arr[left + len / 2];
}

int median_of_medians(vector<int>& arr, int left, int right) {
    vector<int> medians;
    const int group_size = 5;
    for(int i=left; i<right+1; i+=group_size) {
        int group_median = select_median_of_group(arr, i, min(i+group_size-1, right));
        medians.push_back(group_median);
    }
    return quick_select(medians, 0, medians.size()-1, medians.size()/2, median_of_medians);
}

int QuickSelect(vector<int>& arr, int k) {
    assert(k>=0 && k<arr.size());
    return quick_select(arr, 0, arr.size()-1, k-1, median_of_medians);
}

int main() {
    vector<int> arr;
    int k;
    cin >> k;

    do{
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }while(cin.get() != '\n');

    print_arr(arr);
    int kth = QuickSelect(arr, k);
    print_arr(arr);
    cout << "k-th is " << kth << "\n";
    // int median = median_of_medians(arr, 0, arr.size()-1);
    // cout << median << endl;
    return 0;
}