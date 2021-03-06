#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000;
char buf[kMaxN +  1];
int n, m, cnt;
bool dp[kMaxN * 2 - 1][2][2];

int Dfs() {
	int res = cnt ++;
	if (buf[m] == '?' || buf[m] == '0' || buf[m] == '1') {
		if (buf[m] == '?') 
			dp[res][0][1] = dp[res][1][0] = true;
		else
			dp[res][buf[m] - '0'][buf[m] - '0'] = true;
		++ m;
		return res;
	}
	++ m;
	int ls = Dfs();
	char p = buf[m ++];
	int rs = Dfs();
	++ m;
	for (int a = 0; a < 2; ++ a)
		for (int b = 0; b < 2; ++ b) if (dp[ls][a][b])
			for (int c = 0; c < 2; ++ c)
				for (int d = 0; d < 2; ++ d) if (dp[rs][c][d]) {
					int e, f;
					if (p == '&') e = a & c, f = b & d;
					else if (p == '|') e = a | c, f = b | d;
					else e = a ^ c, f = b ^ d;
					dp[res][e][f] = true;
				}
	return res;
}

int main() {
	scanf("%d%s", &n, buf);
	n = strlen(buf), m = 0;
	Dfs();
	if (dp[0][0][1] || dp[0][1][0]) printf("YES\n");
	else printf("NO\n");
	return 0;
}
