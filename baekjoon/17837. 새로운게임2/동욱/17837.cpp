#include <stdio.h>
#include <vector>
#define MAP_MAX 13
#define CHESS_MAX 11

using namespace std;

typedef struct Chess {
	int row;
	int col;
	int dir;
	Chess() {}
	Chess(int r, int c, int d) { row = r; col = c; dir = d; }
}Chess;

typedef struct Map {
	int color;
	vector<int> state;
}Map;


int dir_row[5] = {0,0,0,-1,1};
int dir_col[5] = {0,1,-1,0,0};
Map map[MAP_MAX][MAP_MAX];
Chess chess_info[CHESS_MAX];

int map_size,chess_size;
void insertData()
{
	scanf("%d %d", &map_size, &chess_size);
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			scanf("%d", &map[i][j].color);
		}
	}
	for (int i = 0; i < chess_size; i++) {
		int row, col, dir;
		scanf("%d %d %d", &row,&col,&dir);
		chess_info[i] = Chess(row, col, dir);
		map[row][col].state.push_back(i);
	}
}
bool checkMapRange(int next_row, int next_col)
{
	return next_row > 0 && next_col > 0 && next_row <= map_size && next_col <= map_size;
}

int findFloor(int row, int col, int chess_num) {
	for (int i = 0; i < map[row][col].state.size(); i++) {
		if (map[row][col].state[i] == chess_num)
			return i;
	}
}
void moveAllChess(int &cnt, int floor, Chess &cur, int next_row, int next_col);

void reverseMoveAll(Chess &cur, int floor, int next_row, int next_col);

int reverseDir(int chess_num) {
	switch (chess_info[chess_num].dir){
	case 1:return 2;
	case 2:return 1;
	case 3:return 4;
	case 4:return 3;
	}
}
void moveChess(Chess cur, int next_row, int next_col, int chess_num) {
	int floor = findFloor(cur.row, cur.col, chess_num);
	int cnt=0;
	switch (map[next_row][next_col].color) {
	case 0:// 그냥
		cnt = 0;
		moveAllChess(cnt, floor, cur, next_row, next_col);
		break;
	case 1://쌓인말 순서변경
		
		reverseMoveAll(cur, floor, next_row, next_col);
		break;
	case 2://방향 변경
		cnt = 0;
		int dir = reverseDir(chess_num);
		chess_info[chess_num].dir = dir;
		cur = chess_info[chess_num];
		int nr = cur.row + dir_row[cur.dir];
		int nc = cur.col + dir_col[cur.dir];
		if (checkMapRange(nr, nc)) {
			if (map[nr][nc].color != 2)
				moveChess(cur, nr, nc, chess_num);
		}
		break;
	}
	
}

void reverseMoveAll(Chess &cur, int floor, int next_row, int next_col)
{
	for (int i = map[cur.row][cur.col].state.size() - 1; i >= floor; i--) {//위에 다옮기기
		map[next_row][next_col].state.push_back(map[cur.row][cur.col].state[i]);
		int idx = map[cur.row][cur.col].state[i];
		chess_info[idx].row = next_row;
		chess_info[idx].col = next_col;
		map[cur.row][cur.col].state.pop_back();
	}
}

void moveAllChess(int &cnt, int floor, Chess &cur, int next_row, int next_col)
{
	cnt = 0;
	for (int i = floor; i < map[cur.row][cur.col].state.size(); i++) {//위에 다옮기기
		map[next_row][next_col].state.push_back(map[cur.row][cur.col].state[i]);
		int idx = map[cur.row][cur.col].state[i];
		chess_info[idx].row = next_row;
		chess_info[idx].col = next_col;
		cnt++;
	}
	for (int i = 0; i < cnt; i++) {
		map[cur.row][cur.col].state.pop_back();
	}
}

bool checkEnd() {
	for (int i = 0; i < chess_size; i++) {
		Chess cur = chess_info[i];
		if (map[cur.row][cur.col].state.size() >= 4)
			return true;
	}
	return false;
}

int Process() {
	int cnt = 0;
	while (1) {
		if (cnt > 1000)
			break;
		for (int i = 0; i < chess_size; i++) {
			//printf("\n%d 말 옮길때 : \n",i);
			Chess cur = chess_info[i];
			int next_row = cur.row + dir_row[cur.dir];
			int next_col = cur.col + dir_col[cur.dir];

			if (checkMapRange(next_row, next_col)) {
				moveChess(cur, next_row, next_col, i);
			}
			else {
				int dir = reverseDir(i);
				chess_info[i].dir = dir;
				cur = chess_info[i];
				int nr = cur.row + dir_row[cur.dir];
				int nc = cur.col + dir_col[cur.dir];
				if (checkMapRange(nr, nc)) {
					if (map[nr][nc].color != 2)
						moveChess(cur, nr, nc, i);
				}
			}
			if (checkEnd()) {
				return cnt+1;
			}

			/*for (int i = 0; i <= chess_size; i++) {
				printf("[%d %d %d]\n", chess_info[i].row, chess_info[i].col, chess_info[i].dir);
			}
			for (int i = 1; i <= map_size; i++) {
				for (int j = 1; j <= map_size; j++) {
					printf("(");
					for (int k = 0; k < map[i][j].state.size(); k++) {
						printf("%d ",map[i][j].state[k]);
					}
					printf(")");
				}
				printf("\n");
			}*/
		}
		cnt++;
		
	}
	return -1;
}



int main() {
	insertData();
	printf("%d\n",Process());
}