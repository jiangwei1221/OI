#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <ext\rope>

using namespace std;
using namespace __gnu_cxx;

const int kMaxK = 3000000, kMaxN = 5000;
char buf[kMaxK + 1];
int k, n, l[kMaxN], r[kMaxN];

crope Solve(int pos, int len) {
	if (pos == -1) {
		return crope(((string)buf).substr(0, len).c_str());
	}
	if (r[pos] + 1 >= len) {
		return Solve(pos - 1, len);
	}
	int lb = r[pos] + 1;
	int rb = min(len - 1, lb + (r[pos] - l[pos]));
	int tp = rb - lb + 1;
	crope res = Solve(pos - 1, len - tp);
	string dat = "";
	for (int i = l[pos] + 1; i <= r[pos] && tp; i += 2) {
		dat += res[i];
		-- tp;
	}
	for (int i = l[pos]; i <= r[pos] && tp; i += 2) {
		dat += res[i];
		-- tp;
	}
	res.insert(lb, dat.c_str());
	return res;
}

int main() {
	scanf("%s%d%d", buf, &k, &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &l[i], &r[i]);
		-- l[i], -- r[i];
	}
	puts(Solve(n - 1, k).c_str());
	return 0;
}
