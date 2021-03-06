#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 250000;
int n, s[kMaxN * 2 + 1], t[kMaxN * 2 + 1], o[kMaxN * 2 + 1];
int to[19][kMaxN * 2 + 1];

namespace st {
	const int kMaxM = kMaxN * 2;
	int dp[19][kMaxM + 1], m, r, log2[kMaxM + 1];

	void Init() {
		m = n * 2;
		log2[1] = 0;
		for (int i = 2; i <= m; ++ i) {
			log2[i] = log2[i - 1];
			if ((i & (i - 1)) == 0) ++ log2[i];
		}
		r = log2[m] + 1;
		for (int i = 1; i <= m; ++ i) dp[0][i] = i;
		for (int j = 1; j < r; ++ j)
			for (int i = 1; i <= m; ++ i) {
				dp[j][i] = dp[j - 1][i];
				if (i + (1 << (j - 1)) <= m && t[dp[j - 1][i + (1 << (j - 1))]] < t[dp[j][i]])
					dp[j][i] = dp[j - 1][i + (1 << (j - 1))];
			}
	}
	
	int Query(int l, int r) {
		int s = log2[r - l + 1];
		return (t[dp[s][l]] < t[dp[s][r - (1 << s) + 1]] ? dp[s][l] : dp[s][r - (1 << s) + 1]);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", &s[i]); 
		s[i] = min(s[i], n - 1);
		s[i + n] = s[i];
	}
	for (int i = 1; i <= n * 2; ++ i) t[i] = i - s[i];
	st::Init();
	for (int i = 1; i <= n * 2; ++ i) {
		int lb = i - s[i], rb = i;
		if (lb >= 1) o[i] = st::Query(lb, rb);
	}
	ll ans = 0;
	for (int i = 1; i <= n * 2; ++ i) to[0][i] = o[i];
	for (int j = 1; j < st::r; ++ j)
		for (int i = 1; i <= n * 2; ++ i)
			if (to[j - 1][i]) to[j][i] = to[j - 1][to[j - 1][i]];
	for (int i = 1; i <= n; ++ i) {
		int pos = i + n, req = i + 1;
		int add = 0;
		for (int j = st::r - 1; j >= 0; -- j)
			if (t[to[j][pos]] > req) {
				add |= 1 << j;
				pos = to[j][pos];
			}
		if (t[pos] > req) {
			++ add;
			pos = to[0][pos];
		}
		++ add;
		ans += add;
	}
	printf("%lld\n", ans);
	return 0;
}
