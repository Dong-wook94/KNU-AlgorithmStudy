#include <iostream>

using namespace std;

int arr[51][51];
int spread[51][51];
int row_num;
int col_num;
int sec;
void spread_dust(int row, int col);
void after_one_sec();
void initial_spread();
void up_move();
void down_move();
int sum_arr();

int main() {
	cin >> row_num;
	cin >> col_num;
	cin >> sec;
	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < sec; i++) {
		after_one_sec();
	}
	cout << sum_arr();
}
void down_move() {
	int row;
	int i;
	for (i = row_num; i >= 1; i--) {// 아래쪽기준을 잡음
		if (arr[i][1] == -1) {
			break;
		}
	}
	row = i;

	for (i = row + 1; i <= row_num; i++) {// 윗 바람의 왼쪽변
		arr[i - 1][1] = arr[i][1];
	}
	for (i = 2; i <= col_num; i++) {//아랫변
		arr[row_num][i - 1] = arr[row_num][i];
	}
	for (i = row_num - 1; i >= row; i--) { //오른쪽
		arr[i + 1][col_num] = arr[i][col_num];
	}
	for (i = col_num - 1; i >= 1; i--) {//윗변
		arr[row][i + 1] = arr[row][i];
	}
	arr[row][2] = 0;// 공기청정기에서 나온공기
	arr[row][1] = -1; // 공기청정해주기
}
void up_move() {
	int row;
	int i;
	for (i = 1; i <= row_num; i++) {
		if (arr[i][1] == -1) {
			break;
		}
	}
	row = i;

	for (i = row - 1; i >= 1; i--) {// 윗 바람의 왼쪽변
		arr[i + 1][1] = arr[i][1];
	}
	for (i = 2; i <= col_num; i++) {//윗변
		arr[1][i - 1] = arr[1][i];
	}
	for (i = 2; i <= row; i++) {//오른쪽
		arr[i - 1][col_num] = arr[i][col_num];
	}
	for (i = col_num - 1; i >= 1; i--) {//밑
		arr[row][i + 1] = arr[row][i];
	}
	arr[row][2] = 0;// 공기청정기에서 나온공기
	arr[row][1] = -1; // 공기청정해주기
}
void spread_dust(int row, int col) {
	int dust;
	int count = 0;

	dust = arr[row][col] / 5;

	if (row - 1 >= 1 && arr[row - 1][col]>-1) {
		spread[row - 1][col] += dust;
		count++;
	}
	if (col - 1 >= 1 && arr[row][col - 1]>-1) {
		spread[row][col - 1] += dust;
		count++;
	}
	if (row + 1 <= row_num && arr[row + 1][col]>-1) {
		spread[row + 1][col] += dust;
		count++;
	}
	if (col + 1 <= col_num && arr[row][col + 1]>-1) {
		spread[row][col + 1] += dust;
		count++;
	}
	arr[row][col] = arr[row][col] - count * dust;
}

void after_one_sec() {

	initial_spread();

	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			if (arr[i][j] > 0) {
				spread_dust(i, j);
			}
		}
	}
	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			arr[i][j] = arr[i][j] + spread[i][j];
		}
	}
	up_move();
	down_move();
}
void initial_spread() {
	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			spread[i][j] = 0;
		}
	}
}

int sum_arr() {

	int result = 0;

	for (int i = 1; i <= row_num; i++) {
		for (int j = 1; j <= col_num; j++) {
			if (arr[i][j] > 0) {
				result += arr[i][j];
			}
		}
	}
	return result;
}
