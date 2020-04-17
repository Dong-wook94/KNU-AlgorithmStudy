# [백준 5214] 환승

## 문제 알고리즘

- bfs문제
- 메모리 관리

## 풀이방법

* bfs를 통해서 문제를 푸는데 메모리가 터지는 것을 염두하고 문제를 짜야한다.
  * 처음에는 일반적인 bfs인줄 알고 풀었는데 바로 메모리가 터졌다.
  * 보통 1억개가 넘어가면 300MB가 넘어간다는 이야기를 이 문제를 풀면서 알았다.(100,000개에 100,000개씩 연결이 되면 100억 정도되는데 그러면 메모리가 터져버린다.)
  * 해결책은 1~100000까지는 일반적인 역, 100001 ~ 101000까지는 하이퍼루프 번호로 정해서 연결시켜버리는 것이다.
* 이해를 돕는 사진
  * ![KakaoTalk_20200417_120217608](https://user-images.githubusercontent.com/42582516/79528091-0ed42f00-80a4-11ea-9098-8eb8ff487669.png)

- 핵심 코드

~~~c++
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
				if (nextStation > N)		// 더미역
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

~~~

## 문제 후 느낀점

- 문제를 꼼꼼히 읽어봐야함을 느꼈다.