#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#define int long long

const int MAXN = 1e6 + 5, INF = 1e18;
bool prime[MAXN];

void set_val(std::vector<int>& a, int n) {
    for (int i = 0; i < a.size() ; i++) {
        a[i] = n;
    }
}

void fill_false() {
    std::memset(prime, false, sizeof(prime));
}

void fill_true() {
    std::memset(prime, true, sizeof(prime));
}

void sieve_of_erastothenes() {
    fill_true();
    prime[0] = prime[1] = false;
    for (int i = 2; i * i < MAXN; i++) {
        if (prime[i]) {
            for (int j = 2 * i; j < MAXN; j += i) {
                prime[j] = false;
            }
        }
    }
}

int pow_mod(int a, int b, int m) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return res;
}

int digit_sum(int n) {
    int res = 0;
    while (n > 0) {
        res += n%10;
        n /= 10;
    }
    return res;
} 

void solve() {
    int n; std::cin >> n;
    std::cout << digit_sum(n) << '\n';
}

char erase[12] = {'a', 'o', 'y', 'e', 'u', 'i', 'A', 'O', 'Y', 'E', 'U', 'I'};

bool check (char c) {
    for (int i = 0; i < 12; i++) {
        if (c == erase[i]) return true;
    }
    return false;
}

signed main () {
    //int t = 1; std::cin >> t;
    //while (t--) solve();
    int n, m; std::cin >> n >> m;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];
    int cnt = n, sum = 0, c = 0;
    std::sort(v.begin(), v.end());
    int i = 0, j = n - 1;
    while (i < j) {
        if (v[i] + v[j] <= m) {
            cnt--;
            i++;
            j--;
        } else j--;
    }
    std::cout << cnt;

    return 0;
}
