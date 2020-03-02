#include <iostream>
#include <iostream>
using namespace std;

struct direct {
	int row;
	int col;
};
int arr[13][13];
int horse_arr[13][13][10] = { 0, };
int arr_siz;
int horse_num;
int horse_info[11][3];
int max_height = 0;
direct a[5]; //4방향
void init_direct();
void move();
void blue_block(int row, int col, int height, int ho_num);
void red_block(int row, int col, int height, int ho_num);
void white_block(int row, int col, int height, int ho_num);
void init_horse_arr();
int main() {
	init_direct();
	cin >> arr_siz;
	cin >> horse_num;
	int time = 0;
	for (int i = 1; i <= arr_siz; i++) {
		for (int j = 1; j <=arr_siz; j++) {
			cin >>arr[i][j];
		}
	}
	for (int i = 1; i <= horse_num; i++) {
		cin >> horse_info[i][0];// row
		cin >> horse_info[i][1]; //col
		cin >> horse_info[i][2];
	}
	init_horse_arr();
	while (1) {
		if (max_height >= 4) {
			break;
		}
		move();
		time++;
		if (time > 1000) {
			cout << -1;
			return 0;
		}
	}
	cout << time;
}
void init_direct(){
	a[1].row=0;
	a[1].col = 1;
	a[2].row = 0;
	a[2].col = -1;
	a[3].row = -1;
	a[3].col = 0;
	a[4].row = 1;
	a[4].col = 0;
}
void init_horse_arr() {
	int j;
	for (int i = 1; i <= horse_num; i++) {
		j = 0;
		while (horse_arr[horse_info[i][0]][horse_info[i][1]][j] != 0) {
			j++;
		}
		horse_arr[horse_info[i][0]][horse_info[i][1]][j] = i;
		if (j > max_height) {
			max_height = j;
		}
	}
}
void move() {
	int row;
	int col;
	int j;
	for (int i = 1; i <= horse_num; i++) {
		row=horse_info[i][0];
		col = horse_info[i][1];
		j = 0;
		while (horse_arr[row][col][j] !=i) {
			j++;
		}
		//horse_arr[row][col][j]; // 여기서 부터 윗말까지 영향
		if (row + a[horse_info[i][2]].row < 1 || col + a[horse_info[i][2]].col < 1 || row + a[horse_info[i][2]].row > arr_siz || col + a[horse_info[i][2]].col > arr_siz) {
			//blue
			blue_block(row, col, j,horse_arr[row][col][j]);
		}
		else if (arr[row + a[horse_info[i][2]].row][col + a[horse_info[i][2]].col] == 0)
		{//흰색
			white_block(row, col, j, horse_arr[row][col][j]);
		}
		else if (arr[row + a[horse_info[i][2]].row][col + a[horse_info[i][2]].col] == 1)
		{// 빨간색
			red_block(row, col, j, horse_arr[row][col][j]);
		}
		else {//파란색
			blue_block(row, col, j, horse_arr[row][col][j]);
		}

	}

}

void blue_block(int row, int col, int height, int ho_num) {
	int i = height;
	int j;
	int direct_row;
	int direct_col;

	if (horse_info[ho_num][2] %2 ==1) {
		horse_info[ho_num][2]+=1;
	}
	else if (horse_info[ho_num][2] % 2 == 0) {
		horse_info[ho_num][2] -= 1;
	}
	direct_row= a[horse_info[ho_num][2]].row;
	direct_col= a[horse_info[ho_num][2]].col;
	//옆칸이 블루인지 아닌지 추가적으로 확인 옆칸이넘어가는지도 확인해야함
	if (arr[row + direct_row][col + direct_col] ==2) {

	}
	else if (row + direct_row < 1 || row + direct_row > arr_siz || col + direct_col < 1 || col + direct_col > arr_siz) {

	}
	else {
		if (arr[row+direct_row][col + direct_col] == 0)
		{//흰색
			white_block(row, col, height, ho_num);
		}
		else if (arr[row + direct_row][col + direct_col] == 1)
		{// 빨간색
			red_block(row, col, height, ho_num);
		}
	}
}
void red_block(int row, int col, int height, int ho_num) {
	int i = height;

	int j;
	int direct_row = a[horse_info[ho_num][2]].row;
	int direct_col = a[horse_info[ho_num][2]].col;

	j = 0;
	for (j = 0; j < 10; j++) {
		if (horse_arr[row + direct_row][col + direct_col][j] == 0) {
			break;
		}
	}
	for (; i < 10; i++) {
		if (horse_arr[row][col][i] == 0) {
			i = i - 1;
			break;
		}
	}
	for (; i >= 0&&j<10;) {
		
		horse_arr[row + direct_row][col + direct_col][j] = horse_arr[row][col][i];
		horse_info[horse_arr[row][col][i]][0] = row + direct_row;
		horse_info[horse_arr[row][col][i]][1] = col + direct_col;
		
		
		if (horse_arr[row][col][i] == ho_num) {
			horse_arr[row][col][i] = 0;
			break;
		}
		horse_arr[row][col][i] = 0;
		i--;
		j++;
	} 
	if (j-1 > max_height) {
		max_height = j-1;
	}
}
void white_block(int row, int col, int height, int ho_num) {
	int i = height;

	int j;
	int direct_row = a[horse_info[ho_num][2]].row;
	int direct_col = a[horse_info[ho_num][2]].col;

	j = 0;
	for (j = 0; j < 10; j++) {
		if (horse_arr[row+direct_row][col + direct_col][j] == 0) {
			break;
		}
	}
	for (; i< 10 && j<10;) {
		if (horse_arr[row][col][i] == 0) {
			break;
		}
		horse_arr[row + direct_row][col + direct_col][j] = horse_arr[row][col][i];
		horse_info[horse_arr[row][col][i]][0] = row + direct_row;
		horse_info[horse_arr[row][col][i]][1] = col + direct_col;
		horse_arr[row][col][i] = 0;
		i++;
		j++;
	}
	if (j > max_height) {
		max_height = j;
	}
}
