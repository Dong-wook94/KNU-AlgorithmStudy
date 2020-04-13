#include	<iostream>
#include	<vector>
#include	<queue>
#include	<algorithm>
using namespace std;

#define MAX 100 + 1

struct Shark {
	int speed;
	int dir;
	int size;
};

pair<int, int> dir[5] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };	//<dy, dx>
int R, C, M;
vector<Shark> sharks[MAX][MAX];	// size, speed, dir

bool isInRange(int y, int x) {
	if (y < 1 || y > R || x < 1 || x > C)
		return false;
	return true;
}

int main() {
	int answer = 0;
	// inpput
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		sharks[r][c].push_back({s, d, z});
	}

	// solution
	for (int j = 1; j <= C; j++) {	// 낚시왕 위치가 j
		// 상어 잡기
		for (int i = 1; i <= R; i++) {
			if (sharks[i][j].size()) {
				answer += sharks[i][j][0].size;
				sharks[i][j].clear();
				break;
			}
		}

		// 상어를 큐에 쌓기
		queue<pair<pair<int, int>, Shark>> q;
		for (int y = 1; y <= R; y++) {
			for (int x = 1; x <= C; x++) {
				if (sharks[y][x].size()) {
					q.push({ { y, x }, sharks[y][x][0] });
					sharks[y][x].clear();
				}
			}
		}

		// 상어 이동
		while (!q.empty()) {
			int y = q.front().first.first;
			int x = q.front().first.second;
			int speed = q.front().second.speed;
			int d = q.front().second.dir;
			int size = q.front().second.size;
			q.pop();

			for (int i = 0; i < speed; i++) {
				if (d == 1 || d == 2) {
					int next = y + dir[d].first;
					if (next < 1 || next > R)
						d = 3 - d;
					y += dir[d].first;
				}
				else {
					int next = x + dir[d].second;
					if (next < 1 || next > C)
						d = 7 - d;
					x += dir[d].second;
				}
			}

			if (sharks[y][x].size()) {
				if (sharks[y][x][0].size < size) {
					sharks[y][x].clear();
					sharks[y][x].push_back({ speed, d, size});
				}
			}
			else
				sharks[y][x].push_back({ speed, d, size });
		}
	}

	// output
	cout << answer << "\n";


	return 0;
}