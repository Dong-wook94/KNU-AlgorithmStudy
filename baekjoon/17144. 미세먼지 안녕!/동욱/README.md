# 미세먼지 안녕!
> 삼성 sw 역량테스트 기출문제
시뮬레이션 문제이다.

### 1초당 일어나는일
1. 확산
2. 공기청정기 이동이 필요하다.



**확산**

~~~c++
void SpreadDust() {//미세먼지 확산

	init_NextMap();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Map[i][j] > 0) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int next_row = i + dir_row[d];
					int next_col = j + dir_col[d];
					if (next_row >= 0 && next_col >= 0 && next_row < R&&next_col < C&&Map[next_row][next_col] != -1) {
						NextMap[next_row][next_col] += (Map[i][j] / 5);
						cnt++;
					}
				}
				NextMap[i][j] = NextMap[i][j] + Map[i][j] - ((Map[i][j] / 5)*cnt);
			}
		}
	}
	map_copy(Map, NextMap);
}
~~~

**공기정화**

> 배열 저장이 고려하기 귀찮아서 다른 map에 옮긴후 다시 copy하는 방법이용

~~~c++
void AirCleanerProcess(int num) {
	int col = cleaner[num].col + 1;
	int row = cleaner[num].row;

	NextMap[row][col] = 0;

	for (int i = 0; i < 4; i++) {
		while (1) {
			int next_row = row + dir_row[circulate[num][i]];
			int next_col = col + dir_col[circulate[num][i]];

			//방향바꾸는타이밍
			if (next_row <0 || next_col < 0 || next_row >= R||next_col >= C||Map[next_row][next_col] == -1) {
				break;
			}
			NextMap[next_row][next_col] = Map[row][col];
			row = next_row;
			col = next_col;
		}
	}
}
~~~

시계방향 반시계방향 구현 쉽게하기위해 순환배열을 두었다

~~~c++
int dir_row[4] = { 0,-1,0,1 };
int dir_col[4] = { 1,0,-1,0 };
//위의 배열을 아래 순으로돌림.
int circulate[2][4] = {
	{ 0,1,2,3 },//반시계방향
{0,3,2,1}//시계방향
};
~~~

