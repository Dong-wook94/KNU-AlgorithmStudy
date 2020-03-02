#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 101

struct counter {
	int index;
	int count;
};

vector <counter> sort_arr; //본체는 냅두고 이걸로만 소팅
vector <counter> init_arr; //sort arr init 용
int row_num; // 현재 최대 row 갯수
int col_num; // 현재 최대 col 갯수
int dest_row;// 목적지
int dest_col;
int dest_val;

int arr[MAX][MAX] = { 0, };
void make_init_arr();
bool Comp(counter a, counter b);
void swap_init_sort();
int row_calcul(int row);
int col_calcul(int col);
int calcul();
int main() {


	

	cin >> dest_row;
	cin >> dest_col;
	cin >> dest_val;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}
	row_num = 3;
	col_num = 3; 
	// 여기까지 setting
	
	cout << calcul();

}
int calcul() {
	int time = 0;
	int temp;
	int temp_col_num=0;
	int temp_row_num=0;
	while (arr[dest_row-1][dest_col-1] != dest_val) {
		
		time++;
		if (time > 100) {
			time = -1;
			break;
		}
		if (row_num >= col_num) {
			for (int i = 0; i < row_num; i++) {
				temp=row_calcul(i);
				if (temp > temp_col_num) {
					temp_col_num = temp;
				}
			}
			col_num = temp_col_num;
		}

		else if (row_num < col_num) {
			for (int i = 0; i < col_num; i++) {
				temp = col_calcul(i);
				if (temp > temp_row_num) {
					temp_row_num = temp;
				}
			}
			row_num = temp_row_num;
		}
	}
	return time;

}
int row_calcul(int row) { //change row_num 반환해서 큰걸로 rownum 교체 이럴거면 뒤에 0으로 안 초기화 시켜도 될거같은데..
	int change_col_num=0;
	int i = 0;
	int count = 0; // 이게 그걸로하자 그 머고 arr 위치
	swap_init_sort();
	for (int i = 0; i < col_num; i++) {
		sort_arr[arr[row][i]].count++; //arr에있는 내용물로 count 를 ++한다.
	}
	sort(sort_arr.begin(), sort_arr.end(), Comp);
	while (1) {
		if (i > MAX - 1) {
			break;
		}
		if (sort_arr[i].count != 0&&sort_arr[i].index!=0) {
			arr[row][count++] = sort_arr[i].index;
			arr[row][count++] = sort_arr[i].count;// 이렇게하면 기존에 있던부분을 수정 안해도 되는건가?
			change_col_num = count;
		}
		i++;
	}
	for (i = count; i < MAX; i++) {
		arr[row][i] = 0;
	}
	return change_col_num;
}
int col_calcul(int col) {
	int change_row_num = 0;
	int i = 0;
	int count = 0; // 이게 그걸로하자 그 머고 arr 위치
	swap_init_sort();
	for (i = 0; i < row_num; i++) {
		sort_arr[arr[i][col]].count++; //arr에있는 내용물로 count 를 ++한다.
	}
	sort(sort_arr.begin(), sort_arr.end(), Comp);
	i = 0;
	while(1){
		if (i > MAX - 1) {
			break;
		}
		if (sort_arr[i].count != 0 && sort_arr[i].index != 0) {
			arr[count++][col] = sort_arr[i].index;
			arr[count++][col] = sort_arr[i].count;// 이렇게하면 기존에 있던부분을 수정 안해도 되는건가?
			change_row_num = count;
		}
		i++;
		/*else {
			arr[i*2][col] = 0;
			arr[i*2+1][col] = 0;// 이렇게하면 기존에 있던부분을 수정 안해도 되는건가? 수정했다.
		}*/
	}
	for (i = count; i < MAX; i++) {
		arr[i][col] = 0;
	}
	return change_row_num;
}

bool Comp(counter a, counter b) {
	
	if (a.count == b.count) {
		return a.index<b.index;
	}
	else {
		return a.count < b.count;
	}

}
void make_init_arr() {
	counter temp;
	temp.count = 0;
	for (int i = 0; i < MAX; i++) {
		temp.index = i;
		init_arr.push_back(temp);
	}
	
}
void swap_init_sort() {
	init_arr.clear();
	make_init_arr();
	init_arr.swap(sort_arr);
}