# 14891. 톱니바퀴

## 문제 알고리즘

- 시뮬레이션

## 풀이방법

1. 문제에서 요구하는 대로 풀어주기
2. deque를 사용했다.

* 풀이 사진

  ![image](https://user-images.githubusercontent.com/42582516/80221801-c2c75280-8680-11ea-87eb-f4b6954f5e25.png)

  

- 핵심 코드

~~~c++
#include	<iostream>
#include	<vector>
#include	<string>
#include	<deque>
using namespace std;

deque<int> gear[4];

void turnSelfGear(int gearNum, int gearDir) {
	if (gearDir == 1) {
		int tmp = gear[gearNum][7];
		gear[gearNum].pop_back();
		gear[gearNum].push_front(tmp);
	}
	else {
		int tmp = gear[gearNum][0];
		gear[gearNum].pop_front();
		gear[gearNum].push_back(tmp);
	}

}

void turnLeftGear(int gearNum, int gearDir) {
	if (gearNum < 0)
		return;
	if (gear[gearNum][2] != gear[gearNum + 1][6]) {
		turnLeftGear(gearNum - 1, (gearDir == 1) ? -1 : 1);
		turnSelfGear(gearNum, gearDir);
	}
}

void turnRightGear(int gearNum, int gearDir) {
	if (gearNum > 3)
		return;
	if (gear[gearNum - 1][2] != gear[gearNum][6]) {
		turnRightGear(gearNum + 1, (gearDir == 1) ? -1 : 1);
		turnSelfGear(gearNum, gearDir);
	}
}

int getAnswer() {
	int answer = 0, key = 1;
	for (int i = 0; i < 4; i++) {
		answer += gear[i][0] * key;
		key *= 2;
	}
	return answer;
}

int main() {
	// input
	string gearLine;
	for (int i = 0; i < 4; i++) {
		cin >> gearLine;
		for (int j = 0; j < 8; j++) {
			gear[i].push_back((gearLine[j] - '0'));
		}
	}
	int K, gearNum, gearDir;
	cin >> K;

	// solution
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &gearNum, &gearDir);
		gearNum--;
		turnLeftGear(gearNum - 1, (gearDir == 1) ? -1 : 1);
		turnRightGear(gearNum + 1, (gearDir == 1) ? -1 : 1);
		turnSelfGear(gearNum, gearDir);
	}

	// output
	cout << getAnswer() << "\n";

	return 0;
}
~~~

## 문제 후 느낀점

- 시뮬레이션