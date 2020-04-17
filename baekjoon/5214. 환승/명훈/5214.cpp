#include	<iostream>
#include	<vector>
#include	<queue>
#include	<algorithm>
using namespace std;

#define MAX 100000 + 1

vector<int> adj_list[MAX + 2000];
bool visited[MAX + 2000];
int N, K, M;

int bfs() {
	queue<pair<int, int>> q;	// (station, cnt);
	q.push({ 1, 1 });
	visited[1] = true;

	while (!q.empty()) {
		int curStation = q.front().first;
		int curCnt = q.front().second;
		q.pop();

		if (curStation == N) {
			return curCnt;
		}

		for (int i = 0; i < adj_list[curStation].size(); i++) {
			int nextStation = adj_list[curStation][i];
			if (!visited[nextStation]) {
				if (nextStation > N)		// ´õ¹Ì¿ª
					q.push({ nextStation, curCnt });
				else {
					q.push({ nextStation, curCnt + 1 });
					visited[nextStation] = true;
				}
			}
		}
	}
	return -1;
}

int main() {
	// input
	int key;
	cin >> N >> K >> M;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < K; j++) {
			scanf("%d", &key);
			adj_list[MAX + i].push_back(key);
			adj_list[key].push_back(MAX + i);
		}
	}

	// solution & output
	cout << bfs() << "\n";

	return 0;
}
