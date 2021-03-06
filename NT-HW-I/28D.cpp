#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kInf = 0x3f3f3f3f;
int n, v[kMaxN], c[kMaxN], l[kMaxN], r[kMaxN];
int f[kMaxN], p[kMaxN];
map<pair<int, int>, int> rec;
vector<int> sol;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d%d%d", &v[i], &c[i], &l[i], &r[i]);
		f[i] = -kInf, p[i] = -1;
	}
	int ans = -1;
	for (int i = 0; i < n; ++ i) {
		if (!l[i]) {
			f[i] = v[i];
			if (!r[i] && (ans == -1 || f[ans] < f[i])) ans = i;
		}
		else if (rec.count(make_pair(l[i], r[i] + c[i]))) {
			p[i] = rec[make_pair(l[i], r[i] + c[i])];
			f[i] = v[i] + f[p[i]];
			if (!r[i] && (ans == -1 || f[ans] < f[i])) ans = i;
		}
		if (!rec.count(make_pair(l[i] + c[i], r[i]))) rec[make_pair(l[i] + c[i], r[i])] = i;
		else {
			int &t = rec[make_pair(l[i] + c[i], r[i])];
			if (f[i] > f[t]) t = i;
		}
	}
	while (ans != -1) {
		sol.push_back(ans);
		ans = p[ans];
	}
	printf("%d\n", sol.size());
	for (int i = sol.size() - 1; i >= 0; -- i) {
		if (i < (int)(sol.size() - 1)) printf(" ");
		printf("%d", sol[i] + 1);
	}
	puts("");
	return 0;
}
