#include<iostream>
#include<vector>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> array(n);
    for(int& x: array) {
        cin >> x;
    }
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> choice(n, vector<int>(n, 0));

    for(int i=0;i<n;i++) {
        dp[i][i] = array[i];
    }
    for(int delta=1;delta<n;delta++) {
        for(int j=0;j<n-delta;j++) {
            if(delta == 1) {
                if(array[j] > array[j+1]) {
                    choice[j][j+1] = 0;
                    dp[j][j+1] = array[j];
                }else {
                    choice[j][j+1] = 1;
                    dp[j][j+1] = array[j+1];
                }
            }
            else {
                int gain1=array[j], gain2=array[j+delta];
                if(choice[j+1][j+delta] == 0) {
                    gain1 += dp[j+2][j+delta];
                }else {
                    gain1 += dp[j+1][j+delta-1];
                }
                if(choice[j][j+delta-1] == 0) {
                    gain2 += dp[j+1][j+delta-1];
                }else {
                    gain2 += dp[j][j+delta-2];
                }
                if(gain1 > gain2) {
                    choice[j][j+delta] = 0;
                    dp[j][j+delta] = gain1;
                }else {
                    choice[j][j+delta] = 1;
                    dp[j][j+delta] = gain2;
                }
            }
        }
    }

    // for(int i=0;i<n;i++) {
    //     for(int j=0;j<n;j++) {
    //         cout << dp[i][j] << "(" << choice[i][j] << ") ";
    //     }
    //     cout << endl;
    // }

    int bob_max_gain = min(dp[0][n-2], dp[1][n-1]);
    cout << bob_max_gain << endl;

    int alice_gain = 0;
    int bob_gain = 0;
    int lh=0, rh=n-1;
    int who_round = 0;
    int rounds = 1;
    while(lh <= rh) {
        // cout << "rounds " << rounds++ << endl;
        if(who_round == 0) {
            char take=0;
            cin >> take;
            if(take == 'L') {
                // cout << "alice get " << array[lh] << endl;
                alice_gain += array[lh];
                lh++;
            }else {
                // cout << "alice get " << array[rh] << endl;
                alice_gain += array[rh];
                rh--;
            }
        }else {
            if(choice[lh][rh] == 0) {
                // cout << "bob get " << array[lh] << endl;
                cout << "L" << endl;
                bob_gain += array[lh];
                lh++;
            }else {
                // cout << "bob get " << array[rh] << endl;
                cout << "R" << endl;
                bob_gain += array[rh];
                rh--;
            }
        }
        who_round = 1 - who_round;
    }
    // cout << alice_gain << endl;
    // cout << bob_gain << endl;

    return 0;
}

void greedy(vector<int>& array) {
    int opposite_gain=0;
    int max_gain=0;
    int lptr=0, rptr=array.size()-1;
    if(array.size() == 2) max_gain = min(array[0], array[1]);
    while(lptr <= rptr) {
        if(array[lptr] - max(array[lptr+1], array[rptr]) > array[rptr] - max(array[lptr], array[rptr-1])) {
            opposite_gain += array[lptr];
            // cout << "player 1 choose " << array[lptr] << endl;
            lptr++;
        }else {
            opposite_gain += array[rptr];
            // cout << "player 1 choose " << array[rptr] << endl;
            rptr--;
        }
        if(lptr > rptr) break;
        if(array[lptr] - max(array[lptr+1], array[rptr]) > array[rptr] - max(array[lptr], array[rptr-1])) {
            max_gain += array[lptr];
            // cout << "player 2 choose " << array[lptr] << endl;
            lptr++;
        }else {
            max_gain += array[rptr];
            // cout << "player 2 choose " << array[rptr] << endl;
            rptr--;
        }
    }
    cout << max_gain << endl;

    int cnt=0, gain=0;
    lptr=0, rptr=array.size()-1;
    while(cnt < array.size()/2) {
        char player1_choice;
        cin >> player1_choice;
        if(player1_choice == 'L') lptr++;
        else rptr--;

        if(array[lptr] - max(array[lptr+1], array[rptr]) > array[rptr] - max(array[lptr], array[rptr-1])) {
            cout << "L" << endl;
            gain += array[lptr];
            // cout << "player 2 choose " << array[lptr] << endl;
            lptr++;
        }else {
            cout << "R" << endl;
            gain += array[rptr];
            // cout << "player 2 choose " << array[rptr] << endl;
            rptr--;
        }
        cnt++;
    }
    // cout << gain << endl;
}

void play_with_fool(vector<int>& array, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> choice(n, vector<int>(n, 0));

    for(int i=0;i<n;i++) {
        dp[i][i] = array[i];
    }
    for(int delta=1;delta<n;delta++) {
        for(int j=0;j<n-delta;j++) {
            if(delta == 1) {
                if(array[j] > array[j+1]) {
                    choice[j][j+1] = 0;
                    dp[j][j+1] = array[j];
                }else {
                    choice[j][j+1] = 1;
                    dp[j][j+1] = array[j+1];
                }
            }else {
                choice[j][j+delta] = 0;
                dp[j][j+delta] = dp[j+1][j+delta-1] + array[j];
                dp[j][j+delta] = max(dp[j][j+delta], dp[j+2][j+delta] + array[j]);
                if(dp[j+1][j+delta-1] + array[j+delta] > dp[j][j+delta]) {
                    choice[j][j+delta] = 1;
                    dp[j][j+delta] = dp[j+1][j+delta-1] + array[j+delta];
                }
                if(dp[j][j+delta-2] + array[j+delta] > dp[j][j+delta]) {
                    choice[j][j+delta] = 1;
                    dp[j][j+delta] = dp[j][j+delta-2] + array[j+delta];
                }
            }
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout << dp[i][j] << "(" << choice[i][j] << ") ";
        }
        cout << endl;
    }
    int alice_gain = 0;
    int bob_gain = 0;
    int lh=0, rh=n-1;
    int who_round = 0;
    int rounds = 1;
    while(lh <= rh) {
        cout << "rounds " << rounds++ << endl;
        if(who_round == 0) {
            if(choice[lh][rh] == 0) {
                cout << "alice get " << array[lh] << endl;
                alice_gain += array[lh];
                lh++;
            }else {
                cout << "alice get " << array[rh] << endl;
                alice_gain += array[rh];
                rh--;
            }
        }else {
            if(choice[lh][rh] == 0) {
                cout << "bob get " << array[lh] << endl;
                bob_gain += array[lh];
                lh++;
            }else {
                cout << "bob get " << array[rh] << endl;
                bob_gain += array[rh];
                rh--;
            }
        }
        who_round = 1 - who_round;
    }
    cout << alice_gain << endl;
    cout << bob_gain << endl;
}