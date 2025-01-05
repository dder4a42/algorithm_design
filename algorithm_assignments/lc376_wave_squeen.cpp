#include<iostream>
#include<vector>
using namespace std;

int wiggleMaxLength(vector<int>& nums) {
    int len = nums.size();
    if(len <= 2) return len;
    vector<vector<vector<int>>> state(len, vector<vector<int>> (2, vector<int> (2, 0)));
    // day, up/down, tail/len
    state[0][0][0] = state[0][1][0] = nums[0];
    state[0][0][1] = state[0][1][1] = 1;
    for(int i=1;i<len;i++) {
        
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }
    int result = wiggleMaxLength(arr);
    cout << result << endl;

    
    return 0;
}