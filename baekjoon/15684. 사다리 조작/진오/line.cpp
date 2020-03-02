#include <iostream>
#define MAX 99999

using namespace std;

int N, M, H, a, b, line[31][10] = { 0 ,};
int ans = MAX;

void makeLine(int row, int col, int cnt, int total);
int testAll();
int test(int col);

int main()
{
	cin >> N;
	cin >> M;
	cin>> H;
	for (int m = 1; m <= M; m++) {
		cin >> a >> b;
		line[a][b] = 1;
	}

	int res = testAll();
	if (res != -1) {
		ans = 0;
		cout << ans;
		return 0;
	}
	else {
		for (int trial = 1; trial < 4; trial++) {
			makeLine(1, 1, 1, trial);
		}
	}

	if (ans == MAX) ans = -1;

	cout << ans;

	return 0;
}
void makeLine(int row, int col, int cnt, int total) {
	if (cnt > total) return;
	for (int i = col; i < N; i++) {
		for (int j = 1; j <= H; j++) {
			if (i == col && j == 1) j = row;
			if (line[j][i - 1] != 1 && line[j][i] != 1 && line[j][i + 1] != 1) {
				line[j][i] = 1;
				if (cnt == total) {
					int res = testAll();
					if (res != -1) {
						if (ans > total) ans = total;
					}
				}
				makeLine(j, i, cnt + 1, total);
				line[j][i] = 0;
			}
		}
	}
}
int test(int col) {
	int row = 1;
	while (row <= H) {
		if (line[row][col]) { 
			col++;
			row++;
			continue;
		}
		else if (line[row][col - 1]) { 
			col--;
			row++;
			continue;
		}
		else {
			row++;
		}
	}

	return col;
}
int testAll() { 
	int res = 0;
	for (int i = 1; i <= N; i++) {
		res = test(i);
		if (res != i) {
			res = -1;
			break;
		}
	}

	return res; 
}