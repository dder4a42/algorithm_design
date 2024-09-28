#include<iostream>
#include<iomanip>
#include<random>
using namespace std;

bool is_prime_bf(int n) {
    for(int i=2;i<=sqrt(n);++i) {
        if(n % i == 0) return false;
    }
    return true;
}

int count_prime(int n, bool (*check_prime)(int)) {
    int cnt=0;
    for(int i=2;i<=n;i++) {
        if(check_prime(i)) cnt++;
        // if(i % 100000 == 0) cout << "find " << cnt << " primes\n";
    }
    // cout << "find " << cnt << " primes\n";
    return cnt;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    cin >> n;
    double result = double(count_prime(n, is_prime_bf)) / n / n * 2;
    cout << result << endl;
    return 0;
}