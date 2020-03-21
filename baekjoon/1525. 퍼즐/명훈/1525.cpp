#include	<iostream>
#include	<queue>
#include	<algorithm>
#include	<string>
#include	<set>
using namespace std;

#define MAX 3

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, -1, 0, 1 };
string endStr = "123456780";
set<string> visited;

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

int main() {
	// input
	int key;
	string init_str;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++) {
			scanf("%d", &key);
			init_str += to_string(key);
		}

	// solution
	int ans = bfs(init_str);

	// output
	cout << ans << "\n";

	return 0;
}