#include	<iostream>
#include	<vector>
using namespace std;

#define MAX 100 + 1

pair<int, int> dir[4] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} }; // (x, y)
bool board[MAX][MAX];
int N;
int x, y, d, g;
vector<int> dragon_curve;

int getDragonCurve() {
	int cnt = 0;
	for (int i = 0; i < MAX - 1; i++)
		for (int j = 0; j < MAX - 1; j++)
			if (board[i][j] && board[i][j + 1] && board[i + 1][j] && board[i + 1][j + 1])
				cnt++;
	return cnt;
}

int main() {
	// input & solution
	cin >> N;
	while(N--){
		scanf("%d %d %d %d", &x, &y, &d, &g);

		// make dragon curve dir
		int size = 1;
		board[x][y] = true;
		x += dir[d].first;
		y += dir[d].second;
		board[x][y] = true;
		dragon_curve.push_back(d);
		for (int i = 0; i < g; i++) {
			for (int j = size - 1; j >= 0; j--) {
				int nextDir = (dragon_curve[j] + 1) % 4;
				x += dir[nextDir].first;
				y += dir[nextDir].second;
				if(x >= 0 && x < MAX && y >= 0 && y < MAX)
					board[x][y] = true;
				dragon_curve.push_back(nextDir);
			}
			size *= 2;
		}

		// clear dragon curve vector
		dragon_curve.clear();
	}

	// output
	cout << getDragonCurve() << "\n";
	return 0;
}