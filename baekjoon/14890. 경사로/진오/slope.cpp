#include <iostream>

#define MAX 101
using namespace std;

int arr_siz;
int length;
int able_line = 0;
int arr[MAX][MAX];
int visit[MAX][MAX] = { 0, };
void check_line_row(int col);
int down_check_row(int row, int col);
int up_check_row(int row, int col);
void check_line_col(int row);
int down_check_col(int row, int col);
int up_check_col(int row, int col);
void visit_init();
int main() {

	cin >> arr_siz;
	cin >> length;
	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			cin>>arr[i][j];
		}
	}
	for (int i = 0; i < arr_siz; i++) {
		check_line_row(i);
	}
	visit_init();
	for (int i = 0; i < arr_siz; i++) {
		check_line_col(i);
	}
	cout << able_line;
}
void visit_init() {
	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			visit[i][j] = 0;
		}
	}
}
void check_line_row(int col) {
	int temp;
	int i;

	for (i = 0; i < arr_siz-1; i++) {
		if (arr[i][col] < arr[i + 1][col]) { //커지는것
			temp = up_check_row(i, col);
			if (temp != 0) {
				break;
			}
		}
		else if (arr[i][col] > arr[i + 1][col]) { // 작아지는것
			temp = down_check_row(i, col);
			if (temp != 0) {
				break;
			}
		}
	}
	if (i == arr_siz - 1) {
		able_line++;
	}
	//arr_siz-1 인지아닌지 확인하면 됨
}
int down_check_row(int row, int col) {// 밑으로 내려가는거 체크
	int flag = 0; // 옳은 상황

	if (row + length >= arr_siz) {
		flag = 1;
		return flag;
	}
	// 여기서 length++ 얼만큼 될지모르기때문에 그전에 미리 검사

	for (int i = 1; i <= length; i++) {
		
		if (arr[row][col] - 1 != arr[row + i][col]||visit[row+i][col]==1) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (int i = 1; i <= length; i++) {
			visit[row + i][col] = 1;
		}
	}
	return flag;

}
int up_check_row(int row, int col) {
	int flag = 0;

	//row +1 은 검사할 필요 없음 애초에 row -1 까지만 간다
	if (arr[row + 1][col] != arr[row][col]+1) {
		flag = 1;
		return flag;
	}
	//현재자리에 경사로가 놓아져 있는지
	if (visit[row][col] == 1) {
		flag = 1;
		return flag;
	}
	//여기서 length ++ 검사
	if (row - length+1< 0) {
		flag = 1;
		return flag;
	}

	for (int i = 1; i < length; i++) {
		if (arr[row][col] != arr[row - i][col] || visit[row-i][col] == 1) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (int i = 0; i < length; i++) {
			visit[row-i][col] = 1;
		}
	}
	return flag;
}

void check_line_col(int row) {
	int temp;
	int i;

	for (i = 0; i < arr_siz - 1; i++) {
		if (arr[row][i] < arr[row][i+1]) { //커지는것
			temp = up_check_col(row, i);
			if (temp != 0) {
				break;
			}
		}
		else if (arr[row][i] > arr[row][i+1]) { // 작아지는것
			temp = down_check_col(row, i);
			if (temp != 0) {
				break;
			}
		}
	}
	if (i == arr_siz - 1) {
		able_line++;
	}
	//arr_siz-1 인지아닌지 확인하면 됨
}
int down_check_col(int row, int col) {// 밑으로 내려가는거 체크
	int flag = 0; // 옳은 상황

	if (col + length >= arr_siz) {
		flag = 1;
		return flag;
	}
	// 여기서 length++ 얼만큼 될지모르기때문에 그전에 미리 검사

	for (int i = 1; i <= length; i++) {

		if (arr[row][col] - 1 != arr[row][col+i]||visit[row][col+i]) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (int i = 1; i <= length; i++) {
			visit[row][col+i] = 1;
		}
	}
	return flag;

}
int up_check_col(int row, int col) {
	int flag = 0;

	//row +1 은 검사할 필요 없음 애초에 row -1 까지만 간다
	if (arr[row][col+1] != arr[row][col] + 1) {
		flag = 1;
		return flag;
	}
	//여기서 경사로 놓았는지검사
	if (visit[row][col] == 1) {
		flag = 1;
		return flag;
	}
	//여기서 length ++ 검사
	if (col - length + 1< 0) {
		flag = 1;
		return flag;
	}
	for (int i = 1; i < length; i++) {
		if (arr[row][col] != arr[row][col-i]||visit[row][col-i]==1) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (int i = 0; i < length; i++) {
			visit[row][col-i] = 1;
		}
	}
	return flag;
}