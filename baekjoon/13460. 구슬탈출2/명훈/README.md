# 구슬탈출2

## 문제 알고리즘
- bfs문제

## 풀이방법
1. bfs를 통해서 경로를 찾는다
2. 특히, 신경써줘야하는 부분은 파란공과 빨간공이 합쳐지는 경우인데 이를 예외로 잘 처리해준다.

- 핵심 코드
~~~c++
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
~~~

## 문제 후 느낀점

- bfs문제
- 옛날에 볼 때는 어려웠는데 좀 나아진 문제인 듯 하다.