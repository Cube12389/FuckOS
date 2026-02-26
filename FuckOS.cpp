#include <bits/stdc++.h>

using namespace std;

const int N = 256;

vector<unsigned int> file[100000];
unsigned int cnt[N][N];
set<uint8_t> s;
uint8_t vis[N];

void init();
void pushdown(unsigned int n);
void stop(unsigned int n);
void Run(unsigned int n, uint8_t m, unsigned int &x);
void run(int m);

void init() {
	memset(vis, 0, sizeof(vis));
	ifstream in("FuckFILE.fos");
	int n;
	in >> n;
	while (n--) {
		unsigned int m, k;
		in >> m >> k;
		while (k--) {
			int x;
			in >> x;
			file[m].push_back(x);
		}
	}
}

void pushdown(unsigned int n) {
	exit(1);
}

void stop(unsigned int n) {
	vis[n] = 2;
}

void Run(unsigned int n, uint8_t m, unsigned int &x) {
	
	uint8_t op = (n & 3221225472) >> 30;
	uint8_t mode = (n & 1056964608) >> 24; // 0~63
	uint8_t a = (n & 16711680) >> 16;
	uint8_t b = (n & 65280) >> 8;
	uint8_t c = n & 255;
	
	if (op == 0) {
		if (mode == 0) cnt[m][c] = cnt[m][a] + cnt[m][b];
		if (mode == 1) cnt[m][c] = cnt[m][a] - cnt[m][b];
		if (mode == 2) cnt[m][c] = cnt[m][a] * cnt[m][b];
		if (mode == 3) cnt[m][c] = cnt[m][a] / cnt[m][b];
		if (mode == 4) cnt[m][c] = cnt[m][a] % cnt[m][b];
		if (mode == 5) cnt[m][c] = cnt[m][a] >> cnt[m][b];
		if (mode == 6) cnt[m][c] = cnt[m][a] << cnt[m][b];
	} else if (op == 1) {
		if (mode == 0 and cnt[m][a] == 0) x = cnt[m][b];
		if (mode == 1 and cnt[m][a] != 0) x = cnt[m][b];
		if (mode == 2 and cnt[m][a] >= 0) x = cnt[m][b];
		if (mode == 3 and cnt[m][a] <= 0) x = cnt[m][b];
		if (mode == 4 and cnt[m][a] > 0) x = cnt[m][b];
		if (mode == 5 and cnt[m][a] < 0) x = cnt[m][b];
		if (mode == 6) x = cnt[m][b];
		if (mode == 7) ;
	} else if (op == 2) {
		if (mode == 0) cnt[m][a] = n & 65535;
		if (mode == 1) cnt[m][a] = m;
	} else if (op == 3) {
		if (mode == 0) cout << char(cnt[m][a]);
		if (mode == 1) {
			char ch;
			cin >> ch;
			cnt[m][a] = (unsigned int)ch;
		} if (mode == 2) pushdown(cnt[m][a]);
		if (mode == 3) stop(m);
		if (mode == 4) run(n & 16777215);
	}
}

void run(int m) {
	memset(cnt, 0, sizeof(cnt));
	for (unsigned int i = 0; i < file[m].size(); i++) {
		Run(file[m][i], m, i);
	}
}

int main() {
	init();
	while (1) {
		int n;
		cin >> n;
		run(n);
	}
} 