#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

int main() {
    int n;
    bool is_exist = true;
    cin >> n;
    vector<string> read;
    map<string, string> f;
    for(int i=0;i<n;i++) {
        string tmp;
        cin >> tmp;
        read.push_back(tmp);
    }
    for(int j=0;j<n;j++) {
        string tmp;
        cin >> tmp;
        if(f.find(read[j]) != f.end()) {
            cout << "check exist item\n";
            if(f[read[j]] != tmp) {
                is_exist = false;
                break;
            }
        }else {
            f[read[j]] = tmp;
            cout << "add new relation " << tmp << " <-> " << read[j] << endl;
        }
    }
    if(is_exist) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}