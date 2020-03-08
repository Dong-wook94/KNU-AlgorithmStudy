#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#define PATH0_END_INDEX 21
#define PATH1_END_INDEX 8
#define PATH2_END_INDEX 7
#define PATH3_END_INDEX 8
using namespace std;

/**
1. 4가지 말이 이동하는 모든 경우를 구한다
2. 10번째 턴이 지난경우 결과의 합을 도출한다.
*/

typedef struct Pos{
	int path;
	int index;
	Pos() {}
	Pos(int p,int i) {
		path = p;
		index = i;
	}
}Pos;

int input[10];

int max_score=0;

int Map[4][22] = { {},
{ 10,13,16,19,25,30,35,40},
{20,22,24,25,30,35,40},
{30,28,27,26,25,30,35,40} };

void makeMap() {
	//일반경로
	for (int i = 0; i <= 20; i++) {
		Map[0][i] = i * 2;
	}
}

Pos connectNextPath(int index) {
	switch (index) {
	case 5:
		return Pos(1, 0);
	case 10:
		return Pos(2, 0);
	case 15:
		return Pos(3, 0);
	default:
		return Pos(0, index);
	}

}

int updateScore(int sum,Pos cur_horses) {
	int score=0;
	score += Map[cur_horses.path][cur_horses.index];
	sum += score;
	return sum;
}

bool checkEnded(Pos cur) {
	if (cur.path == 0 && cur.index >= PATH0_END_INDEX) {
		return true;
	}
	return false;
}

bool checkOverlap(Pos cur,Pos horses[]) {
	for (int i = 0; i < 4;i++) {
		if (checkEnded(cur)) //종료지점은 겹침에서 제외
			return false;
		if (cur.index == horses[i].index && cur.path == horses[i].path)
			return true;
	}
	return false;
}

bool checkAllEnded(Pos horses[]) {
	for (int i = 0; i < 4; i++) {
		if (!checkEnded(horses[i]))
			return false;
	}
	return true;
}
Pos syncMap(Pos cur) {//씽크맞추기
	
	if (cur.path == 1) {
		if (cur.index >= PATH1_END_INDEX - 1) //40지점이후
			return Pos(0, cur.index + 13); //0번째 경로로 변경
	}

	else if (cur.path == 2) {
		if (cur.index >= PATH2_END_INDEX - 1)
			return Pos(0, cur.index + 14);
		else if (cur.index >= 3)
			return Pos(1, cur.index + 1);
	}
	else if (cur.path == 3) {
		if (cur.index >= PATH3_END_INDEX - 1)
			return Pos(0, cur.index + 13);
		else if (cur.index >= 4)
			return Pos(1, cur.index);
	}
	return cur;
}

//시작 turn은 1로
void dfs(int turn,int sum, Pos horses[]) {
	if (turn >10 || checkAllEnded(horses)) { //종료조건
		max_score = max(max_score, sum);
		return;
	}
	//말 다돌림
	for (int i = 0; i < 4; i++) {
		Pos cur = horses[i];
		Pos prev = horses[i];
		if (checkEnded(cur)) {
			continue;
		}
		if (horses[i].path == 0) { //경로변경이 있을수 있다.
			int cur_index = horses[i].index + input[turn-1];
			cur = connectNextPath(cur_index);
		}
		else {//경로변경이 있을수 없다.
			cur.index = cur.index + input[turn-1];
			cur = syncMap(cur);//같은 위치 처리
		}
		if (checkOverlap(cur,horses)) { //겹치는거 확인
			continue;
		}
		if (checkEnded(cur)) {
			cur.index = PATH0_END_INDEX;
		}
		horses[i] = cur;
		//max_score = max(max_score, sum + Map[horses[i].path][horses[i].index]);
		dfs(turn + 1, sum + Map[horses[i].path][horses[i].index] ,horses);
		horses[i] = prev;
	}
}

int main() {
	makeMap();
	for (int i = 0; i < 10; i++) {
		scanf("%d", &input[i]);
	}
	Pos horses[4] = { Pos(0,0),Pos(0,0) ,Pos(0,0) ,Pos(0,0) };
	dfs(1,0,horses);
	printf("%d\n", max_score);
}