# 2580 스도쿠

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/82863642-9c395780-9f5d-11ea-8520-d91095c686b9.png)

## 문제 알고리즘

- 위상정렬

## 풀이방법

1. 받은 값들로 graph를 만든다.
2. indegree를 만들어서 진입차수를 결정한다.
3. topological sort를 한다.

- 핵심 코드

```c++
#include	<iostream>
#include	<vector>
#include	<queue>
using namespace std;

#define MAX 1000 + 1

int N, M;
int indegree[MAX];
vector<int> graph[MAX];

void bfs() {
	queue<int> q;
	vector<int> ans;
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q.push(i);
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		ans.push_back(now);
		for (int i = 0; i < graph[now].size(); i++) {
			indegree[graph[now][i]]--;
			if (indegree[graph[now][i]] == 0)
				q.push(graph[now][i]);
		}
	}

	if (ans.size() != N)
		cout << "0\n";
	else
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i] << "\n";

	return;
}

int main() {
	int a, b;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int cnt = 0;
		scanf("%d", &cnt);
		scanf("%d", &a);
		cnt--;
		while (cnt--) {
			scanf("%d", &b);
			graph[a].push_back(b);
			indegree[b]++;
			a = b;
		}
	}
	bfs();

	return 0;
}
```

## 문제 후 느낀점

- 과거에 풀었던 c++ 코드
