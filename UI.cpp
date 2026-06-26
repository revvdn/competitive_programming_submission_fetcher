//#include<iostream>
//#include<algorithm>
//#include<cstring>
//#include<vector>

//#define int long long

/*
const int MAXN = 3e5 + 15, MOD = 1e9 + 7;

int a[MAXN], fact[MAXN], tree[MAXN], b[MAXN], n;
//std::vector<int> b, tmp;

void precompute() {
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = (1LL * fact[i - 1] * i)%MOD;
	}
}

int getsum (int i) {
	int sum = 0;
	
	while (i > 0) {
		sum += tree[i];
		i -= i & (-i);
	}

	return sum;
}

void update(int i, int num) {
	while (i < MAXN) {
		tree[i] += num;
		i += i & (-i);
	}
}

void fenwick() {
	for (int i = 1; i <= n; i++) {
		update(a[i], 1);
	}
}

signed main () {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::memset(tree, 0, sizeof(tree));
	
	precompute();

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; std::cin >> x;
		a[i] = b[i] = x;
		//update(x, 1);
	}

	std::sort(b + 1, b + n + 1);

	for (int i = 1; i <= n; i++) {
		int ord = std::lower_bound(b, b + n, a[i]) - b;
		a[i] = ord;
	}
	//compress();
	//std::sort(b.begin(), b.end());

	fenwick();

	int ans = 0;
	for (int i = n; i >= 1; i--) {
		int idx = n - i + 1;

		int cnt = getsum(a[idx] - 1);
		ans = (ans + (1LL * cnt * fact[i - 1]) %MOD) %MOD;

		update(a[idx], -1);
	}

	std::cout << (ans + 1) %MOD;
	return 0;
}

finally, ac jadi full solution nya itu cuma kita urutin dia berdasarkan indeks relatif nya, jaid kalau misal dikasi 3, 7, 10 itu kita bisa jadiin 
1, 2, 3 karena 3 < 7 < 10, dan kalau misal ditanyain 7 3 10 yaudah berarti kita sama aja nemuin 2 1 3 dari permutasi 1 2 3.
cara untuk bisa ngelakuin itu adalah dengan gunain yang namanya lower_bound

jadi kalau misal dikasi suatu range misal a, b, c; kita urutin dulu berdasarkan itu dan kemudain kita cara a[i] itu di posisi berapa si dari b[i] dan kalau udah nemu di index ke berapa
berati yaudah kita berhasil nemuin dia ada di bagian mana. sebenernya bisa cari manual tapi kebetulan karena aku orangnya malesan jadi aku pakai stl aja ya meskipun itu lambar si wkwkw

*/

/*
jadi di sini kita diberi sebuah 

				1
			2		2
		3		4		3
	4		7		7		4
5		10		14		10		5

kalau misal ditanya 4 2 kenapa output nya 7 itu karen dia di posisi 2 dari kanan 4

atau misal kita track itu berarti 

4 7 7 4 yang berdasarkan index 1 2 3 4

kalau misal kita mengacu ke segitiga pascal yang asli itu berarti 

					1
				1		1
			1		2		1
		1		3		3		1
	1		4		6		4		1
1		5		10		10		5		1

kalau misal ada 10^6 ^ 2 berarti itu bakal berukuran 10 ^ 12


*/
/*
const int MAXN = 1005;

std::vector<std::vector<int>> sto (MAXN, std::vector<int> (MAXN, -1));
*/
/*
int dfs (int r, int c) {
	if (c == 1 || c == r) return r;

	if (c < 1 || c > r) return 0;

	if (sto[r][c] != -1) return sto[r][c];

	sto[r][c] = dfs(r - 1, c - 1) + dfs(r - 1, c);

	return sto[r][c];
}

void construct (int target) {
	for (int r = 1; r <= target; r++) {
		for (int c = 1; c <= r; c++) {
			dfs(r, c);
		}
	}
}

i think i must find the modified formula based on this 

what if nCr with (r-1)C(c-2) + (r)C(c)

but the contraint are so large, it's 10^6 what if it ask for (1e6 - 15)C(1e5 + 57) that would be incredibly large and complex even if i done the modulo




signed main () {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	//construct(MAXN);
	int n, k; std::cin >> n >> k;
	std::cout << sto[n][k];
	return 0;
}

*/

/*
bedah test case

9
OSKOSPOSN

jadi kalau misal dibuat jadi freq
O -> 3
S -> 3
K -> 1
P -> 1
N -> 1

susunan yang mungkin itu 
O S K O S 

*/
/*
#include<iostream>
#include<algorithm>
#include<cstring>

int freq[26];

int main () {
	std::memset(freq, 0, sizeof(freq));

	int n; std::cin >> n;
	std::string s; std::cin >>s;

	for (int i = 0; i < n; i++) {
		freq[s[i] - 'A']++;
	}

	std::sort(freq, freq + 26, std::greater<int>());

	int idx = 0, ans = 0;
	while (true) {
		if (freq[idx] > 0) {
			ans++;
			freq[idx]--;
		}
		else break;

		idx = (idx + 1)%3;
	}

	std::cout << (ans < 3 ? -1 : ans);
	return 0;
}

kalau dari pengamatan ku harusnya o(N) udah bisa nyelesain masalahnya karena cuma 500 doang wkwkwk

lanjut ke prob terkahir
*/

/*
jadi kita dikasi sebuah array yang dimana kita udah di salah satu posisi 
pake cara awal kek nya bisa satu satu

3
GBK
BKK

pake freq array jadi 
case 1:
G -> 1
B- > 1
K -> 1

case 2:
G -> 0
B -> 1
K -> 2

dari sini kita cuma bisa ngambil case 
GK -> G kita cuma 1 sementaar K musuh 2 berarti cuma bisa ambil 1 K-- = 1
BG -> karena musuh gapunya G jadi, 0
KB -> kita punya K = 1, dan musuh punya B = 1, berarti kita cuma bisa ambil satu doang yang berarti 2

buat mereka jadi indeks yang berurutan
G - A = 6, berarti formula nya nanti jadi 'G' - 'A' - 5
B - A = 1, berarti formulanya nanti jadi 'B' - 'A' - 1
K - A = 10, berarti nanti formulanya jadi 'K' - 'A' - 8
*/
/*
#include<iostream>
#include<map>
#include<string>

std::map<char, int> freq1, freq2;

int main () {
	int n; std::cin >> n;
	std::string s1, s2; std::cin >> s1 >> s2;

	for (int i = 0; i < n; i++) {
		freq1[s1[i]]++;
		freq2[s2[i]]++;
	}

	int ans = 0;

	int match1 = std::min(freq1['G'], freq2['K']);
	ans += match1;
	freq1['G'] -= match1;
	freq2['K'] -= match1;

	int match2 = std::min(freq1['B'], freq2['G']);
	ans += match2;
	freq1['B'] -= match2;
	freq2['G'] -= match2;

	int match3 = std::min(freq1['K'], freq2['B']);
	ans += match3;
	freq1['K'] -= match3;
	freq2['B'] -= match3;

	std::cout << ans;
	return 0;
}
*/

/*
dikasi sebuah data 1 - N di kedua sisi dimana salah kita harus ngehubungin kota kota tersebut
test case pertama
2 1 3 4 5

4 5 1 2 3

ide yang pertama kupikirin adalah kita cari longest increasing subsequence yang dari kedua sisi misal 
sisi 1 :  2 3 4 5 | 1 3 4 5 -> 4 
sisi 2 : 4 5 | 1 2 3 -> paling tinggi 3

tapi di jawaban yang benar itu 2, berarti salah

ide 2 : kita ambil salah satu indeks kemudian baru deteksi lcs 

karena n = 1e3 atmost kita cuma bisa n ^ 2 log n

buat table biner 

____4___5___1___2___3_
2 | 0   0   0   1   0
1 | 0   0   1   1   1
3 | 0   0   1   1   2
4 | 1   1   1   1   2
5 | 1   2   2   2   2

*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

int main () {
	int n; std::cin >> n;

	int a[n], b[n];
	for (int i = 0; i < n; i++) 
		std::cin >> a[i];
	for (int i = 0; i < n; i++) 
		std::cin >> b[i];

	int dp[n + 5][n + 5];
	std::memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (a[i - 1] == b[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	std::cout << dp[n][n];
	return 0;
}
*/

/*
jadi disini disuruh nyari semua longest palindromic dari seuatu string

ini sama aja kayak problem longest palindromic sub sequence
*/
/*
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

std::string s;

int find (int lo, int hi) {
	if (lo > hi) return 0;
	if (lo == hi) return 1;
	if (s[lo] == s[hi]) return find(lo + 1, hi - 1) + 2;
	return std::max(find(lo, hi - 1), find(lo + 1, hi));
}


void solve() {
	std::cin >> s;
	int n = s.size();
	std::vector<int> curr(n), prev(n);
	
	for (int i = n - 1; i >= 0; --i) {
		curr[i] = 1;

		for (int j = i + 1; j < n; ++j) {
			if (s[i] == s[j]) {
				curr[j] = prev[j - 1] + 2;
			}
			else {
				curr[j] = std::max(prev[j], curr[j - 1]);
			}
		}

		prev = curr;
	}
	std::cout << curr[n - 1] << '\n';
}

int main () {
	int t; std::cin >> t;
	while (t--) solve();
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>
#include<algorithm>

const int MAXN = 2e5+5;
int prefa[MAXN], prefp[MAXN];

int main () {
	std::string s; std::cin >> s;
	int n = s.size();

	int totp = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'P') totp++;
	}
	//std::cout << totp << '\n';

	bool firstO = false, firstS = false, firstN = false;
	int ans = 0, cnt = 0;
	
	for (int i = 0; i < n; i++) {
		if (s[i] == 'O') firstO = true, cnt++;
		if (s[i] == 'S') firstS = true, cnt++;
		if (s[i] == 'N') firstN = true, cnt++;

		if (s[i] == 'P') {
			if (firstN && firstS && firstO) ans = std::max(ans, cnt + totp);
			totp--;
		}
	}

	std::cout << (ans == 0 ? -1 : ans);
	return 0;
}
*/
/*
#include<iostream>
#include<algorithm>

#define ll long long
const ll BOUND = 1e9, INF = 3e9;

int main () {
	ll n, p, l; 
	std::cin >> n >> p >> l;

	ll lo = 1, hi = INF, ans;
	bool over = true;
	while (lo <= hi) {
		ll m = lo + ((hi - lo) / 2);
		//std::cout << m << '\n';
		ll side1 = m / l;
		ll side2 = m / p;
		ll cnt;
		if (side1 > 0 && side2 > n / side1) cnt = n;
		else cnt = side1 * side2;
		if (cnt >= n) {
			hi = m - 1;
		} 
		else {
			lo = m + 1;
		}
	}
	std::cout << lo;
	return 0;
}
*/

/*
18 

list bilangan prima yang habis membagi 18, itu 2 sama 3

faktorisasi prima dari 18 = 2 * 3^2
berarti banyak solusi nya bandingin 
3 * 3 = 9
2 * 3 = 6

berarti dari faktorisasi prima diambil pangkat yang lebih besar terus nanti ditambah sama 1
terus nanti kalau udah ditambah 1 tinggal kaliin lagi yang terbesar

case 60 = 2^2 * 3 * 5

berarti bakal 

urutan 

pake sieve of erasthothesnes buat list bilangan prima
*/

/*
#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>

#define int long long
//const int MAXN = 1e12 + 5;

signed main () {
	int n; std::cin >> n;
	std::vector<std::pair<int, int>> factor;

	/*
	while (n%2 == 0) {
		if (factor.empty()) factor.push_back({2, 0});
		factor[0].second++;
		n = n / 2;
	}

	for (int i = 3; i * i <= n; i = i + 2) {
		while (n % i == 0) {
			if (factor.empty()) factor.push_back({i, 0});
			if (factor.back().first == i) factor.back().second += 1;
			else factor.push_back({i, 1}); 
			n /= i;
		}
	}

	for (int i = 2; i * i <= n; i++) {
		if (n%i == 0) {
			int cnt = 0;
			while (n % i == 0) {
				cnt++;
				n /= i;
			}
			factor.push_back({i, cnt});
		}
	}

	if (n > 1) {
		factor.push_back({n, 1});
	}

	int cnt = 1;
	for (int i = 0; i < factor.size(); i++) {
		cnt *= (factor[i].second + 1);
	}

	int ans = 0, idx;
	for (int i = 0; i < factor.size(); i++) {
		//std::cout << factor[i].first << " " << factor[i].second << '\n';
		int get = factor[i].second;
		int tmp = (cnt / (get + 1)) * (get + 2);
		if (tmp > ans) {
			idx = factor[i].first;
			ans = tmp;
		}
	}

	std::cout << idx;
	return 0;
}
*/

/*
jadi initnya itu kita harus nyari range berapa aja B yang terperangkap dinatara A paling awal dan A palign akhir

misal dalam case yang dalam gambar 

BB A B AAAA B AA BBB

berarti B yang terperangkap di antara A paling awal dan A palign akhir adalah

B B

dan kira cuma total hanya perlu ngehapus K - 1 indeks yang udah di shirnk ini

dan sebisa mungkin yang dihapus adalah k - 1 range terkecil dari B
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<utility>

int main () {
	int n, k; std::cin >> n >> k;
	std::string s; std::cin >> s;

	std::vector<int> sum;

	bool flip = false, startB = false;
	int start, end, firstA = -1, endA = 0;

	if (s[0] == 'B') flip = true;

	for (int i = 0; i < n; i++) {
		if (s[i] == 'A') {
			if (firstA == -1) firstA = i;
			endA = i + 1;
			if (flip && startB) {
				end = i - 1;
				sum.push_back(end - start + 1);
				flip = false;
			}
			else {
				startB = true;
				start = i + 1;
			}
		}
		if (s[i] == 'B' && startB) {
			if (!flip) {
				start = i;
				flip = true;
			}
		}
	}

	std::sort(sum.begin(), sum.end(), std::greater<int>());

	int ans = 0;
	int comp = sum.size();
	for (int i = 0; i < std::min(k - 1, comp); i++) {
		ans += sum[i];
	}

	if (firstA == -1) firstA = 0;
	std::cout << ans + firstA + (n - endA);
	return 0;
}
*/

/*
kalau 4
4 C 2 = 4 * 3 / 2 = 6

1 2 3 4
1 - 2 3 - 4
1 - 3 2 - 4

1 2 3 4 5 6 7 8
8C2 = 8 * 7 / 2 = 28
*/
/*
#include<iostream>

#define int long long 

signed main () {
	int n; std::cin >> n;
	if (n&1) {
		std::cout << 0;
		return 0;
	}
	n /= 2;
	int dp[n + 1];
	dp[0] = dp[1] = 1;

	for (int i = 1; i <= n; i++) {
		dp[i] = 0;
		for (int j = 0; j < i; j++) {
			dp[i] += dp[j] * dp[i - j - 1];
		}
	}

	std::cout << dp[n];
	return 0;
}
*/

/*
N -> N / 2 + N / 3 + N /4, 
berarti bisa jadi  (6N + 4N + 3N) / 12 -> 13N / 12 
karena pembagian di c++ bersifat rounding maka cuma butuh cek apakah bilangan itu habis dibagi 12

misal kalau habis bagi 2 atau 3 aja -> 18

antara 18, atau 18 / 2 + 18 / 3 + 18 / 4 = 9 + 6 + 4 = 19

6, 6 / 2 + 6 / 3 + 6 / 4 = 3 + 2 + 1 = 6

13, 13 / 2 + 13 / 3 + 13 / 4 = 6 + 4 + 3 = 13
*/

/*
#include<stdio.h>

static const short dp[1005] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 13, 14, 15, 17, 17, 19, 19, 21, 22, 23, 23, 27, 27, 27, 28, 30, 30, 32, 32, 35, 36, 36, 36, 41, 41, 41, 41, 44, 44, 46, 46, 48, 49, 49, 49, 57, 57, 57, 57, 57, 57, 60, 60, 63, 63, 63, 63, 68, 68, 68, 69, 74, 74, 76, 76, 76, 76, 76, 76, 87, 87, 87, 87, 87, 87, 87, 87, 92, 93, 93, 93, 98, 98, 98, 98, 101, 101, 104, 104, 104, 104, 104, 104, 119, 119, 119, 120, 120, 120, 120, 120, 120, 120, 120, 120, 129, 129, 129, 129, 134, 134, 134, 134, 134, 134, 134, 134, 144, 144, 144, 144, 144, 144, 147, 147, 155, 155, 155, 155, 160, 160, 160, 161, 161, 161, 161, 161, 161, 161, 161, 161, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 193, 193, 197, 197, 197, 197, 197, 197, 207, 207, 207, 207, 207, 207, 207, 207, 212, 212, 212, 212, 221, 221, 221, 221, 221, 221, 221, 221, 221, 222, 222, 222, 250, 250, 250, 250, 250, 250, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 276, 276, 276, 276, 276, 276, 276, 276, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 304, 304, 304, 305, 305, 305, 305, 305, 305, 305, 305, 305, 314, 314, 314, 314, 327, 327, 327, 327, 327, 327, 327, 327, 337, 337, 337, 337, 337, 337, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 341, 391, 391, 391, 391, 391, 391, 391, 391, 391, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 392, 405, 405, 405, 405, 419, 419, 419, 419, 419, 419, 419, 419, 419, 419, 419, 419, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 439, 447, 447, 447, 447, 447, 447, 447, 447, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 469, 473, 473, 473, 473, 473, 473, 524, 524, 524, 524, 524, 524, 524, 524, 524, 524, 524, 524, 533, 533, 533, 533, 533, 533, 533, 533, 533, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 641, 641, 641, 641, 641, 641, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 668, 668, 668, 668, 668, 668, 668, 668, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 689, 709, 709, 709, 709, 709, 709, 709, 709, 709, 709, 709, 709, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 723, 724, 724, 724, 724, 724, 724, 724, 724, 724, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 826, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 830, 851, 851, 851, 851, 851, 851, 851, 851, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 892, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 943, 994, 994, 994, 994, 994, 994, 994, 994, 994, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 995, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1009, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1123, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1257, 1258, 1258, 1258, 1258, 1258, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1279, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1350, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 1370, 
};

inline int read() {
	int val = 0;
	char c = getchar_unlocked();

	while (c < '0' ||c > '9') {
		c = getchar_unlocked();
	}

	while (c >= '0' && c <= '9') {
		val = (val << 3) + (val << 1) + (c - '0');
		c = getchar_unlocked();
	}
	return val;
}

inline void write(int val) {
	if (val == 0) {
		putchar_unlocked('0');
		return;
	}
	char buf[10];
	int idx = 0;
	while (val > 0) {
		buf[idx++] = (val%10) + '0';
		val /= 10;
	}
	while (idx > 0) {
		putchar_unlocked(buf[--idx]);
	}
}

int main () {
	int n = read();
	write(dp[n]);
}
*/

/*

*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

#define int long long

const int MAXN = 505;
bool a[MAXN][MAXN];
int dp[MAXN][MAXN];

signed main () {
	std::memset(a, false, sizeof(false));
	std::memset(dp, 0, sizeof(dp));

	int x, y, n; std::cin >> x >> y >> n;
	for (int i = 1; i <= n; i++) {
		int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;
		for (int j = x1; j <= x2;  j++) {
			for (int k = y1; k <= y2; k++) {
				a[j][k] = true;
			}
		}
	}
	
	for (int i = x; i >= 0; i--) {
		for (int j = 1; j <= y; j++) {
			if (!a[i][j]) {
				if (a[i + 1][j] == 0) {
					dp[i][j] = dp[i + 1][j];
				}
				else {
					int add1 = j - 1;
					while (add1 > 0 && a[i + 1][add1] == 1) add1--;

					int add2 = j + 1;
					while (add2 <= y && a[i + 1][add2] == 1) add2++;

					dp[i][j] = dp[i + 1][add1] + dp[i + 1][add2] + 1;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= y; i++) {
		ans = std::max(ans, dp[0][i]);
	}
	std::cout << ans;
	return 0;
}
*/

/*
berarti sama aja kayak satu 1 dimensi tapi ada 1 block dan 3 block 
1 blok aja 
f(n) = f(n - 1)

3 blok aja 
g(n) = g(n - 3) + 1

gabungan

g(n - 3) = f(n - 1) + g(n - 6)

berarti bisa disimpulin
f(n) = f(n - 1) + f(n - 3)

n = 0 -> 1
n = 1 -> 1
n = 2 -> 1
n = 3 -> 2
n = 4 -> 3
*/

/*
#include<iostream>

#define int long long

const int MOD = 1e6, MAXN = 1005;
int dp[MAXN];

void precomp() {
	dp[0] = dp[1] = dp[2] = 1;
	for (int i = 3; i < MAXN; i++) {
		dp[i] = (dp[i - 1] + dp[i - 3])%MOD;
	}
}

signed main () {
	precomp();

	int n; std::cin >> n;
	std::cout << dp[n] % MOD;
	return 0;
}
*/

/*

*/

/*
#include<iostream>
#include<deque>
#include<cstring>
#include<algorithm>

#define int long long

std::deque<int> a;

signed main () {
	int q; std::cin >> q;
	bool reverse = false;
	while (q--) {
		std::string s; std::cin >> s;
		if (s == "add") {
			int x, y; std::cin >>x >> y;
			
			for (int i = 1; i <= y; i++) {
				if (!reverse) a.push_back(x);
				else a.push_front(x);
			}
			
			std::cout << a.size() << '\n';
		}
		if (s == "del") {
			int x; std::cin >> x;
			
			int ans;
			if (!reverse) ans = a.front();
			else ans = a.back();
			std::cout << ans << '\n';

			for (int i = 1; i <= x; i++) {
				if (!reverse) a.pop_front();
				else a.pop_back();
			}
		}
		if (s == "rev") {
			reverse = !reverse;
		}
	}
	return 0;
}
*/

/*
#include<iostream>
#include<stack>
#include<cstring>

#define int long long

std::stack<int> a;

signed main () {
	int q; std::cin >> q;
	int add = 0;
	while (q--) {
		std::string s; std::cin >> s;
		if (s == "add") {
			int x, y; std::cin >> x >> y;
			for (int i = 1; i <= y; i++) {
				a.push(x - add);
			}
			std::cout << a.size() << '\n';
		}
		if (s == "del") {
			int y; std::cin >> y;
			std::cout << a.top() + add << '\n';
			for (int i = 1; i <= y; i++) {
				a.pop();
			}
		}
		if (s == "adx") {
			int d; std::cin >> d;
			add += d;
		}
		if (s == "dex") {
			int d; std::cin >> d;
			add -= d;
		}
	}
	return 0;
}
*/

/*
#include<iostream>
#include<stack>

#define int long long 

const int MAXN = 1e5 + 5;
int n, h[MAXN];

signed main () {
	std::cin >> n;

	for (int i = 1; i <= n; i++) std::cin >> h[i];

	std::stack<int> st;
	int maks = 0;

	for (int i = 1; i <= n;  i++) {
		while (!st.empty() && h[st.top()] <= h[i]) {
			st.pop();
		}

		if (st.empty()) {
			maks += i;
		} else {
			maks += (i - st.top());
		}

		st.push(i);
	}

	std::cout << maks;
	return 0;
}
*/

/*
#include<iostream>
#include<map>
#include<cstring>

std::map<std::string, std::string> a;

int main () {
	int n, q; std::cin >> n >> q;

	for (int i = 1; i<= n; i++) {
		std::string name; std::cin >> name;
		std::string no; std::cin >> no;
		a[name] = no;
	}
	
	while (q--) {
		std::string que; std::cin >> que;
		auto find = a.find(que);
		if (find != a.end()) 
			std::cout << find->second;
		else 
			std::cout << "NIHIL";
		std::cout << '\n';
	}
	return 0;
}
*/

/*
#include<iostream>
#include<vector>
#include<cstring>

const int MAXN = 1e5 + 5; 
bool vis[MAXN];
std::vector<std::vector<int>> adj(MAXN);
int ans = 0;

void search(int idx) {
	vis[idx] = true;
	for (auto c : adj[idx]) {
		if (!vis[c]) search(c);
	}
}

int main () {
	std::memset(vis, false, sizeof(false));

	int n, m; std::cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			search(i);
			//std::cout << i << " ";
			ans++;
		}
	}

	std::cout << ans;
	return 0;
}
*/
// the code are just talking about the covered area, so it can be an overlappin g area
/*
#include<iostream>
#include<vector>
#include<cstring>

const int MAXN = 505;
char a[MAXN][MAXN];
bool vis[MAXN][MAXN];
int areaK = 0, areaB = 0, c, r;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void travel (bool cond, int x, int y) {
	if (x > 0 && x <= r && y > 0 && y <= c) {
		if (!vis[x][y] && a[x][y] != '#') {
			vis[x][y] = true;

			if (cond) areaK++;
			else areaB++;

			for (int i = 0; i < 4; i++) {
				travel(cond, x + dx[i], y + dy[i]);
			}
		}
	}
}

int main () {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::memset(vis, false, sizeof(vis));

	std::cin >> c >> r;
	int xK, yK, xB, yB;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			char ch; std::cin >> ch;
			a[i][j] = ch;
			if (ch == 'K') {
				xK = i; 
				yK = j;
			}
			if (ch == 'B') {
				xB = i;
				yB = j;
			}
		}
	}

	travel(true, xK, yK);
	std::memset(vis, false, sizeof(vis));
	travel(false, xB, yB);

	//std::cout << areaK << ' ' << areaB << '\n';

	if (areaB > areaK) {
		std::cout << "B " << areaB - areaK;
	}
	else if (areaK > areaB) {
		std::cout << "K " << areaK - areaB; 
	}
	else {
		std::cout << "SERI";
	}
	return 0;
}
*/

/*
just check wheter the relative distance between two circle are <= r1 + r2 (there's intersection) or > r1 + r2 (no intersection)
*/

/*
#include<iostream>

#define int long long

signed main () {
	int x1, y1, r1; std::cin >> x1 >> y1 >> r1;
	int x2, y2, r2; std::cin >> x2 >> y2 >> r2;

	int del_x = (x1 - x2);
	int del_y = (y1 - y2);
	int del = (del_x * del_x) + (del_y * del_y);

	int sum = r1 + r2;
	sum *= sum;
	int diff = r1 -r2;
	diff *= diff;

	if (del >= diff && del <= sum) {
		std::cout << "bersentuhan";
	}
	else {
		std::cout << "tidak bersentuhan";
	}
	return 0;
}
*/

/*
test case 1 :

kalo -> archeo, parahi
parahi -> meryc
meryc -> dino, cali, cormo
dino -> hippi, equu

equu, dino meryc parahi, kalo

test case 2 :
bota -> koro, veedro
metal -> wargrey
grey -> metal, skull
agu -> grey, mera
koro -> agu

wargrey -> metal -> grey -> agu

test case 3:
mander -> melon
melon -> chari
bulba -> ivy
ivy -> venu
suir -> wrtor
wartor -> blasto

bulba 
chari -> melon -> mander
*/

/*
#include<iostream>
#include<map>
#include<vector>
#include<cstring>

std::map<std::string, std::vector<std::string>> tree;
std::vector<std::string> path;
std::string src1, src2;

bool search(std::string idx1, std::string idx2) {
	path.push_back(idx1);

	if (idx1 == idx2) return true;

	for (auto i : tree[idx1]) {
		if (search(i, idx2)) {
			return true;
		}
	}

	path.pop_back();
	return false;
}

int main () {
	int n, m; std::cin >> n >> m;
	while (m--) {
		std::string data1, data2; std::cin >> data1 >> data2;
		tree[data1].push_back(data2);
		//tree[data2].push_back(data1);
	}

	std::cin >> src1 >> src2;

	if (search(src1, src2)) {
		for (auto i : path) {
			std::cout << i << '\n';
		}
		return 0;
	}
	path.clear();
	if (search(src2, src1)) {
		for (auto i : path) {
			std::cout << i << '\n';
		}
		return 0;
	}

	std::cout << "TIDAK MUNGKIN";
	return 0;
}
*/

/*
karena ini materi nya bfs jadi kemungkinan gini

54123

karena k = 3, berarti nyoba semua kemungkinanya

54123 -> 14523, 52143, 54321
terus dari masing masing itu di coba lagi sampai dia nyampe ke ururtan nya
*/

/*
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>

int n, k, ans = -1;;
std::vector<int> a, trgt;

void bfs() {

	std::queue<std::vector<int>> q;
	std::map<std::vector<int>, int> dist;

	q.push(a);
	dist[a] = 0;

	while (!q.empty()) {
		std::vector<int> curr = q.front();
		q.pop();

		int curr_dist = dist[curr];

		if (curr == trgt) {
			ans = curr_dist;
			return;
		}

		for (int i = 0; i <= n - k; ++i) {
			std::vector<int> nxt = curr;

			std::reverse(nxt.begin() + i, nxt.begin() + i + k);

			if (dist.find(nxt) == dist.end()) {
				dist[nxt] = curr_dist + 1;
				q.push(nxt);
			}
		}
	}

	return;
}

int main () {
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		a.push_back(x);
	}
	std::cin >> k;

	trgt = a;
	std::sort(trgt.begin(), trgt.end());

	bfs();
	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

std::string a[6] = {"OSN", "ONS", "NOS", "NSO", "SON", "SNO"};
std::string inp;
int n;

int count (std::string trgt) {
	int cnt = 0;
	
	int idx = 0;
	for (int i = 0; i < n; i++) {
		if (inp[i] == trgt[idx]) {
			cnt++;
			idx++;
			idx = idx%3;
		}
	}

	return cnt;
}

int main () {

	std::cin >> inp;
	n = inp.size();

	int maks = 0;
	for (int i = 0; i < 6; i++) {
		maks = std::max(maks, count(a[i]));
	}

	if (maks < 3) std::cout << -1;
	else std::cout << maks;
	return 0;
}
*/

/*
#include<iostream>
#define int long long

signed main () {
	int b, c, d; std::cin >> b >> c >> d;

	int sum = 0;
	if (c - d == 0) {
		if (b > d) {
			sum = b - d;
		}
	}
	else {
		for (int i = 1; i * i <= (c - d); i++) {
			if (i <= b) {
				if ((c - d) % i == 0) {
					if (c % i == d) {
						sum++;
					} 
					if (((c - d) / i != i) && (c % ((c - d) / i)) == d && ((c - d) / i) <= b) {
						sum++;
					}
				}
			}
		}
	}

	std::cout << sum;
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#define int long long

const int MAXN = 1e5 + 5;
int n, m, a[MAXN];

int count (int mi) {
	int res = 0;

	for (int i = 0; i < n; i++) {
		res += std::max(0ll, a[i] - mi);
	}

	return res;
}

signed main () {
	std::cin >> n >> m;

	int sum = 0, maks = 0;
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		a[i] = x;
		sum += x;
		maks = std::max(maks, x);
	}

	if (m > sum) {
		std::cout << -1;
		return 0;
	}
	
	int l = 0, r = maks, ans;
	while (l <= r) {
		int mi = l + ((r - l) / 2);
		int cnt = count(mi);
		
		if (cnt >= m) {
			ans = mi; 
			l = mi + 1;
		}
		else 
			r = mi - 1;
	}

	std::cout << ans;
	return 0;
}
*/

/*
atas kiri = -1, +2
atas kanan = +1, +2
kiri atas = -2, +1
kiri bawah = -2, -1
kanan atas = +2, +1
kanan kiri = +2, -1
bawah kanan = +1, -2
bawah kiri = -1, -2
*/

/*
#include<iostream>
#include<utility>
#include<cstring>
#include<vector>

int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int vis[505][505], n, m;

void dfs (int x, int y, int s) {
	if (x > 0 && x <= n && y > 0 && y <= m && s >= 0) {
		if (s > vis[x][y]) {
			vis[x][y] = s;

			for (int i = 0; i < 8; i++) {
				dfs(x + dx[i], y + dy[i], s - 1);
			}
		}
	}
}

void solve() {
	std::memset(vis, -1, sizeof(vis));

	int k, s, i, j; std::cin >> n >> m >> k >> s >> i >> j;

	std::vector<std::pair<int, int>> a(k);
	for (int in = 0; in < k; in++) {
		int x, y; std::cin >> x >> y;
		a[in] = {x, y};
	}

	for (int in = 0; in < k; in++) {
		dfs(a[in].first, a[in].second, s);
	}

	if (vis[i][j] != -1) {
		std::cout << "TRUE\n";
	}
	else {
		std::cout << "FALSE\n";
	}
}

int main () {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int t; std::cin >> t;
	while (t--) solve();

	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<utility>
#include<string>

const int MAXN = 1e6 + 5;
std::pair<int, std::string> a[MAXN];

int main () {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int n, s, p; std::cin >> n >> s >> p;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i].first;
	}
	for (int i = 1; i <= p; i++) {
		std::string s; std::cin >> s;
		int x; std::cin >> x;
		a[x].second = s;
	}

	for (int i = 1; i <= (n - p); i++) {
		int x, y; std::cin >> x >> y;

		a[y].first += a[x].first;
		a[y].second = a[x].second;
	}

	std::sort(a + 1, a + n + 1, [](const std::pair<int, std::string>& x, std::pair<int, std::string>& y) {
		return x.first > y.first;
	});

	std::cout << a[1].second << '\n' << a[1].first;
	return 0;
}
*/

/*
karena yang diminta itu inggal operasi join dan find, berarti tinggal template disjoint set
*/

/*
#include<iostream>
#include<vector>

int n, q;
std::vector<int> p;

void prebuild (int sz) {
	p.resize(sz);

	for (int i = 0; i < sz; i++) {
		p[i] = i;
	}
}

int find (int i) {
	if (p[i] == i) {
		return i;
	}

	return p[i] = find(p[i]);
}

void join (int i, int j) {
	int id = find(i);
	int jd = find(j);

	if (id != jd) {
		p[id] = jd;
	}
}

bool check (int i, int j) {
	return find(i) == find(j);
}

void solve() {
	int comp, a, b; std::cin >> comp >> a >> b;

	if (comp == 1) {
		join(a, b);
	}
	else {
		if (check(a, b)) {
			std::cout << "Y\n";
		}
		else std::cout << "T\n";
	}
}

int main () {
	std::cin >> n >> q;

	prebuild(n + 5);

	while (q--) solve();
	return 0;
}

*/

/*
#include<iostream>

int main () {
	int n,m ;std::cin >> n >> m;
	int a[n + 5];
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	int ans = 0;
	while (m--) {
		int x; std::cin >> x;
		ans += a[x];
	}
	std::cout <<  ans;
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>

const int MAXN = 105;
bool vis[MAXN];
int w[MAXN];

int main () {
	std::memset(vis, false, sizeof(vis));

	int x, n; std::cin >> x >> n;
	for (int i = 1; i <= n; i++) std::cin >> w[i];
	int q; std::cin >> q;
	int ans = x;
	while (q--) {
		int p; std::cin >> p;
		if (!vis[p]) {
			vis[p] = true;
			ans += w[p];
		} else {
			vis[p] = false;
			ans -= w[p];
		}
		std::cout << ans << '\n';
	}
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>

#define int long long
const int MAXN = 2e5 + 5;

int pref[MAXN], n, m, a[MAXN];

signed main () {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		pref[i] = pref[i - 1] + a[i];
	}

	while (m--) {
		int x; std::cin >> x;
		int idx = std::lower_bound(pref + 1, pref + n + 1, x) - pref;
		std::cout << idx << "  " << x - pref[idx - 1] << '\n';
	}
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>

int pref[26];
std::string s[20];

int main () {
	int n, k; std::cin >> n >> k;
	for (int i = 0; i < n; i++) {
		std::cin >> s[i];
	}

	int maks = 0;
	for (int i = 0; i < (1 << n); i++) {
		std::memset(pref, 0, sizeof(pref));

		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1) {
				for (int x = 0; x < s[j].size(); x++) {
					pref[s[j][x] - 'a']++;
				}
			}
		}

		int cnt = 0;
		for (int j = 0; j < 26; j++) {
			if (pref[j] == k) cnt++;
		}

		maks = std::max(maks, cnt);
	}
	

	std::cout << maks;
	return 0;
}
*/

/*
#include<iostream>
#include<set>

int main () {
	int q; std::cin >> q;
	std::multiset<int> a;
	while (q--) {
		int stat; std::cin >> stat;
		if (stat == 1) {
			int x; std::cin >> x;
			a.insert(x);
		}
		if (stat == 2) {
			int x, c; std::cin >> x >> c;
			while (c > 0) {
				auto idx = a.find(x);
				if (idx == a.end()) break;
				a.erase(idx);
				c--;
			}
		}
		if (stat == 3) {
			std::cout << *a.rbegin() - *a.begin() << '\n';
		}
	}
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>
#define int long long
const int MAXN = 2e5;

int a[MAXN], n, k;
bool vis[MAXN];

bool ans () {
	int p = n - 1, tmp;
	for (int i = 0; i < k; i++) {
		if (vis[p]) return true;
		if (!(1 <= a[p] && a[p] <= n)) return false;
		vis[p] = true;
		
		tmp = (p - a[p])%n;
		if (tmp < 0) tmp += n;
		p = tmp;
	}
	return true;
}

void solve() {
	std::cin >> n >> k;
	for (int i = 0; i < n ; i++) std::cin >> a[i];
	std::cout << (ans() ? "Yes" : "No") << '\n';
	std::memset(vis, false, sizeof(vis)); 
}

signed main () {
	int t; std::cin >> t;
	while (t--) solve();
	return 0;
}
*/

/*
#include<iostream>
#define int long long

const int MAXN = 3e5 + 5;
int a[MAXN];

void solve() {
	int n; std::cin >> n;
	int odd = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		if(a[i] & 1) odd++;
	}
	if (odd && odd < n) {
		std::cout << "-1\n";
		return;
	}

	std::cout << "31\n";
	for (int i = 29; i >= 0; i--) {
		std::cout << (1ll << i) << " ";
		a[1] = abs(a[1] - (1ll << i));
	}
	std::cout << a[1] << '\n';
}

signed main () {
	int t; std::cin >> t;
	while (t--)solve();
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long 

signed main () {
	int q; std::cin >> q;
	std::vector<int> a;
	while (q--) {
		int stat; std::cin >> stat;
		if (stat == 1) {
			int x; std::cin >> x;
			a.push_back(x);
			std::push_heap(a.begin(), a.end());
		}
		if (stat == 2) {
			std::cout << a.front() << '\n';
		}
		if (stat == 3) {
			std::pop_heap(a.begin(), a.end());
			a.pop_back();
		}
	}
	return 0;
}
*/

/*
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

const int MAXN = 305;
std::vector<int> p;
std::vector<std::pair<int, std::pair<int, int>>> cell;
bool vis[MAXN][MAXN];
int n, m, tot;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int find(int v) {
	if (v == p[v]) 
		return v;
	return p[v] = find(p[v]);
}

bool u_set(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		p[y] = x;
		return true;
	}
	return false;
}

int ans() {
	int curr = 0;
	int maks = 0;

	int i = 0;
	while (i < tot) {
		int j = i;
		while (j < tot && cell[j].first == cell[i].first) {
			int x = cell[j].second.first;
			int y = cell[j].second.second;

			vis[x][y] = true;
			curr++;

			int u = x * m + y;

			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx >= 0 && nx < n && ny >= 0 && ny < m && vis[nx][ny]) {
					int v = nx * m + ny;
					if (u_set(u, v)) curr--;
				}
			}
			j++;
		}
		maks = std::max(maks, curr);
		i = j;
	}
	return maks;
}

int main (){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::memset(vis, false, sizeof(vis));

	std::cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int val; std::cin >> val;
			cell.push_back({val, {i, j}});
		}
	}

	std::sort(cell.begin(), cell.end(), std::greater<std::pair<int, std::pair<int, int>>>());

	tot = n * m;
	p.resize(tot);
	for (int i = 0; i < tot; i++) p[i] = i;

	std::cout << ans() << "\n";
	return 0;
}
*/

/*
1 6 8 3 10 2
sorted : 1 2 3 6 8 10
case xi = 2
karena posisinya 2 berarti data maksumal nya itu 7
berarti pilihannya antara ngehapus sebelum 2 atau ngehapus lebih dari 7 
berarti ada 3 pilihan yaitu gatau :(
*/

/*
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define ll long long 

const int MAXN = 1e5 + 5;
std::pair<int, int> e[MAXN];
std::priority_queue<std::pair<int, int>> pq;
int n, p, q, ans[MAXN];

signed main () {
	std::cin >> n >> p >> q;

	for (int i = 1; i <= n; i++) {
		std::cin >> e[i].first;
		e[i].second = i;
	}

	std::sort(e + 1, e + n + 1);

	int idx = 1;
	for (int i = 1; i <= n; i++) {
		while (e[idx].first - e[i].first <= p && idx <= n) {
			idx++;
		}
		idx--;

		pq.push(std::make_pair(idx - i + 1, idx));
		while (pq.top().second < i) {
			pq.pop();
		}
		ans[e[i].second] = pq.top().first;
	}

	while (q--) {
		int x; std::cin >> x;
		std::cout << ans[x] << '\n';
	}
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

const int INF = 1e9;

std::vector<std::vector<std::pair<int, int>>> adj;
int n, m, p, q;

std::vector<int> dijkstra(int src) {
	//int v = adj.size();
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

	std::vector<int> dist(n + 1, INF);

	dist[src] = 0;
	pq.emplace(0, src);

	while (!pq.empty()) {
		auto top = pq.top();
		pq.pop();

		int d = top.first;
		int u = top.second;

		if (d > dist[u]) 
			continue;

		for (auto &p : adj[u]) {
			int v = p.first;
			int w = p.second;

			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
	}
	return dist;
}

int main () {
	std::cin >> n >> m >> p >> q;
	adj.resize(n + 1);	
	
	for (int i = 0; i < m; i++) {
		int u, v, w; std::cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	std::vector<int> res = dijkstra(p);

	std::cout << res[q];
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long

const int INF = 1e9;

std::vector<std::vector<std::pair<int, int>>> adj;
int n, m, p, q;

std::vector<int> dijkstra (int src) {
	std::vector<int> dist(n + 1, INF);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

	dist[src] = 0;
	pq.emplace(0, src);

	while (!pq.empty()) {
		auto top = pq.top();
		pq.pop();

		int d = top.first;
		int u = top.second;

		if (d > dist[u]) {
			continue;
		}

		for (auto &p : adj[u]) {
			int v = p.first;
			int w = p.second;

			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
	}

	return dist;
}

signed main () {
	std::cin >> n >> m >> p >> q;
	adj.resize(n + 1);

	for (int i = 0; i < m; i++) {
		int u, v, w; std::cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	std::vector<int> res = dijkstra(p);

	std::cout << res[q];
	return 0;
}
*/

/*
#include<iostream>
#include<vector>

const int INF = 1e9;

std::vector<int> bellmanford(int n, std::vector<std::vector<int>>& adj) {
	std::vector<int> dist(n, INF);
	dist[0] = 0;

	for (int i = 0; i < n - 1; i++) {
		for (auto& e : adj) {
			int u = e[0];
			int v = e[1];
			int w = e[2];

			if (dist[u] != INF && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
			}
		}
	}

	for (const auto& e : adj) {
		int u = e[0];
		int v = e[1];
		int w = e[2];

		if (dist[u] != INF && dist[u] + w < dist[v]) {
			return {};
		}
	} 

	return dist;
}

void solve () {
	int n, m; std::cin >> n >> m;
	std::vector<std::vector<int>> adj;

	for (int i = 0; i < m; i++) {
		int u, v, w; std::cin >> u >> v >> w;
		adj.push_back({u, v, w});
		//adj[v].push_back({u, w});
	}

	std::vector<int> ans = bellmanford(n, adj);

	if (ans.empty()) {
		std::cout << "Pak Dengklek tidak mau pulang\n";
	} else if (ans[n - 1] == INF) {
		std::cout << "Tidak ada jalan\n";
	}
	else if (ans[n - 1] > 0) {
		std::cout << ans[n - 1] << '\n';
	}
	else {
		std::cout << (ans[n - 1]) << '\n';
	}
}

signed main () {
	int t; std::cin >> t;
	while (t--) solve();
	return 0;
}
*/

/*
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

const int INF = 1e8, MAXN = 505;

int n, m, q, dist[MAXN][MAXN];
std::vector<std::vector<int>> adj;

void floydwarshall() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (dist[i][k] != INF && dist[k][j] != INF) {
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}
}

void convert() {
	for (auto& i : adj) {
		int u = i[0];
		int v = i[1];
		int w = i[2];

		dist[u][v] = std::min(dist[u][v], w);
		dist[v][u] = std::min(dist[v][u], w);
	}
}

int main () {
	std::memset(dist, INF, sizeof(dist));

	std::cin >> n >> m >> q;
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}

	for (int i = 0; i < m; i++) {
		int u, v, w; std::cin >> u >> v >> w;
		//adj.push_back({u, v, w});
		//adj[v].push_back({v, u, w});
		dist[u][v] = std::min(dist[u][v], w);
		dist[v][u] = std::min(dist[v][u], w);
	}

	//convert();
	floydwarshall();

	int init = -1, ans = 0;
	while (q--) {
		int p; std::cin >> p;
		if (init != -1) ans += dist[init][p];
		init = p;
	}
	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>

const int MAXN = 105, INF = 1e8;
int grid[MAXN][MAXN], n, ans = 0;

int min (int key[], bool mst[], int sz) {
	int mini = INF, min_idx;

	for (int v = 0; v < sz; v++) {
		if (mst[v] == false && key[v] < mini) {
			mini = key[v];
			min_idx = v;
		}
	}

	return min_idx;
}

void prim() {
	int key[n], par[n];
	bool mst[n];

	for (int i = 0; i < n; i++) {
		key[i] = INF;
		mst[i] = false;
	}

	key[0] = 0;
	par[0] = -1;

	for (int cnt = 0; cnt < n - 1; cnt++) {
		int u = min(key, mst, n);
		if (u == -1) break;
		mst[u] = true;

		for (int v = 0; v < n; v++) {
			if (grid[u][v] && mst[v] == false && grid[u][v] < key[v]) {
				par[v] = u;
				key[v] = grid[u][v];-
			}
		}
	}

	for (int i = 1; i < n; i++) {
		ans += grid[par[i]][i];
	}
}

int main () {
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> grid[i][j];
		}
	}

	prim();

	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#define int long long

const int MAXN = 1e5 + 5;
int b[MAXN], g[MAXN], idx = 0;
std::vector<std::vector<int>> adj, tmp;
bool vis[MAXN];

void search (int id) {
	if (!vis[id]) {
		vis[id] = true;
		tmp[idx].push_back(b[id]);
		for (int i : adj[id]) {
			search(i);
		}
	}
}

signed main () {
	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

	int n, m, k; std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	for (int i = 1; i <= m; i++) std::cin >> g[i];
	
	std::sort(g + 1, g + m + 1);

	adj.resize(n + 1);
	for (int i = 0; i < k; i++) {
		int p, q; std::cin >> p >> q;
		adj[p].push_back(q);
		adj[q].push_back(p);
	}

	std::memset(vis, false, sizeof(vis));

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			tmp.push_back(std::vector<int>());
			search(i);
			idx++;
		}
	}

	int ans = 0;
	for (auto i : tmp) {
		if (!i.empty()) {
			int sz = i.size(), target;
			std::sort(i.begin(), i.end());
			if (sz&1) {
				target = i[sz / 2];
			} else {
				target = (i[sz / 2] + i[sz / 2 - 1]) / 2;
			}
			int id_ans = std::lower_bound(g + 1, g + m + 1, target) - g;
			if (id_ans > m) {
				id_ans = m;
			}
			
			int pref[sz + 1];
			std::memset(pref, 0, sizeof(pref));
			for (int idx = 0; idx < sz; idx++) {
				pref[idx + 1] = pref[idx] + i[idx];
			}

			int ans_comp = 1e18;

			int lb = std::max(1LL, id_ans - 2);
			int rb = std::min(m, id_ans + 2);
			for (int idx = lb; idx <= rb; idx++) {
				int y = g[idx];

				int find = std::upper_bound(i.begin(), i.end(), y) - i.begin();

				int left = find * y - pref[find];

				int right = (pref[sz] - pref[find]) - (sz - find) * y;

				int tot = left + right;

				ans_comp = std::min(ans_comp, tot);
			}

			ans += ans_comp;
		}
	}

	std::cout << ans;
	return 0;
}
*/

/*
case pertama :
ada 1 x 4
1 2 3 4

2 warna dengan 1 * 3
n = 4
m = 2
k = 3
banyak warna

2 2 2 (2 + 2 * 2)

dp[i], i <= k -> m
dp[i], i > k -> dp[i] = m * (dp[i - m] + 1) 

1 2 3 4 5
2 2 2 6 6

A A A B A
A A A A B
A A A B B
A B A A A
B B A A A
B A A A A

B B B A B
B B B B A
B B B A A
B A B B B
A B B B B
A A B B B

A A A A A
B B B B B 

total : 10

4
4 - 3 = 1
(2 * 2 - 1) * 2

AAA A | B
BBB B | A

A | B AAA
A | B BBB

AAAA -> dua kali berarti dikurang 1 sebelum dia dikali dua setelahnya

2 2 2 
misal kalau lima 

AAA, A | B, A | B -> AAAAA, AAABA, AAABB, AAAAB
BBB, A | B, A | B -> BBBBB, BBBAA, BBBAB, BBBBA, BBBBB

dibalik

A | B, A | B, AAA -> intersection nya cuma ketika semua nya itu sama
A | B, A | B, BBB -> intersection nya ketika semua itu sama

berarti rumusnya 

dp[i] = m, i <= k
dp[i] = (dp[i] - 1) * 2, i > k
*/

/*
#include<iostream>
#include<cstring>
#define int long long

const int MAXN = 1e6 + 5, MOD = 1e9 + 7;
int dp[MAXN], n, m, k;

int power_mod(int a, int b) {
	int res = 1;
	while (b > 0) {
		if (b&1) res = (res * a)%MOD;
		a = (a * a)%MOD;
		b /= 2;
	}
	return res;
}

signed main () {
	std::cin >> n >> m >> k;
	
	for (int i = 0; i <= n; i++) {
		if (i < k) dp[i] = 0;
		else if (i == k) dp[i] = m;
		else if (i < 2 * k){
			dp[i] = ((dp[i - 1]* m)%MOD + (m * (m - 1))%MOD)%MOD;
		}
		else {
			dp[i] = ((dp[i - 1] * m)%MOD + ((dp[i - k] - dp[i - k -1] + MOD)%MOD * (m - 1))%MOD)%MOD;
		}
	}

	std::cout << dp[n];
	return 0;
}
*/

/*
#include<iostream>
#include<cstring>

const int MAXN = 1e6 + 5, MOD = 1e9 + 7;
int dp[MAXN], n, m, k;

int pow_mod (int a, int b) {
	int res = 1;
	while (b > 0) {
		if (b&1) res = (res * a)%MOD;
		a = (a * a)%MOD;
		b >>= 1;
	}
	return res;
}

signed main () {
	std::cin >> n >> m >> k;

	dp[0] = 1;
	for (int i = 1;i <= n; i++) {
		if (i < k) dp[i] = (m * dp[i - 1])%MOD;
		else if (i == k) dp[i] = ((dp[k - 1] * m)%MOD - m + MOD)%MOD;
		else {
			dp[i] = (((dp[i - 1]) * m)%MOD - ((m - 1) * dp[i - k])%MOD + MOD)%MOD;
		}
	}

	std::cout << (pow_mod(m, n) - dp[n] + MOD)%MOD;
	return 0;
}
*/

/*
berarti pake suffix atau prefi tetapi di sort berdasarkan dari terbesar (descending order)

5 6 3 4 2 7 4 5 -> 36
7 5 5 7 3 4 3 6 5 3 -> 48

selisih nya 12, berarti harus pindahin minimal x > n / 2;

3 3 3 4 5 5 5 6 7 7
7 7 6 5 5 5 4 3 3 3 -> 

kalau misal jadi prefix 

gausah pake suffi, pake freq array
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long

const int INF = 1e17;

signed main () {
	int n, m; std::cin >> n >> m;

	int cntA = 0;
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		cntA += x;
	}

	int cntB = 0;
	std::vector<int> b;
	for (int i = 0; i < m; i++) {
		int x; std::cin >> x;
		cntB += x;
		b.push_back(x);
	}

	std:sort(b.rbegin(), b.rend());

	if (cntA * m > cntB * n) {
		std::cout << 0;
		return 0;
	}

	int ans = -1;
	int cnt = 0;

	for (int i = 0; i < b.size() - 1; i++) {
		cnt += b[i];
		int idx = i + 1;

		if (b[i] != b[i + 1]) {
			if (((cntA + cnt) * (m - idx)) > ((cntB - cnt) * (n + idx))) {
				ans = cnt;
				break;
			}
		}
	}

	std::cout << ans;
	return 0;
}
*/

/*
5 1 3
9 8 7 6

5 1 3 9 -> 18 * 3 = 54

8 7 6 -> 21 * 4 = 84

5 1 3 9 8 -> 26 * 2 = 52

7 6 -> 13 * 5 = 65

5 1 3 9 8 7 -> 33 * 1 = 33

6 ->  6 * 6 = 36

5 1 3
3 3 3 3 3 
*/

/*
6 3 2

tinggi pada hari ke i

3 5 7 9 11 13 15

  6 9 10 10 16 18

3 6 9 16 18 20 22

18
20

*/

/*
#include<iostream>
#include<algorithm>
#define int long long

const int MAXN = 1e5 + 5;
int a[MAXN];

signed main () {
	int n, m ,k; std::cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	std::sort(a, a + n);

	int h = m, i = 0, ans = 0;
	while (i < n) {
		h += k;
		while (i < n && a[i] <= h) {
			i++;
		}
		if (i >= n) break;
		h = a[i];
		ans++;
	}

	std::cout << ans;
	return 0;
}
*/

/*
10 37 11

41 61 72 78 83 98 107 140 152 183

6
*/

/*
2 5 3
7 5 6 3

1 -> 2 * 5 = 10
2 - 3 -> 3 * 3 = 9

19


4 8 2
1 3
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#define int long long

const int MAXN = 1e5 + 5, INF = 1e17;
int a[MAXN], b[MAXN], n, m, k, ans = 0, mini;
bool vis[MAXN];
std::vector<std::vector<int>> adj;
std::vector<int> min_cycle, tmp;

void dfs(int i) {
	if (!vis[i]) {
		mini = std::min(mini, a[i]);
		vis[i] = true;
		for (auto j : adj[i]) {
			dfs(j);
		}
	}
}

signed main () {
	std::cin >> n >> m >> k;
	adj.resize(n + 1);
	std::memset(vis, false, sizeof(vis));

	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 0; i < m; i++) std::cin >> b[i];
	for (int i = 0; i < k; i++) {
		int u, v; std::cin >> u >> v;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}

	std::sort(b, b + m);

	int cnt_cycle = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			mini = INF;
			cnt_cycle++;
			dfs(i);
			tmp.push_back(mini);
		}
	}

	std::sort(tmp.rbegin(), tmp.rend());
	for (int i = 0; i < tmp.size(); i++){
		ans += (tmp[i] * b[i]);
	}

	if (cnt_cycle > m) {
		std::cout << -1;
	}
	else {
		std::cout << ans;
	}
}

/*
8 4 5

7 5 3 10 2 8 6 9
25 10 35 30

1 - 2 -> 5
3 - 4 - 5 - 6 -> 2 
7 -> 6
8 -> 9

9 6 5 2
90 150 150 70

10 25 30 35
*/

/*
4 3 5

0 4 6 10 
135 72 7 127

dari posisi x itu coba ke kiri 

nah dari bensin yang diabisin waktu pergi ke kiri dipake juga buat ngehabisin ke posisi kanan

misal dalam case yg pertama
1 2 3 4
mulai dari 5

5 full ke kanan berarti ke 8 -> 6 -> dapet 7
4 baru full kenan berarti -> 5 - 1 = 4, 72 -> 4 + 2 = 6 -> 7
baru ditambah jadi nya 79
3 baru ke kanan berarti -> 5 - 2 = 3, 72
pake lower bound buat ngeposisin indeks X 

l sama r set ke indeks X



*/

/*
#include<iostream>
#include<vector>
#include<algorithm>
#define int long long

signed main () {
	int n, k, x; std::cin >> n >> k >> x;
	std::vector<int> a(n + 1); 
	std::vector<int> b(n + 1); 
	std::vector<int> pref(n + 1, 0);
	
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) {
		std::cin >> b[i];
		pref[i] = pref[i - 1] + b[i];
	}

	//int idx = std::lower_bound(a.begin(), a.end(), x) - a.begin();
	
	int maks = 0;
	int r = 1;
	for (int l = 1; l <= n; l++) {
		while (r <= n) {
			int dist = 0;
			
			if (x < a[l]) {
				dist = a[r] - x;
			} else if (x > a[r]) {
				dist = x - a[l];
			} else {
				dist = (a[r] - a[l]) + std::min(x - a[l], a[r] - x);
			}

			if (dist > k) break;

			int tot = pref[r] - pref[l - 1];
			maks = std::max(maks, tot);

			r++;
		}

		if (r < l) r = l;
	}

	std::cout << maks;
	return 0;
}
*/

/*
2 5 3 5 6 5 3 5 2

2 2 3 3 5 5 5 5 6

2 2 3 3 5 5 5 5 6

2 2 2 2 5 5 5 5 5


2 2 3 3 5 5 5 5 6
2 2 2 3 3 3 3 3 3

2 2 3 3 5 5 5 5 6
1 2 3 4 

2 2 3 3 5 5 5 5 6
2 2 2 2 3 3 3 3 4

0 - 2, 1 - 3, 3 - 5, 4 - 6
2		2		4		1
*/

/*
#include<iostream>
#include<algorithm>
#include<queue>

const int MAXN = 2e5 + 5;
int a[MAXN], dp[MAXN];
std::deque<int> dq;

int main () {
	int n, m, k; std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) std::cin >> a[i];

	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		while (!dq.empty() && a[dq.front()] < a[i] - k) {
			dq.pop_front();
		}
		dq.push_back(i);
		if (dq.size() >= m) {
			if (dq.size() <= m && dp[i - m] == -1) dp[i] = -1;
			else if (dp[i - m] == -1) dp[i] = dp[i - 1];
			else dp[i] = dp[i - m] + 1;
		} else {
			dp[i] = -1;
		}
	}

	std::cout << dp[n];
	return 0;
}
*/

/*
m = 3

3 
*/

/*
//#include<queue>
#include<algorithm>
#include<cstdio>
//#define int long long
typedef long long ll;
//const int MAXN = 2e5 + 5;
int ans = 0;

inline ll read() {
	int s = 0, w = 1;
	char ch = getchar_unlocked();
	while (ch > '9' || ch < '0') {
		if (ch == '-') w = -1;
		ch = getchar_unlocked();
	}
	while (ch <= '9' && ch >= '0') {
		s = (s << 1) + (s << 3) + (ch ^ 48);
		ch = getchar_unlocked();
	}
	return s * w;
}

signed main () {
	int n = (int)read();
	ll m = read();
	//int a[n + 5];	
	//for (int i = 1; i <= n; i++) a[i] = read();
	
	ll pref[n + 1]; pref[0] = 0;
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1] + read();
	}

	//std::deque<int> dq_min;
	//std::deque<int> dq_max;
	int dq_min[n + 1], head_min = 0, tail_min = 0;
	int dq_max[n + 1], head_max = 0, tail_max = 0;


	int l = 0;
	for (int r = 1; r <= n; r++) {

		while(tail_max > head_max && pref[dq_max[tail_max - 1]] <= pref[r]) {
			tail_max--;
		}
		//dq_max.push_back(r);
		dq_max[tail_max++] = r;

		while (tail_min > head_min && pref[dq_min[tail_min - 1]] >= pref[r]) {
			tail_min--;
		}
		//dq_min.push_back(r);
		dq_min[tail_min++] = r;

		while (l < r && (pref[dq_max[head_max]] - pref[l] > m || pref[dq_min[head_min]] - pref[l] < 0)) {
			l++;

			if (head_max < tail_max && dq_max[head_max] < l) {
				//dq_max.pop_front();
				head_max++;
			}
			if (head_min < tail_min && dq_min[head_min] < l) {
				//dq_min.pop_front();
				head_min++;
			}
		}

		//ans = std::max(ans, r - l);
		ans = (ans > r - l ? ans : r - l);
	}

	std::printf("%d", ans);
	return 0;
}
*/

/*
16 2 11 6 1 12

1 2 6 11 12 16
*/

/*
#include<stdio.h>
#include<algorithm>
//#define int long long

const int INF = 1e9;

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

signed main () {
	int n = read();
	int m =  2 * n;
	int a[m + 5];
	for (int i = 1; i <= m; i++) a[i] = read();
	
	std::sort(a + 1, a + m + 1);

	int ans = INF;
	for (int i = 1; i <= n + 1; i++) {
		//ans = std::min(ans, a[i + n - 1] - a[i]);
		if (a[i + n - 1] - a[i] < ans) {
			ans = a[i + n - 1] - a[i];
		}
	}
	printf("%d", ans);
	return 0;
}
*/

/*
160 -> 1 1
180 -> 2 4
180 -> 2 4
180 -> 2 4
220 -> 5 6
220 -> 5 6
*/

/*
7 3

3 1 -2 2 -1 2 -3

3 4 2 4 3 5 2

pref[r] - pref[l] >= 0, r - l paling besar


*/

/*
160
*/

/*
160 180 180 180 220 220
1   2   3   4   5   6
*/

/*
#include<stdio.h>
#include<algorithm>

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

int main () {
	int n = read(); 
	int a[n], b[n];
	for (int i = 0; i < n; i++) {
		a[i] = read();
	}
	
	std::sort(b, b + n);

	for (int i = 0; i < n; i++) {
		printf("%d %d\n", std::lower_bound(b, b + n, a[i]) - b + 1, std::upper_bound(b, b + n, a[i]) - b);
	}

	return 0;
}
*/

/*
#include<stdio.h>

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

int main () {
	int n = read();
	int maks1 = 0, maks2 = 0;
	for (int i = 0; i < n; i++) {
		int x = read();
		if (x > maks2) {
			maks2 = maks1;
			maks1 = x;
		}
		else if (x > maks2) maks2 = x;
	}

	printf("%d\n", maks1 * maks2);
	return 0;
}
*/

/*
#include<stdio.h>
#include<algorithm>

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

inline void writestring(const char* s) {
	while (*s) {
		putchar_unlocked(*s++);
	}
}

signed main () {
	int n = read();
	int a[n];
	for (int i = 0; i < n; i++) a[i] = read();
	
	std::sort(a, a + n);

	if (n > 1 && a[1] <= a[0]) {
		writestring("NO\n");
		return 0;
	}
	for (int i = 2; i < n; i++) {
		if (a[i] < a[i - 1] + 2) {
			writestring("NO\n");
			return 0;
		}
	}

	writestring("YES\n");
	return 0;
}
*/

/*
5 1

x
x
x
x
x

2 7 3
1 2 3

x x x x x x x
x x x x x x x

0 2 3
1 0 0

(2, 1), (1, 2), (1, 3)

1 0 0
0 2 3

(1, 1) (2, 2), (2, 3)

2 + 3 + 1 = 6

x x x x x x x x x x x
x x x x x x x x x x x 
x x x x x x x x x x x 
x x x x x x x x x x x 

1 1 3 7 11

1
1 3 7 11

1 1 3 3 7 7 11

1
1 3
  3 7
    7 11
*/

/*
#include<stdio.h>
#include<algorithm>
#define int long long

const int MAXN = 2e5 + 5;
int a[MAXN], h, w, n;

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

bool check (int x) {
	int c = 1;
	for (int i = 2; i <= n; i++) {
		int dist = a[i] - a[i - 1];
		int cnt = std::max(0ll, x - dist);
		c += cnt;
	}
	return (c <= h);
}

signed main () {
	h = read();
	w = read();
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	std::sort(a + 1, a + n + 1);

	int l = 1, r = h + w, mid = 0, cnt = -1;
	while (l <= r) {
		mid = l + (r - l) / 2;
		if (check(mid)) {
			cnt = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	printf("%d", cnt);
	return 0;
}
*/

/*
676
1 2 3

3 5 6
6 7 6

3 2
2 0 -> 3 + 1 = 4
1 0 -> 6
0 0 -> 6

16

4 3 1
2 4 5




*/

/*
#include<stdio.h>

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

inline void write (int x) {
    if (x == 0) {
        putchar_unlocked('0');
        return;
    }
    if (x < 0) {
        putchar_unlocked('-');
        x = -x;
    }
    char buf[12];
    int top = 0;
    while (x > 0) {
        buf[top++] = (x % 10) + '0';
        x /= 10;
    }
    while (top--) {
        putchar_unlocked(buf[top]);
    }
}

int main () {
	int n = read(), x = read();
	int idx1, idx2, tmp;

	for (int i = 1; i <= n; i++) {
		if (i == x) {
			tmp = read();
			continue;
		}
		idx1 = read();
		if (idx1 - idx2 < 0) {
			write(0);
			return 0;
		}
		idx2 = idx1;
	}

	write(1);
	return 0;
}
*/

/*
%k

+ a[i]

(x + j * a[i])%k == y % k
x + j * a[i] = y + k * i


*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long

const int MAXN = 2e5 + 5, INF = 1e17;
int w[MAXN], l[MAXN];
//bool vis[MAXN];

signed main () {
	std::memset(l, INF, sizeof(l));
	int n, m ; std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> w[i] >> l[i];
	}
	//std::memset(vis, false, sizeof(vis));
	int ans = 0;
	while (m--) {
		int x, y; std::cin >> x >> y;
		w[x] += y;
	}
	for (int i = 1; i <= n; i++) {
		if (w[i] > l[i]) ans++;
	}

	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<vector>
#include<algorithm>
#define int long long 
std::vector<int> t, s, c;
std::vector<std::pair<int, int>> tmp;

signed main () {
	int n, m; std::cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		t.push_back(x);
	}

	while (m--) {
		int x, y; std::cin >> x >> y;
		tmp.push_back({x, y});
	}

	std::sort(tmp.begin(), tmp.end());

	int x = tmp[0].first, y = tmp[0].second;
	for (int i = 1; i < (int)tmp.size(); i++) {
		if (tmp[i].first == tmp[i - 1].first) {
			y = std::min(y, tmp[i].second);
		}
		else {
			s.push_back(x);
			c.push_back(y);
			x = tmp[i].first;
			y = tmp[i].second;
		}
	}
	s.push_back(x);
	c.push_back(y);

	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto idx = std::lower_bound(s.begin(), s.end(), t[i]);
		if (idx == s.end() || *idx != t[i]) {
			std::cout << -1;
			return 0;
		}
		ans += c[idx - s.begin()];
	}

	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

char c[505][505];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main () {
	int n; std::cin >> n;
	int id_sx, id_sy, id_gx, id_gy;
	for (int i = 0; i < n; i++) {
		std::string s; std::cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == 'S') {
				id_sx = i;
				id_sy = j;
			}
			if (s[j] == 'G') {
				id_gx = i;
				id_gy = j;
			}
			c[i][j] = s[j];
		}
	}

	std::queue<std::pair<int, int>> dq;
	dq.push({id_sx, id_sy});
	
	int dist[505][505];
	bool vis[505][505];
	std::memset(dist, 0, sizeof(dist));
	std::memset(vis, false, sizeof(vis));

	vis[id_sx][id_sy] = true;
	while (!dq.empty()) {
		auto id = dq.front();
		dq.pop();

		int x = id.first;
		int y = id.second;

		if (x == id_gx && y == id_gy) break;

		for (int d = 0; d < 4; d++) {
			int nxt_x = x + dx[d];
			int nxt_y = y + dy[d];
			if (nxt_x >= 0 && nxt_x < n && nxt_y >= 0 && nxt_y < n && c[nxt_x][nxt_y] != '#' && !vis[nxt_x][nxt_y]) {
				vis[nxt_x][nxt_y] = true;
				dq.push({nxt_x, nxt_y});
				dist[nxt_x][nxt_y] = dist[x][y] + 1;
			}
		}

	}

	std::cout << dist[id_gx][id_gy] + 1;
	return 0;
}
*/

/*
ada n 
n + 1 / 2, 

kalau bilangan ganjil berarti n / 2 + 1, kalau bilagan genap berarti n / 2

3
7 2
1 2 1 2 1 2 1 
1 -> 1 + 3 + 5 + 7 / 4 = 4
2 +> 2 + 4 + 6 = 12 / 4 = 3
2 1 2 1 2 1 2

2 2
1 2

2 1 
1 1 

1 1 1 2 2 2 3

1 2 3 4 5 6 7
1 2 2 3 1 2 1

1 2 3 4 5 6
1 1 1 2 2 2 
1 2 1 1 2 1



1 2 3 4 5 6 7

*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>

void solve() {
   	int n, k; std::cin >> n >> k;
	//std::map<int, std::vector<int>> cl;
	std::map<int, int> mp;
   	for (int i = 0; i < n; i++) {
		int co; std::cin >> co;
		mp[co]++;
	}

	int odd_co = -1;
	int odd_cnt = 0;

	for (auto const& [col, cnt] : mp) {
		if (cnt&1) {
			odd_cnt++;
			odd_co = col;
		}
	}

	if ((!(n&1) && odd_cnt > 0) || ((n&1) && odd_cnt != 1)) {
		std::cout << "NO\n";
		return;
	} 

	int res[n];

	if (n&1) {
		int m = n / 2;
		res[m] = odd_co;
		mp[odd_co]--;
	}

	std::vector<int> tmp;
	for (auto const& [col, cnt]: mp) {
		for (int i = 0; i < cnt; i++) {
			tmp.push_back(col);
		}
	}

	int l = 0, r = n - 1;
	int tmp_idx = 0;

	while (l < r) {
		res[l] = tmp[tmp_idx];
		res[r] = tmp[tmp_idx + 1];

		tmp_idx += 2;
		l++;
		r--;
	}

	std::cout << "YES\n";
	for (auto i : res) {
		std::cout << i << " ";
	}

	std::cout << '\n';
}

signed main () {
   	std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

   	int t = 1;
   	std::cin >> t;
   	while (t--) solve();
   	return 0;
}
*/

/*
1
15 3
2 2 1 1 2 2 3 1 1 3 1 3 3 2 3

1 1 1 1 1 2 2 2 2 2 3 3 3 3 3
1 -> 5
2- > 5
3 -> 5

3 1 2 3 1 2 2 3 1 1 2 3 2 1 3
1 -> tengah, 1 tinggal 4, terus posisi genap
2 dan 3 ->  ambil 2 masing masing buat posisi genap
2 -> 3
3 -> 3
122 m 112

1
15 6
3 4 1 3 2 5 4 3 1 5 2 6 1 1 2

1 1 1 1 2 2 2 3 3 3 4 4 5 5 6
1 -> 4
2 -> 3
3 ->  3
4 -> 2
5 ->  2
6 ->  1
233 m 223

25, m = 13

1, 2, 3, 4, 5 ->  5
1 -> 3
2 -> 3
3 -> 3
4 -> 3
5 -> 3

1 2 3 4 5 6 7 8 9 10 11 12 13
1 2 2 3 4 4 x 1 1 2   3  3  4
1 -> 1 + 12 + 13 = 26 / 3

m - 6
m + 6

-1, -2, -3, -4, -5, -6


1, 2, 3, 4, 5, 6

m, m + 1, m + 2

6 -> -2, -4

1, 5 -> -6

4 -> -1, -3

2, 3 -> -5

-1, -2, -3

1, 2, 3
-3 -> 1, 2
-1, -2 -> 3

jadi ini untuk case ganjil, jadi yang genap tidka akan ditaruh di tengahm kemudian posisikan sehingga bilangan ganjil yang tersisa berjumlah 3
misal 
ada 
1 sebanyak 5
2 sebanyak 5
3 sebanyak 5
4 sebanyak 5
5 sebanyak 5 

nah jadi taruh salah satu ke tengah 

5 1 1 4 2 3 3 6 2 2 3 4 1 1 5
ambil 6 buat ditaruh di tengah 6, terus yang genapa mirroring
tinggal 2, 3
*/
/*
#include<iostream>
#include<map>
#include<cstring>

int main () {
	std::string s; std::cin >> s;
	int n = s.size();
	std::map<char, int> cnt;
	for (int i = 0; i < n; i++) {
		cnt[s[i]]++;
	}

	char odd;
	int odd_cnt = 0;
	for (auto const& [x, y] : cnt) {
		if (y&1) {
			odd = x;
			odd_cnt++;
		}
	}

	if ((!(n&1) && (odd_cnt > 0)) || ((n&1) && (odd_cnt != 1))) {
		std::cout << "NO SOLUTION\n";
		return 0;
	}

	char c[n];
	int l = 0, r = n - 1;
	auto idx = cnt.begin();

	if (n&1) {
		int m = n / 2;
		c[m] = odd;
		cnt[odd]--;
	}

	while (l <= r) {
		while (idx != cnt.end() && idx->second == 0) {
			idx++;
		}
		if (idx == cnt.end()) break;

		c[l] = idx->first;
		c[r] = idx->first;
		idx->second -= 2;

		l++; r--;
	}

	for (int i = 0; i < n; i++) {
		std::cout << c[i];
	}
	return 0;
}
*/
/*
#include<stdio.h>
#include<queue>
#include<vector>
#include<string>

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}

void writestr(const std::string& s) {
	for (char c : s) {
		putchar_unlocked(c);
	}
}

int main () {
	int n = read();

	std::queue<std::string> q;
	q.push("0");
	q.push("1");

	for (int i = 2; i <= n; i++) {
		std::vector<std::string> curr;

		while (!q.empty()) {
			curr.push_back(q.front());
			q.pop();
		}

		for (int j = 0; j < curr.size(); j++) {
			q.push("0" + curr[j]);
		}

		for (int j = curr.size() - 1; j >= 0; j--) {
			q.push("1" + curr[j]);
		}
	}

	while (!q.empty()) {
		//std::cout << q.front() << '\n';
		writestr(q.front() + '\n');
		q.pop();
	}
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long 

const int MOD = 1e9 + 7;

signed main () {
	int n; std::cin >> n;
	int dp[n + 1][n + 1];
	std::memset(dp, 0, sizeof(dp));
	
	dp[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c; std::cin >> c;
			dp[i][j] = (dp[i][j - 1] + dp[i - 1][j])%MOD;
			if (c == '*') dp[i][j] = 0;
		}
	}

	std::cout << dp[n][n];
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

const int MAXN = 1e6 + 5, INF = 1e8;
int dp[MAXN], a[MAXN];

int main () {
	std::memset(dp, INF, sizeof(dp));
	int n, x; std::cin >> n >> x;
	
	for (int i = 1; i <= x; i++) {
		dp[i] = INF;
	}
	
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		dp[a[i]] = 1;
	}

	dp[0] = 0;

	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= n; j++) {
			if (i - a[j] >= 0 && dp[i - a[j]] != INF) {
				dp[i] = std::min(dp[i], dp[i - a[j]] + 1);
			}
		}
	}

	if (dp[x] == INF) {
		std::cout << -1;
	}
	else {
		std::cout << dp[x];
	}
	return 0;
}
*/

/*
dp[0] = 0
dp[1] = 1
dp[2] = 2
dp[3] = 3
dp[4] = 4
dp[5] = 1
dp[6] = 2
dp[7] = 1
dp[8] = 2
dp[9] = 3
dp[10] = 2
dp[11] = 3
*/
/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long

const int MOD = 1e9 + 7, MAXN = 1e6 + 5;
int a[MAXN], dp[MAXN];

signed main () {
	int n, x; std::cin >> n >> x;
	std::memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		//dp[a[i]] = 1;
	}

	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= x; j++) {
			if (j - a[i] >= 0) {
				dp[j] = (dp[j] + dp[j - a[i]])%MOD;
			}
		}
	}

	std::cout << dp[x];
	return 0;
}
*/
/*
dp[2] = 1
dp[3] = 1
dp[4] = 1
dp[5] = 

5 -> 2 + 3, 5
*/

/*
#include<iostream>
#include<cstring>

const int MAXN = 1e6 + 5;
int dp[MAXN], maks = 0;

int find(int x) {
	if (x <= 0) return maks;
	
	int tmp = x%10;
	if (tmp > maks) {
		maks = tmp;
	}
	return find(x/10);
}

int main () {
	std::memset(dp, 0, sizeof(dp));
	int n; std::cin >> n;
	for (int i = 0; i < MAXN - 4; i++) {
		if (i < 10) dp[i] = 1;
		else {
			int idx = find(i);
			dp[i] = dp[i - idx] + 1;
		}
		maks = 0;
	}

	std::cout << dp[n];
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

const int MAXN = 1e5 + 5;
int h[MAXN], s[MAXN], dp[MAXN];

int main () {
	std::memset(dp, 0, sizeof(dp));
	int n, x; std::cin >> n >> x;
	for (int i = 0; i < n; i++) {
		std::cin >> h[i];
	}
	for (int i = 0; i < n; i++) {
		std::cin >> s[i];
	}
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = x; j >= h[i]; j--) {
			if (j - h[i] >= 0) {
				dp[j] = std::max(dp[j], dp[j - h[i]] + s[i]);
			}
		}
	}

	std::cout << dp[x];
	return 0;
}
*/

/*

*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long 

const int MAXN = 1e5 + 5, MOD = 1e9 + 7;
int x[MAXN], dp[MAXN][105];

signed main () {
	//std::memset(dp, -1, sizeof(dp));
	int n, m; std::cin >> n >> m;
	for (int i = 0; i < n; i++) {
		std::cin >> x[i];
	}

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			if (x[i] == 0) {
				for (int j = 1; j <= m; j++) {
					dp[i][j] = 1;
				}
			}
			else dp[i][x[i]] = 1;
		}
		else {
			if (x[i] == 0) {
				for (int j = 1; j <= m; j++) {
					dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1])%MOD; 
				}
			}
			else {
				dp[i][x[i]] = (dp[i - 1][x[i] - 1] + dp[i - 1][x[i]] + dp[i - 1][x[i] + 1])%MOD;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= m; i++) {
		ans = (ans + dp[n - 1][i])%MOD;
	}

	std::cout << ans;
	return 0;
}
*/

/*
n = 1, 2
n = 2, 8
n = 3, 
*/

/*
#include<stdio.h>
#define int long long

const int MAXN = 1e6 + 5, MOD = 1e9 + 7;
int dp[MAXN][2];

inline int read() {
   int s = 0, w = 1;
   char ch = getchar_unlocked();
   while (ch > '9' || ch < '0') {
	   if (ch == '-') w = -1;
	   ch = getchar_unlocked();
   }
   while (ch <= '9' && ch >= '0') {
	   s = (s << 1) + (s << 3) + (ch ^ 48);
	   ch = getchar_unlocked();
   }
   return s * w;
}
 
void write_int(int x) {
   if (x < 0) {
	   putchar_unlocked('0');
	   return;
   }
   if (x < 0) {
	   putchar_unlocked('-');
	   x = -x;
   }
   char buff[12];
   int idx = 0;
   while (x > 0) {
	   buff[idx++] = (x % 10) + '0';
	   x /= 10;
   }
   while (idx > 0) {
	   putchar_unlocked(buff[--idx]);
   }
}
 

void precomp() {
	dp[0][1] = dp[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		dp[i][1] = ((2 * dp[i - 1][1])%MOD + dp[i - 1][0])%MOD;
		dp[i][0] = (dp[i - 1][1] + (4 * dp[i - 1][0])%MOD)%MOD;
	}
}

void solve() {
	int n = read();
	int cnt = (dp[n - 1][1] + dp[n - 1][0])%MOD;
	write_int(cnt);
	putchar_unlocked('\n');
}

signed main () {
	precomp();

   int t = 1;
   t = read();
   while (t--) solve();
   return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>

const int MAXN = 5005;
int dp[MAXN][MAXN];

int min (int a, int b, int c) {
	if (a < b) {
		if (a < c) return a;
		else return c;
	}
	else {
		if (b < c) return b;
		else return c;
	} 
}

int main () {
	std::string s1, s2; std::cin >> s1 >> s2;
	int n = s1.size();
	int m = s2.size();
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0) {
				dp[i][j] = j;
			}
			else if (j == 0) {
				dp[i][j] = i;
			}
			else if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
			}
		}
	}

	std::cout << dp[n][m];
	return 0;
}
*/

/*

	  3 1 3 2 7 4 8 2
	6 0 0 0 0 0 0 0 0
	5 0 0 0 0 0 0 0 0
	1 0 * 1 1 1 1 1 1
	2 0 1 1 * 2 2 2 2
	3 1 1 2 2 2 2 2 2
	4 1 1 2 2 2 * 3 3
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

const int MAXN = 1e3 + 5;
int dp[MAXN][MAXN], a[MAXN], b[MAXN];

void print(int i, int j) {
	if (i == 0 || j == 0) return;
	if (a[i] == b[j]) {
		print(i - 1, j - 1);
		std::cout << a[i] << " ";
	} else if (dp[i - 1][j] > dp[i][j - 1]) {
		print(i - 1, j);
	} else {
		print(i, j - 1);
	}
}

int main () {
	std::memset(dp, 0, sizeof(dp));
	int n , m; std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= m; i++) std::cin >> b[i];

	std::vector<int> res;
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	std::cout << dp[n][m] << '\n';
	print(n, m);

	return 0;
}
*/

/*
3 5 

3 2

3 1

1 1 
*/

/*
#include<iostream>
#include<algorithm>

const int MAXN = 505, INF = 1e9;
int dp[MAXN][MAXN];

void precomp() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}
}

int main () {
	int a, b; std::cin >> a >> b;
	precomp();
	for (int i = 0; i <= a; i++) {
		for (int j = 0; j <= b; j++) {
			if (i == j) {
				dp[i][j] = 0;
			} else {
				for (int k = 1; k < j; k++) {
					dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
				}
				for (int k = 1; k < i; k++) {
					dp[i][j] = std::min(dp[i][j], dp[i - k][j] + dp[k][j] + 1);
				}
			}
		}
	}
	std::cout << dp[a][b];
	return 0; 
}
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>

const int MAXN = 3005;

int dx[2] = {0, 1};
int dy[2] = {1, 0};
bool vis[MAXN][MAXN];

int main () {
	std::memset(vis, false, sizeof(vis));
	int n; std::cin >> n;
	std::vector<std::string> grid(n);
	for (int i = 0; i < n; i++) std::cin >> grid[i];

	std::vector<std::pair<int, int>> curr;
	curr.push_back({0, 0});
	vis[0][0] = true;

	std::cout << grid[0][0];
	for (int st = 0; st < 2 * n - 2; st++) {
		std::vector<std::pair<int, int>> nxt;
		char min = 'Z' + 1;
		
		for (auto [ux, uy] : curr) {
			for (int i = 0; i < 2; i++) {
				int vx = ux + dx[i];
				int vy = uy + dy[i];

				if (vx < n && vy < n) {
					if (!vis[vx][vy]) {
						vis[vx][vy] = true;

						if (grid[vx][vy] < min) {
							min = grid[vx][vy];
							nxt.clear();
							nxt.push_back({vx, vy});
						} else if (grid[vx][vy] == min) {
							nxt.push_back({vx, vy});
						}
					}
				}
			}
		}
		std::cout << min;

		curr = std::move(nxt);
	}
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

const int MAXN = 1e5 + 5;
int a[MAXN];
bool dp[MAXN];

int main () {
	int n; std::cin >> n;

	int sum = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		sum += a[i];
	}
	std::memset(dp, false, sizeof(dp));

	dp[0]= true;
	for (int i = 0; i < n; i++) {
		for (int j = sum; j >= a[i]; j--) {
			if (dp[j - a[i]]) {
				dp[j] = true;
			}
		}
	}

	std::vector<int> res;
	for (int i = 1; i <= sum; i++) {
		if (dp[i]) {
			res.push_back(i);
		}
	}
	std::cout << res.size() << '\n';
	for (auto i : res) {
		std::cout << i << " ";
	}

	return 0;
}
*/

/*
#include<bits/stdc++.h>
using namespace std;

int main () {
	string s; cin >> s;
	int n = s.length();
	int maks = 1;
	int idx1 = 0, idx2 = 1;
	string ans = "";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= 1; j++) {
			int l = i;
			int r = i + j;
			while (l >= 0 && r < n && s[l] == s[r]) {
				int curr = r - l + 1;
				if (curr > maks) {
					maks = curr;
					idx1 = l;
					idx2 = curr;
				}
				l--;
				r++;
			}
		}
	}

	cout << s.substr(idx1, idx2);
}
*/

/*
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 5;
char pos[MAXN][MAXN];

int main () {
	string s; cin >> s;
	int n; cin >> n;

	/*
	line 1 pattern -> x * (n - 1) * 2, x >= 0
	line 2 pattern 
	general question  = x * 2 * (n - 1) - 2

	line 3 equation x * 2 * (n - 1) + 2
	
	1   7    13
	2 6 8 12 14
	3 5 9 11 15
	4   10   16

	increasing key x =  2 * n - 2
	1 + k * x, k >= 0
	2 + k * x, k >= 0
	
	1   4   7, 
	2 3 5 6 8

	1   5   9     13
	2 4 6 8 10 12 14
	3   7   11

	1   9
	2 8
	3 7
	4 6
	5

	2 + n - 2 + n - 2  = 2n - 2
	*/  

	/*
	int m = s.length();
	if (m == 1) {
		return s[0];
	}
	//cout << m  << '\n';
	string ans = "";
	for (int i = 1; i <= n; i++) {
		if (i > 1 && i < n) {
			int j, k;
			for (j = i, k = 2 * n - i; j <= m && k <= m; j += 2 *n - 2, k += 2 *n - 2) {
				//std::cout << s[j - 1] << " " << s[k - 1] << " ";
				ans += s[j - 1];
				ans += s[k - 1];
			}
			while (j <= m) {
				//cout << s[j -1];
				ans += s[j -1];
				j += 2 * n - 2;
			}
			while (k <= m) {
				ans += s[k - 1];
				//cout << s[k -1];
				k += 2 * n - 2;
			}

			//cout << '\n';
		} else {
			for (int j = i; j <= m; j += 2 * n - 2) {
				//std::cout << s[j - 1] << " ";
				ans += s[j - 1];
			}
			//cout << '\n';
		}
	}
	cout <<  ans;
	return 0;
}
*/

/*
#include<bits/stdc++.h>
using namespace std;

int main () {
	string s; cin >> s;
	long long ans = 0;
	int i = 0;
	int n = s.length();
	int sign = -1;

	while (i < n && s[i] == ' ') {
		i++;
	}

	if (i < n && s[i] == '+' || s[i] == '-') {
		if (s[i] == '-') sign = -1;
		i++;
	}

	while (i < n && s[i] >= '0' && s[i] <= '9') {
		ans = ans * 10 + (s[i] - '0');

		if (sign == 1 && ans > INT_MAX) {
			cout << INT_MAX;
			return 0;
		}
		if (sign == -1 && -ans < INT_MIN) {
			cout << INT_MIN;
			return 0;
		}
		i++;
	}

	cout << sign * ans;

	return 0;
}
*/

/*
#include<bits/stdc++.h>
using namespace std;

int main () {
	int x; cin >> x;
	string s = to_string(x);
	int l = 0, r = s.length() - 1;
	while (l <= r) {
		if (s[l] != s[r]) {
			cout << "NO";
			return 0;
		}
		l++;
		r--;
	}
	cout << "YES";

	return 0;
}
*/

/*

#include<bits/stdc++.h>
using namespace std;

int main () {
	string s, p; cin >> s >> p;
	int n = s.length(), m = p.length();
	bool dp[n + 1][m + 1];
	memset(dp, false, sizeof(dp));
	dp[0][0] = 1;

	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (p[j - 1] == '*') {
				dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
			}
			else {
				dp[i][j] = (i > 0) && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
			}
		}
	}

	cout << dp[n][m];
	return 0;
}
	*/

/*
#include<bits/stdc++.h>
using namespace std;

int main () {
	int n; cin >> n;
	int a[n];
	for (int i = 0; i < n; i++) cin >> a[i];

	int l = 0, r = n - 1, ans = 0;
	while (l < r) {
		int wi = r - l;
		int hi = min(a[l], a[r]);
		int area = wi * hi;
		ans = max(ans, area);
		if (height[l] < height[r]) l++;
		else r--;
	}
	return ans;
}
*/

/*
#include<iostream>
#include<cstring>

const int MAXN =1e6 + 5, MOD = 1e9 + 7;
int dp[MAXN];

int main () {
	std::memset(dp, 0, sizeof(dp));
	int n; std::cin >> n;
	for (int i = 1; i <= 6; i++) {
		dp[i] = 1;
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 1; j <= 6; j++) {
			if (i - j >= 0) {
				dp[i] = (dp[i] + dp[i - j])%MOD;
			}
		}
	}

	std::cout << dp[n];
}
*/

/*
#include<iostream>
#include<algorithm>
#define int long long

const int MAXN = 5005;
int dp[MAXN][MAXN];

signed main () {
	int n; std::cin >> n;
	int a[n], sum = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		sum += a[i];
	}

	for (int l = n - 1; l >= 0; l--) {
		for (int r = l; r < n; r++) {
			if (l == r) {
				dp[l][r] = a[l];
			}
			else {
				dp[l][r] = std::max(a[l] - dp[l + 1][r], a[r] - dp[l][r - 1]);
			}
		}
	}

	std::cout << (sum + dp[0][n - 1]) / 2;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long

const int MOD = 1e9 + 7, MAXN = 2e5 + 5;
int dp[MAXN];

signed main () {
	int n; std::cin >> n;
	int sum = (n * (n + 1)) / 2;
	int target = sum / 2;
	
	if (sum%2 == 1) {
		std::cout << 0;
		return 0;
	}

	dp[0] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = target; j >= i; j--) {
				dp[j] = (dp[j] + dp[j - i])%MOD;
		}
	}	

	std::cout << dp[target];
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>

int main () {
	int n, m, k; std::cin >> n >> m >> k;
	int a[n];
	for (int i = 0; i < n; i++) std::cin >> a[i];
	int b[m];
	for (int i = 0; i < m; i++) std::cin >> b[i];
	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto idx = std::lower_bound(b, b + m, a[i]);
		if (*idx >= a[i] - 5 && *idx <= a[i] + 5) ans++;
	}
	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long

const int MAXN = 1e5 + 5;
int grid[2][MAXN], pos[2][2], cost[2][MAXN];
char c[2][MAXN]; 

signed main () {
	int n; std::cin >> n;

	std::string s1, s2; std::cin >> s1 >> s2;

	for (int i = 0; i < n; i++) {
		c[0][i] = s1[i];
		c[1][i] = s2[i];
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> cost[i][j];
		}
	}

	int pos_a = -1, pos_b = -1;

	for (int i = 0; i < n; i++) {
		if (c[0][i] == 'A') pos_a = i + 1;
		if (c[1][i] == 'B') pos_b = i + 1;
	}

	for (int i = 0; i < n; i++) {
		if (c[1][n - i - 1] == 'A') pos_a = n + i + 1;
		if (c[0][n - i - 1] == 'B') pos_b = n + i + 1;
	}

	if (pos_a + pos_b > 2 *n) {
		std::cout << "-1\n";
		return 0;
	}

	if (pos_b < pos_a) {
		std::swap(pos_a, pos_b);
		for (int i = 0; i < n; i++) {
			if (c[0][i] != '.') c[0][i] = (c[0][i] == 'A' ? 'B' : 'A');
            if (c[1][i] != '.') c[1][i] = (c[1][i] == 'A' ? 'B' : 'A');		
		
			std::swap(c[0][i], c[1][i]);
			std::swap(cost[0][i], cost[1][i]);		
		}
	}

	grid[0][0] = cost[0][0];
	grid[1][0] = cost[1][0];

	for (int i = 1; i < pos_a; i++) {
		grid[0][i] = grid[0][i - 1] + cost[0][i];
		grid[1][i] = grid[1][i - 1] + cost[1][i];
	}

	for (int i = pos_a; i < n; i++) {
		if (i == pos_a) {
			grid[1][i] = grid[1][i - 1] + cost[1][i];
			grid[0][i] = grid[1][i] + cost[0][i];
		} else {
			grid[0][i] = std::min(grid[0][i - 1] + cost[0][i], grid[1][i - 1] + cost[1][i] + cost[0][i]);
			grid[1][i] = std::min(grid[1][i - 1] + cost[1][i], grid[0][i - 1] + cost[0][i] + cost[1][i]);
		}
	}

	int tot = 0;
	for (int i = 0; i < n; i++) {
		if (c[0][i] == 'A' || c[0][i] == 'B') tot += grid[0][i];
		if (c[1][i] == 'A' || c[1][i] == 'B') tot += grid[1][i];
	}

	std::cout << tot << '\n';
	return 0;
}
*/
/*
#include<iostream>
#include<algorithm>
#include<cstring>

const int MAXN = 1005;
char grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
int ans = 0, n, m;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

void search(int x, int y) {
	if (x >= 0 && x < n && y >= 0 && y < m) {
		if (grid[x][y] == '.') {
				if (!vis[x][y]) {
				vis[x][y] = true;
				for (int i = 0; i < 4; i++) {
					search(x + dx[i], y + dy[i]);
				}
			}
		}
	}
}

int main () {
	std::cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> grid[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!vis[i][j] && grid[i][j] == '.') {
				ans++;
				search(i, j);
			}
		}
	}

	std::cout << ans;
	return 0;
}
*/

/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>

const int MAXN = 1005;
char grid[MAXN][MAXN];
char move[MAXN][MAXN];
bool vis[MAXN][MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char dir[] = {'R', 'L', 'D', 'U'};

int main () {
	std::memset(vis, false, sizeof(vis));
	int n, m; std::cin >> n >> m;
	int xa, ya, xb, yb;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> grid[i][j];
			if (grid[i][j] == 'A') {
				xa = i;
				ya = j;
			}
			if (grid[i][j] == 'B') {
				xb = i;
				yb = j;
			}
		}
	}

	std::queue<std::pair<int, int>> dq;
	dq.push({xa, ya});
	vis[xa][ya] = true;
	bool found = false;

	while (!dq.empty()) {
		auto idx = dq.front();
		dq.pop();
		int x = idx.first;
		int y = idx.second;

		if (x == xb && y == yb) {
			found = true;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int vx = x + dx[i];
			int vy = y + dy[i];
			if (vx >= 0 && vx < n && vy >= 0 && vy < m && !vis[vx][vy] && grid[vx][vy] != '#') {
				vis[vx][vy] = true;
				move[vx][vy] = dir[i];
				dq.push({vx, vy});
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << move[i][j] << " ";
		}
		std::cout << '\n';
	}

	
	if (!found) {
		std::cout << "NO\n";
		return 0;
	}
	else std::cout << "YES\n";

	std::vector<char> res;
	int x = xb;
	int y = yb;
	while (x != xa && y != ya) {
		char note = move[x][y];
		res.push_back(note);
		if (note == 'R') {
			y--;
		}		
		if (note == 'U') {
			x++;
		}		
		if (note == 'L') {
			y++;
		}		
		if (note == 'D') {
			x--;
		}		
	}

	std::cout << res.size() << '\n';
	for (int i = res.size() - 1; i >= 0; i--) {
		std::cout << res[i];
	}
	
	return 0;
}

/*
5
12.5
3:7
-3.30
0.95
*/

