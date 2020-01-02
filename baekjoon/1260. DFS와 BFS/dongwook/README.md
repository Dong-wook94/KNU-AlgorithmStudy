# DFS와 BFS

### 풀이방법

* 2차원 vector를 통한 adjlist 생성
* 재귀함수를 이용하여 dfs, 큐를 이용하여 bfs 구현



**dfs 코드**

~~~c++
void dfs(int v) {
	visited[v] = 1;
	printf("%d ", v);
	for (int i =0; i < graph[v].size(); i++) {
		if (!visited[graph[v][i]])
			dfs(graph[v][i]);
	}
}
~~~

**bfs 코드**

~~~c++
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
~~~

