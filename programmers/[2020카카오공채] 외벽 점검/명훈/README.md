# [2020 KAKAO BLIND RECRUITMENT] 외벽 점검

![image](https://user-images.githubusercontent.com/42582516/80854184-fa319280-8c70-11ea-9c85-6c43cee542d6.png)

## 문제 알고리즘

- 순열



## 풀이방법

* 취약지점은 원형의 형태를 지니고 있고, 하나의 취약지점에서 시작하는 것이 많은 취약지점을 방문할 수 있는 시작점이다. 그러므로 취약지점을 deque형태로 만들어서, 갈 수 있는 경우를 모두 구한다.
* 사람 수를 점차 올리면서 그 사람의 수로 취약지점을 전부 방문 가능한지 확인한다.
  * 그 사람이 최대 갈수있는 취약지점을 체크하고 못 갔던 부분은 그 다음사람에게 넘긴다. 

![image](https://user-images.githubusercontent.com/42582516/80854217-2fd67b80-8c71-11ea-9322-bcd0f2bfd78b.png)

- 핵심 코드

~~~c++
#include    <iostream>
#include    <string>
#include    <vector>
#include    <deque>
#include    <algorithm>
using namespace std;

bool isFinished(vector<int> dist, deque<int> weakList, int cnt) {
	sort(dist.begin(), dist.end());
	
	do {
		int start = 0;
		for (int i = 0, j=start; i < cnt; i++) {
			// i는 사람 번호, j는 그 사람이 갈 수 있는 취약지점 위치
			int possibleDist = weakList[start] + dist[i];
			while (j < weakList.size()) {
				if (weakList[j] <= possibleDist)
					j++;		// 더 갈수있으면 더 간다
				else {
					start = j;	// 다음 사람에게 맡김
					break;
				}
			}
			// 취약지점을 다 돈 경우
			if (j == weakList.size()) {
				return true;
			}
		}
	} while (next_permutation(dist.begin(), dist.end()));

	return false;
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	deque<int> weakList;

	// 취약지점 없으면 0
	if (weak.size() == 0)
		return 0;

	// 사람 수를 올리면서 확인
	for (int i = 1; i <= dist.size(); i++) {                 // 사람 수
		// weak list 생성
		for (int j = 0; j < weak.size(); j++)
			weakList.push_back(weak[j]);
		for (int j = 0; j < weak.size(); j++) {

			// 해당 사람수로 해결되면 종료
			if (isFinished(dist, weakList, i))
				return i;

			int key = weakList.front();
			weakList.pop_front();
			weakList.push_back(key + n);
		}
		weakList.clear();
	}
	return -1;
}

int main() {
	cout << solution(12, { 1, 5, 6, 10 }, { 1, 2, 3, 4 }) << "\n";
	cout << solution(12, { 1, 3, 4, 9, 10 }, { 3, 5, 7 }) << "\n";
}
~~~



## 문제 후 느낀점

- 다른 아이디어를 참고했다.

