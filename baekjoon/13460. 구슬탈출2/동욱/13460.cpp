#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef struct Pos {
	int row;
	int col;
}Pos;
typedef struct State {
	Pos R;
	Pos B;
	int cnt;
	int visit[10][10][10][10] = { 0 };
}State;

State Cur;
Pos Hole;
queue<State> q;

int N, M;//N :행개수 M:열개수
//# : 벽 , . :빈칸 , O : 구멍 , R : 빨간구슬, B : 파란구슬
//배열에 입력시(1:구멍 -1 : 벽 0 : 빈칸
int board[10][10];

int direction_col[4] = { 1,-1,0,0 };
int direction_row[4] = { 0,0,1,-1 };
int min_cnt = 11;
void BFS();
int main() {
	int flag;
	char input;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%c", &input);
			switch (input)
			{
			case 'R'://빨간공
				board[i][j] = 0;
				Cur.R.row = i;
				Cur.R.col = j;
				break;
			case 'B'://파란공
				board[i][j] = 0;
				Cur.B.row = i;
				Cur.B.col = j;
				break;
			case 'O'://구멍
				board[i][j] = 1;
				Hole.row = i;
				Hole.col = j;
				break;
			case '.'://빈칸
				board[i][j] = 0;
				break;
			case '#'://벽
				board[i][j] = -1;
				break;
			default://예외입력
				j--;
				break;
			}

		}
	}
	Cur.cnt = 0;//카운트 초기화
	q.push(Cur);//시작상태 큐에 삽입
	BFS();//BFS이용
	if (min_cnt > 10)
		printf("-1\n");
	else
		printf("%d\n", min_cnt);
}

void BFS() {
	State x, temp;
	int flag;

	while (!q.empty()) {
		x = q.front();
		q.pop();
		temp.cnt = x.cnt + 1;


		if (temp.cnt > 10)
			return;

		for (int i = 0; i < 4; i++) {//4방향으로 기울였을경우들
			flag = 0;
			//빨간공 굴리기 먼저
			for (int n = 0; ; n++) {//n은 얼마나 이동하는 칸수 
				temp.R.row = x.R.row + direction_row[i] * n;
				temp.R.col = x.R.col + direction_col[i] * n;
				if (temp.R.row >= 0 && temp.R.col >= 0 && temp.R.row < N&&temp.R.col < M)
				{
					if (board[temp.R.row][temp.R.col] == -1) {
						temp.R.row = x.R.row + direction_row[i] * (n - 1);
						temp.R.col = x.R.col + direction_col[i] * (n - 1);
						break;//벽만났을때
					}
					if (temp.R.row == x.B.row &&temp.R.col == x.B.col)//빨간공이 가다가 파란공을 만난경우
					{
						flag = 1;
						//진행하다가 파란공 만났을때
						//파란공먼저굴리기
						break;
					}
					if (board[temp.R.row][temp.R.col] == 1) {//목표도착 후 파란공처리
						for (int n = 0; ; n++) {//n은 얼마나 이동하는 칸수 
							temp.B.row = x.B.row + direction_row[i] * n;
							temp.B.col = x.B.col + direction_col[i] * n;
							if (temp.B.row >= 0 && temp.B.col >= 0 && temp.B.row < N&&temp.B.col < M)
							{

								if (board[temp.B.row][temp.B.col] == 1) {//파란공이 들어가는경우
									flag = 3;
									break;
								}
								if (board[temp.B.row][temp.B.col] == -1) {
									//printf("목표도착 : %d\n", temp.cnt);
									if (min_cnt > temp.cnt)
										min_cnt = temp.cnt;
									break;
								}
							}
							else break;
						}
					}
				}
				else break;
				if (flag == 3) {
					break;
				}
			}
			//파란공 굴림 
			if (flag == 3)
				continue;
			if (flag == 0) {//빨간공이 가다가 파란공을 만나지 않은경우
				for (int n = 0; ; n++) {//n은 얼마나 이동하는 칸수 
					temp.B.row = x.B.row + direction_row[i] * n;
					temp.B.col = x.B.col + direction_col[i] * n;
					if (temp.B.row >= 0 && temp.B.col >= 0 && temp.B.row < N&&temp.B.col < M)
					{
						if (board[temp.B.row][temp.B.col] == -1 || (temp.R.row == temp.B.row &&temp.R.col == temp.B.col)) {
							temp.B.row = x.B.row + direction_row[i] * (n - 1);
							temp.B.col = x.B.col + direction_col[i] * (n - 1);
							if (x.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] != 1) {//방문안했던곳일때
								temp.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] = 1;
								temp.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] = 1;
								//printf("\n방문 : R(%d,%d),B(%d,%d) cnt : %d\n", temp.R.row, temp.R.col, temp.B.row, temp.B.col, temp.cnt);

								q.push(temp);
							}
							break;//벽만났을때
						}
						if (board[temp.B.row][temp.B.col] == 1) {//파란공이 들어가는경우
							break;
						}
					}
					else break;
				}
			}
			else {//빨간공이 가다가 파란공을 만난경우 파란공이 먼저가는경우
				for (int n = 0; ; n++) {//n은 얼마나 이동하는 칸수 
					temp.B.row = x.B.row + direction_row[i] * n;
					temp.B.col = x.B.col + direction_col[i] * n;
					if (temp.B.row >= 0 && temp.B.col >= 0 && temp.B.row < N&&temp.B.col < M)
					{
						if (board[temp.B.row][temp.B.col] == -1) {
							temp.B.row = x.B.row + direction_row[i] * (n - 1);
							temp.B.col = x.B.col + direction_col[i] * (n - 1);
							break;//벽만났을때
						}
						if (board[temp.B.row][temp.B.col] == 1) {//파란공이 목표점 먼저들어온경우 실패처리
							flag = 2;
							break;
						}
					}
					else break;
				}
				if (flag != 2) {//파란공이 먼저 도착하지 않은경우
					for (int n = 0; ; n++) {//n은 얼마나 이동하는 칸수 
						temp.R.row = x.R.row + direction_row[i] * n;
						temp.R.col = x.R.col + direction_col[i] * n;
						if (temp.R.row >= 0 && temp.R.col >= 0 && temp.R.row < N&&temp.R.col < M)
						{
							if ((temp.R.row == temp.B.row &&temp.R.col == temp.B.col) || board[temp.R.row][temp.R.col] == -1) {
								temp.R.row = x.R.row + direction_row[i] * (n - 1);
								temp.R.col = x.R.col + direction_col[i] * (n - 1);
								if (x.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] != 1) {//방문안했던곳일때
									temp.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] = 1;
									temp.visit[temp.R.row][temp.R.col][temp.B.row][temp.B.col] = 1;
									//printf("\n방문 : R(%d,%d),B(%d,%d) cnt : %d\n", temp.R.row, temp.R.col, temp.B.row, temp.B.col, temp.cnt);
									q.push(temp);
								}
								break;//파란공만났을때
							}
						}
						else break;
					}
				}

			}
		}
	}
}