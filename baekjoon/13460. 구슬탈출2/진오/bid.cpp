#include <iostream>
#include <vector>

#define MAX 11
using namespace std;

struct state {
	int red_row;
	int red_col;
	int blue_row;
	int blue_col;
	int dir; //1 오른쪽 2 밑 3 왼쪽 4 위
};
struct direction {
	int row;
	int col;
};



int flag = 0; // 1되면 끝
int push_row;
int push_col;
vector <state> state_arr; //cur_state 쌓기
direction a[5]; // dir 기반 방향찾기


int row_siz;
int col_siz;
int arr[MAX][MAX]; // 구슬은 2으로 받고, 벽은 1로받자, 움직이는건 0 구멍은 3
state cur_state;

void move();
int go_right(int row, int col, int dir);
int go_down(int row, int col, int dir);
int go_left(int row, int col, int dir);
int go_up(int row, int col, int dir);
void initial_direction();

int main() {
	char temp;
	int time = 0;
	cin >> row_siz;
	cin >> col_siz;

	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			cin >> temp;
			if (temp == '#') {
				arr[i][j] = 1;
			}
			else if (temp == '.') {
				arr[i][j] = 0;
			}
			else if (temp == 'O') {
				arr[i][j] = 3;
			}
			else if (temp == 'B') {
				arr[i][j] = 2;
				cur_state.blue_row = i;
				cur_state.blue_col = j;
			}
			else if (temp == 'R') {
				arr[i][j] = 2;
				cur_state.red_row = i;
				cur_state.red_col = j;
			}
		}
	}
	cur_state.dir = 1;// cur state 초기화 완료
	initial_direction();
	move();
	time = state_arr.size();
	cout << time;
	return 0;
}

 void move() {
	state temp;
	state push_temp;// 넣을거
	int count = 0; //움직였는지
	int vector_find = 0;
	state_arr.push_back(cur_state);
	
	while (!state_arr.empty()) {
		
		temp=state_arr.back();
		state_arr.pop_back(); //꺼내고
		//////////////////////////////////여기서 방향보고 합시다 4까지인지 검사하기
		push_temp = temp;
		if (temp.dir < 4) {
			push_temp.dir = push_temp.dir + 1; //다시 dir +1 해서 넣어놓기
			//state_arr.push_back(push_temp);
			for (int i = 0; i < state_arr.size(); i++) {
				if (state_arr[i].blue_row == push_temp.blue_row&&state_arr[i].blue_col == push_temp.blue_col&&state_arr[i].red_row == push_temp.red_row&&state_arr[i].red_col == push_temp.red_col) {
					vector_find = 1;
				}
				else {

				}
			}
			if (vector_find == 0) {
				state_arr.push_back(push_temp);
			}
		}
		vector_find = 0;
		switch (temp.dir) {
		case 1: // 얘가 오른쪽
			if (temp.blue_col > temp.red_col) {
				
				count=count+go_right(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				count = count + go_right(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				push_temp.dir = 1;
			}
			else {
				count = count + go_right(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				count = count + go_right(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				push_temp.dir = 1;
			}
			break;
		case 2://밑
			if (temp.blue_row > temp.red_row) {
				count = count + go_down(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				count = count + go_down(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				push_temp.dir = 1;
			}
			else {
				count = count + go_down(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				count = count + go_down(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				push_temp.dir = 1;
			}
			break;
		case 3://왼쪽
			if (temp.blue_col < temp.red_col) {
				count = count + go_left(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				count = count + go_left(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				push_temp.dir = 1;
			}
			else {
				count = count + go_left(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				count = count + go_left(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				push_temp.dir = 1;
			}
			break;
		case 4://위
			if (temp.blue_row < temp.red_row) {
				count = count + go_up(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				count = count + go_up(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				push_temp.dir = 1;
			}
			else {
				count = count + go_up(temp.red_row, temp.red_col, temp.dir);
				push_temp.red_row = push_row;
				push_temp.red_col = push_col;
				count = count + go_up(temp.blue_row, temp.blue_col, temp.dir);
				push_temp.blue_row = push_row;
				push_temp.blue_col = push_col;
				push_temp.dir = 1;
			}
			break;
		}
		//
		if (flag == 1) {
			break;
		}
		if (count > 0) {
			for (int i = 0; i < state_arr.size(); i++) {
				if (state_arr[i].blue_row == push_temp.blue_row&&state_arr[i].blue_col == push_temp.blue_col&&state_arr[i].red_row == push_temp.red_row&&state_arr[i].red_col == push_temp.red_col) {
					vector_find = 1;
				}
				else {
					
				}
			}
			if (vector_find == 0) {
				state_arr.push_back(push_temp);
			}
		}


		count = 0;
		vector_find = 0;
	}
	//stack 사용
	//빨강 파랑구슬 위치비교
}

int go_right(int row, int col, int dir) {
	int i;
	int j;

	int count = 0;
	//count 랑 vector 확인 후에 push

	i = row;
	j = col;
	arr[i][j] = 0;
	for (;j < col_siz;) {
		
		i = i + a[dir].row;
		j = j + a[dir].col;
		if (arr[i][j] != 0) {
			break;
		}
		count++;
	}
	//범위넘어갈때
	
	//3일때
	if (arr[i][j] == 3)
		flag = 1; // 끝남;
	else {
		j = j - 1;
	}
	push_row = i;
	push_col = j;
	arr[i][j] = 2;
	return count;
	//벽에 부딪혓을때는 따로 안해도 될듯
}
int go_down(int row, int col, int dir) {
	int i;
	int j;
	int count = 0;
	i = row;
	j = col;
	arr[i][j] = 0;
	for (; i < row_siz;) {
		
		i = i + a[dir].row;
		j = j + a[dir].col;
		if (arr[i][j] != 0) {
			break;
		}
		count++;
	}
	//범위넘어갈때
	if (arr[i][j] == 3)
		flag = 1; // 끝남;
	else {
		i = i - 1;
	}
	push_row = i;
	push_col = j;
	arr[i][j] = 2;
	return count;
}
int go_left(int row, int col, int dir) {
	int i;
	int j;
	int count = 0;
	i = row;
	j = col;
	arr[i][j] = 0;
	for (; j >= 0;) {
		
		i = i + a[dir].row;
		j = j + a[dir].col;
		if (arr[i][j] != 0) {
			break;
		}
		count++;
	}
	//범위넘어갈때
	if (j < 0) {
		j = 0;
	}
	//3일때
	if (arr[i][j] == 3)
		flag = 1; // 끝남;
	else {
		j = j+1;
	}
	push_row = i;
	push_col = j;
	arr[i][j] = 2;
	return count;
}
int go_up(int row, int col, int dir) {
	int i;
	int j;
	int count = 0;
	i = row;
	j = col;
	arr[i][j] = 0;
	for (; i >= 0;) {
		
		i = i + a[dir].row;
		j = j + a[dir].col;
		if (arr[i][j] != 0) {
			break;
		}
		count++;
	}
	//범위넘어갈때
	if (i < 0) {
		i = 0;
	}
	//3일때
	if (arr[i][j] == 3)
		flag = 1; // 끝남;
	else {
		i = i + 1;
	}
	push_row = i;
	push_col = j;
	arr[i][j] = 2;
	return count;
}
void initial_direction(){
	a[1].row=0;
	a[1].col=1;
	a[2].row=1;
	a[2].col=0;
	a[3].row=0;
	a[3].col=-1;
	a[4].row=-1;
	a[4].col=0;
}