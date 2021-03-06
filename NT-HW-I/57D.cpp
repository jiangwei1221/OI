#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000, kMaxM = 1000;
char buf[1024];
int n, m, row[kMaxN], col[kMaxM];
long long sum, cnt;

void Solve(int *arr, int s) {
	int t = n + m - s;
	for (int i = 0; i < s; ++ i) if (arr[i] != -1) {
		sum += 4 * arr[i] * (t - arr[i] - 1);
		for (int j = i - 1; j >= 0; -- j)
			if (arr[j] != -1 && arr[j] > arr[j + 1])
				sum += 4 * arr[i] * (t - arr[j] - 1);
			else break;
		for (int j = i + 1; j < s; ++ j)
			if (arr[j] != -1 && arr[j] > arr[j - 1])
				sum += 4 * arr[i] * (t - arr[j] - 1);
			else break;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	memset(row, -1, sizeof(row));
	memset(col, -1, sizeof(col));
	for (int i = 0; i < n; ++ i) {
		scanf("%s", buf);
		for (int j = 0; j < m; ++ j)
			if (buf[j] == 'X') {
				row[i] = j;
				col[j] = i;
			}
			else {
				++ cnt;
				sum += n * j * (j + 1) / 2 + n * (m - j - 1) * (m - j) / 2;
				sum += m * i * (i + 1) / 2 + m * (n - i - 1) * (n - i) / 2;
			}
	}
	cnt *= cnt;
	for (int i = 0; i < n; ++ i) if (row[i] != -1) {
		sum -= n * row[i] * (row[i] + 1) / 2 + n * (m - row[i] - 1) * (m - row[i]) / 2;
		for (int j = 0; j < n; ++ j) if (i != j) {
			sum -= m * abs(i - j);
			if (row[j] != -1) sum += abs(i - j) + abs(row[i] - row[j]);
		}
	}
	Solve(row, n);
	Solve(col, m);
	printf("%.8lf\n", sum * 1.0 / cnt);
	return 0;
}
