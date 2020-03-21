# 1525 퍼즐

## 문제 알고리즘
- bfs

## 문제 설명
- 따로 어려웠던 부분 없이 쉬웠던 문제

## 풀이방법
1. string으로 bfs()를 사용했다.
2. 'set<string>'을 이용해서 방문여부를 확인했다.


- 핵심 코드
~~~c++
int bfs(string init_str) {
	queue<pair<string, int>> q;
	q.push({ init_str, 0 });
	visited.insert(init_str);

	while (!q.empty()) {
		string curStr = q.front().first;
		int curCnt = q.front().second;
		int zero_pos = curStr.find("0");
		int curY = zero_pos / 3;
		int curX = zero_pos % 3;
		q.pop();

		if (curStr.compare(endStr) == 0)
			return curCnt;

		// check all
		for (int dir = 0; dir < 4; dir++) {
			int nextY = curY + dy[dir];
			int nextX = curX + dx[dir];
			int next_pos = nextY * 3 + nextX;

			if (0 <= nextY && nextY < MAX && 0 <= nextX && nextX < MAX) {
				string tmp(curStr);
				tmp[zero_pos] = tmp[next_pos];
				tmp[next_pos] = '0';

				if (visited.find(tmp) == visited.end()) {
					q.push({ tmp, curCnt + 1 });
					visited.insert(tmp);
				}
			}
		}
	}
	return -1;
}
~~~



