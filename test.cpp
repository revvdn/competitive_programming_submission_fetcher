#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
#define int long long

signed main () {
    int n, sum = 0; std::cin >> n;
    int val = LLONG_MIN;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        sum = std::max(sum + x, x);
        val = std::max(val, sum);
    }
    std::cout << val;

    return 0;
}