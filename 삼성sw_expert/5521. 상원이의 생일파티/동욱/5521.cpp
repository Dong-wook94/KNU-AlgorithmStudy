#include <stdio.h>
#include <vector>
using namespace std;

int N, M;
int cnt = 0;
vector<int> visited;
void dfs(int num,vector<vector<int>> graph,int depth) {
	if (depth == 2)
		return;
	for (int i = 0; i < graph[num].size(); i++) {
		visited[graph[num][i]] = 1;
		dfs(graph[num][i], graph, depth + 1);
		
	}

}
void Testcase() {
	scanf("%d %d", &N, &M);
	vector<vector<int>> graph;
	visited.assign(N+1, 0);
	graph.assign(N + 1, vector<int>(0, 0));
	cnt = 0;

	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	visited[1] = 1;
	dfs(1,graph,0);
	for (int i = 2; i <= N; i++) {
		if (visited[i])
			cnt++;
	}
}

int main() {
	int testcase;
	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		Testcase();
		visited.clear();
		printf("#%d %d\n", t, cnt);
	}
}