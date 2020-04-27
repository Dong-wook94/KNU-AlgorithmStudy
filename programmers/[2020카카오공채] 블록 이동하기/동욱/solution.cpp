#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define HORIZONTAL 0
#define VERTICAL 1

using namespace std;

typedef struct Robot {
	int row;
	int col;
	int dir;
	int time;
	Robot(int r, int c, int d, int t) { row = r; col = c; dir = d; time = t; }
}Robot;

int dir_row[4] = {1,0,-1,0};
int dir_col[4] = {0,-1,0,1};
int turn_row[2][4] = { {0,0,-1,-1},{1,1,0,0} };
int turn_col[2][4] = { {0,1,0,1},{0,-1,0,-1} };
int visited[2][101][101];

queue<Robot> q;

bool checkEnd(Robot cur,int n) {
	if (cur.dir == HORIZONTAL) {
		if (cur.row == n - 1 && cur.col + 1 == n - 1)
			return true;
	}
	else {
		if (cur.row + 1 == n - 1 && cur.col == n - 1)
			return true;
	}
	return false;
}

//범위 넘을때, 벽일때 false 반환
bool canMoveNext(int r, int c, int d,vector<vector<int>> board) {
	int b_size = board.size();
	if (r < 0 || r >= b_size|| c < 0 || c >= b_size)
		return false;
	if (board[r][c] == 1)
		return false;
	if (d == HORIZONTAL) {
		if (c + 1 >= b_size || board[r][c+1] ==1)
			return false;
	}
	else {
		if (r + 1 >= b_size || board[r + 1][c] == 1)
			return false;
	}
	return true;
}

//회전시 범위가 넘을때, 회전 중간에 벽만나는지 체크
bool canTurnRobot(Robot cur, int next_row, int next_col, vector<vector<int>> board) {
	int b_size = board.size();
	if (cur.dir == HORIZONTAL) { // 가->세
		if (cur.row == next_row) { //아래로 돌리는 회전
			if (cur.row + 1 >= b_size)//범위 벗어날때
				return false;
			if (board[cur.row + 1][cur.col] || board[cur.row + 1][cur.col + 1]) //둘중 하나라도 벽일때
				return false;
		}
		else { // 위로 돌리는 회전
			if (cur.row - 1 < 0)
				return false;
			if (board[cur.row - 1][cur.col] || board[cur.row - 1][cur.col + 1])
				return false;
		}
	}
	else {// 세->가
		if (cur.col == next_col) {//오른쪽으로 돌리는 회전
			if (cur.col + 1 >= b_size)
				return false;
			if (board[cur.row][cur.col + 1] || board[cur.row + 1][cur.col + 1])
				return false;
		}
		else {
			if (cur.col - 1 < 0)
				return false;
			if (board[cur.row][cur.col - 1] || board[cur.row + 1][cur.col - 1])
				return false;
		}
	}
	return true;
}

int BFS(vector<vector<int>> board) {
	q.push(Robot(0, 0, HORIZONTAL, 0));
	visited[HORIZONTAL][0][0] = 1;
	while (!q.empty()) {
		Robot cur = q.front();
		q.pop();
		cout << cur.row << ","<< cur.col <<" : "<< cur.dir << endl;
		if (checkEnd(cur, board.size())) {
			return cur.time;
		}
		//회전말고 네방향 이동
		for (int i = 0; i < 4; i++) { 
			int next_row = cur.row + dir_row[i];
			int next_col = cur.col + dir_col[i];

			if (!canMoveNext(next_row, next_col, cur.dir, board))
				continue;
			if (!visited[cur.dir][next_row][next_col]) {//방문 안했었다면
				visited[cur.dir][next_row][next_col] = 1;
				q.push(Robot(next_row, next_col, cur.dir, cur.time + 1));
			}
		}
		//회전
		for (int i = 0; i < 4; i++) { //4가지 방법의 회전
			int next_dir = cur.dir ^ 1; //xor연산을 통해 방향 뒤집기
			int next_row = cur.row + turn_row[cur.dir][i];
			int next_col = cur.col + turn_col[cur.dir][i];
	

			if (!canTurnRobot(cur, next_row, next_col, board))
				continue;
			if (!visited[next_dir][next_row][next_col]) {
				visited[next_dir][next_row][next_col] = 1;
				q.push(Robot(next_row, next_col, next_dir, cur.time + 1));
			}
		}
	}
}

int solution(vector<vector<int>> board) {
	return BFS(board);
}

int main() {
	vector<vector<int>> board = { {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0} };
	cout << solution(board) << endl;
}