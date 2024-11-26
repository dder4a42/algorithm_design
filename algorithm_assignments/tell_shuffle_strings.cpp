#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool tell_shuffle_strings(string &A, string &B, string &C) {
    if(C.size() != A.size() + B.size()) return false;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());
    int i=0, j=0;
    while(i < A.size() && j < B.size()) {
        if(A[i] == C[i+j]) {
            i++;
        }else if(B[j] == C[i+j]) {
            j++;
        }else {
            return false;
        }
    }
    while(i < A.size()) {
        if(A[i] == C[i+j]) {
            i++;
        }else {
            return false;
        }
    }
    while(j < B.size()) {
        if(B[j] == C[i+j]) {
            j++;
        }else {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B, C;
    cin >> A >> B >> C;
    // cout << A << endl << B << endl << C << endl;
    
    bool is_shuffle = tell_shuffle_strings(A, B, C);
    if(is_shuffle) cout << "Yes!\n";
    else cout << "No!\n";
    return 0;
}