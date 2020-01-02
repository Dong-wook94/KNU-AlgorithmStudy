#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;
int N, M, start;
void dfs(int v);
void bfs(int v);
queue<int> q;
int main() {
	int a, b;
	scanf("%d %d %d", &N, &M, &start);
	graph.assign(N + 1, vector<int>(0, 0));
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);//a->b
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}
	visited.assign(N + 1, 0);
	dfs(start);
	visited.assign(N + 1, 0);
	printf("\n");
	bfs(start);
}

void dfs(int v) {
	visited[v] = 1;
	printf("%d ", v);
	for (int i = 0; i < graph[v].size(); i++) {
		if (!visited[graph[v][i]])
			dfs(graph[v][i]);
	}
}

void bfs(int v) {
	q.push(v);
	visited[v] = 1;

	while (!q.empty()) {
		v = q.front();
		q.pop();
		printf("%d ", v);
		for (int i = 0; i < graph[v].size(); i++) {
			if (!visited[graph[v][i]]) {
				visited[graph[v][i]] = 1;
				q.push(graph[v][i]);
			}
		}
	}

}