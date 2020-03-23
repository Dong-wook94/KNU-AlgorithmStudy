#include	<iostream>
#include	<queue>
using namespace std;

#define MAX 10

struct bead {
	int rx, ry, bx, by, d;
};

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int N, M;
char map[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];
queue<bead> q;

void move(int &x, int &y, int &c, int dx, int dy) {
	while (map[x + dx][y + dy] != '#' && map[x][y] != 'O') {
		x += dx;
		y += dy;
		c += 1;
	}
}

void bfs() {
	while(!q.empty()) {
		int rx = q.front().rx;
		int ry = q.front().ry;
		int bx = q.front().bx;
		int by = q.front().by;
		int d = q.front().d;
		q.pop();

		if (d >= 10)
			break;
		for (int i = 0; i < 4; i++) {
			int nrx = rx, nry = ry, nbx = bx, nby = by;
			int rc = 0, bc = 0, nd = d + 1;
			move(nrx, nry, rc, dx[i], dy[i]);
			move(nbx, nby, bc, dx[i], dy[i]);
			if (map[nbx][nby] == 'O') continue;
			if (map[nrx][nry] == 'O') {
				cout << nd << "\n";
				return;
			}
			if(nrx == nbx && nry == nby){
				if (rc > bc) nrx -= dx[i], nry -= dy[i];
				else nbx -= dx[i], nby -= dy[i];
			}
			if (visited[nrx][nry][nbx][nby]) continue;
			visited[nrx][nry][nbx][nby] = true;
			q.push({ nrx, nry, nbx, nby, nd });
		}
	}
	cout << "-1\n";
}

int main() {
	char line[MAX + 1];
	int rx = 0, ry = 0, bx = 0, by = 0;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		scanf("%s", line);
		for (int j = 0; j < M; j++) {
			map[i][j] = line[j];
			if (map[i][j] == 'R')
				rx = i, ry = j;
			else if (map[i][j] == 'B')
				bx = i, by = j;
		}
	}
	q.push({ rx, ry, bx, by, 0 });
	visited[rx][ry][bx][by] = true;
	bfs();

	return 0;
}