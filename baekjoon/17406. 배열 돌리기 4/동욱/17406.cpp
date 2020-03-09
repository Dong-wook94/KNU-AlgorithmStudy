#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;
int N, M, K; //K는 회전연산의 개수

int Map[51][51];
int originalMap[51][51];
typedef struct Rotate {
	int row, col, size;
	Rotate(){}
	Rotate(int r, int c, int s) {
		row = r; col = c; size = s;
	}
}Rotate;

vector<Rotate> rotate_info;
vector<int> rotate_order;

int dir_row[4] = {1,0,-1,0};
int dir_col[4] = { 0,1,0,-1 };

int result = INT_MAX;
bool check_edge(int next_row, int next_col, int row, int col, int rotate_size) {
	if (next_row == row + rotate_size && next_col == col + rotate_size) 
		return true;
	else if (next_row == row - rotate_size && next_col == col + rotate_size) 
		return true;
	else if (next_row == row - rotate_size && next_col == col - rotate_size) 
		return true;
	else if (next_row == row + rotate_size && next_col == col - rotate_size) 
		return true;
	return false;
}
void rotateArray(Rotate rotate) {
	for (int s = 1; s <=rotate.size; s++) {
		int temp = Map[rotate.row - s][rotate.col - s];
		int d = 0;
		int cur_row = rotate.row - s;
		int cur_col = rotate.col - s;
		int next_row = cur_row + dir_row[d];
		int next_col = cur_col + dir_col[d];
		while (1) {
			if (next_row == rotate.row - s && next_col == rotate.col - s) { //회전 시작지점이 next일때
				Map[cur_row][cur_col] = temp;
				break;
			}
			Map[cur_row][cur_col] = Map[next_row][next_col];
			cur_row = next_row;
			cur_col = next_col;
			next_row = cur_row + dir_row[d];
			next_col = cur_col + dir_col[d];
			if (check_edge(next_row, next_col, rotate.row, rotate.col, s))
				d = (d + 1) % 4;
		}
	}
	
}
void copyMap(int a[][51], int b[][51]) {
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <=M; j++) {
			a[i][j] = b[i][j];
		}
	}
}
//void print_map() {
//	printf("\nmap : \n");
//	for (int i = 1; i <= N; i++) {
//		for (int j = 1; j <= M; j++) {
//			printf("%d ", Map[i][j]);
//		}
//		printf("\n");
//	}
//}
int minSumOfRow() {
	int min_sum = INT_MAX;
	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = 1; j <= M; j++) {
			sum += Map[i][j];
		}
		//printf("%d행 합 : %d\n", i, sum);
		min_sum = min(min_sum, sum);
	}
	return min_sum;
}

void findMinResult() {
	do {
		copyMap(Map, originalMap);
		//print_map();
		for (int i = 0; i < rotate_order.size(); i++) {
			rotateArray(rotate_info[rotate_order[i]]);
			//print_map();
		}
		//print_map();
		result = min(result,minSumOfRow());
	} while (next_permutation(rotate_order.begin(), rotate_order.end()));
}
int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <=M; j++) {
			scanf("%d", &originalMap[i][j]);
		}
	}
	for (int i = 0; i < K; i++) {
		int r, c, s;
		scanf("%d %d %d", &r,&c,&s);
		rotate_info.push_back(Rotate(r, c, s));
		rotate_order.push_back(i);
	}
	findMinResult();
	printf("%d\n", result);
}