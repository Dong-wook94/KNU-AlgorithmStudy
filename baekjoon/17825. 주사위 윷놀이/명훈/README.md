# 주사위 윷놀이



## 문제 알고리즘

- dfs문제

## 풀이방법

1. dfs를 돌리면서, 순서 배열(order[10])을 채우다가 가득채우면 그때 합을 구한다
2. 가는 길은 4가지의 길로 구별했다. 0번 길이 둘러가는 길
3. 경로를 체크할 때 두가지를 체크한다.
   1. 도착했는지 여부.
   2. 지름길(파란길)에 도착했는지.
   3. 길에 말이 중복으로 있는지 확인
4. 최댓값을 최신화 시켜주면서 답을 구한다.



- 핵심 코드

~~~c++int board[MAX][MAX];						// array
#include	<iostream>
#include	<algorithm>
using namespace std;

#define MAX 10

struct horse {
	int id;		// 길 넘버
	int loc;	// 현재 위치
	bool arrived;
};

int board_len[4] = { 21, 8, 7, 8 };
int board[4][22] = {
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0},
	{10, 13, 16, 19, 25, 30, 35, 40, 0},
	{20, 22, 24, 25, 30, 35, 40, 0},
	{30, 28, 27, 26, 25, 30, 35, 40, 0}
};

int dice[MAX];
int order[MAX];
int max_score = -1;

bool isInBoard(horse Horse[4], int idx) {
	if (Horse[idx].loc < board_len[Horse[idx].id])
		return true;
	return false;
}

int getCross(horse Horse[4], int idx) {
	if (Horse[idx].id == 0) {
		if (Horse[idx].loc == 5 || Horse[idx].loc == 10 || Horse[idx].loc == 15)
			return Horse[idx].loc / 5;
		else
			return 0;
	}
	return 0;
}

bool isAnyHorse(horse Horse[4], int idx) {
	for (int i = 0; i < 4; i++) {
		if (i != idx) {
			// 숫자판이 같은 경우
			if (board[Horse[idx].id][Horse[idx].loc] == board[Horse[i].id][Horse[i].loc]) {
				if (Horse[idx].id == Horse[i].id)
					return true;		// 아예 경로가 겹치는 경우
				else if (Horse[idx].loc >= board_len[Horse[idx].id] - 4 && Horse[i].loc >= board_len[Horse[i].id] - 4)
					return true;		// 경로가 겹치는 파란길 4칸(25, 30, 35, 40)에서 만나는 경우 
				else
					return false;
			}
		}
	}
	return false;
}

void dfs(int cnt) {
	if (cnt == 10) {
		// 실행 코드
		horse Horse[4];
		int score = 0;
		for (int i = 0; i < 4; i++)	// init
			Horse[i] = { 0, 0, false };

		for (int i = 0; i < 10; i++) {
			int idx = order[i];		// idx 는 i번째 움직일 말
			int move = dice[i];		// move 는 i번째에 움직일 칸
			if (isInBoard(Horse, idx)) {	// 맵안에 있는 경우만
				Horse[idx].loc += move;
				
				if (!isInBoard(Horse, idx)) {	// 밖에 나가버린 경우, 도착처리
					Horse[idx].arrived = true;
					Horse[idx].loc = board_len[Horse[idx].id];
				}
				score += board[Horse[idx].id][Horse[idx].loc];

				// 경로가 바뀌는 경우 체크
				int new_id = getCross(Horse, idx);
				if (new_id) {
					Horse[idx].id = new_id;
					Horse[idx].loc = 0;
				}

				// 만약에 도착을 안했는데 겹치는 경우가 있으면 바로 종료
				if (!Horse[idx].arrived && isAnyHorse(Horse, idx))
					return;
			}
			else
				return;
		}
		max_score = max(max_score, score);
		return;
	}

	for (int i = 0; i < 4; i++) {
		order[cnt] = i;
		dfs(cnt + 1);
	}
}


int main() {
	// input
	for (int i = 0; i < MAX; i++)
		scanf("%d", &dice[i]);

	// solution
	dfs(0);

	// output
	cout << max_score << "\n";
	return 0;
}
~~~

## 문제 후 느낀점

- dfs문제
- 어려워서 다른 사람 코드를 많이 참고 했다.