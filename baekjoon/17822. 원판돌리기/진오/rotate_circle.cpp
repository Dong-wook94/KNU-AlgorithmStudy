#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

deque < deque< int > > circle; // 원판정보 저장
int circle_num; // 원판갯수
int circle_size; // 원판사이즈
int rotate_num; // 돌리는횟수

void rotate_func(int number, int direct, int count);
void clockwise_rotate(int i);
void counterwise_rotate(int i);
void initialized_navi();
void dfs(int row, int col);
void initial_visit();
void del_val();
int sum_val();
void process();
int survived_count();
int checked_visited();
struct location {
	int row;
	int col;
};

vector<location> stk;
location navi[4];
int visited[51][51] = { 0, };

int main() {

	deque<int> temp; //원판 정보 임시저장
	int	info[3]; // 숫자들 임시저장
	int element;

	cin >> circle_num;
	cin >> circle_size;
	cin >> rotate_num;
	for (int i = 0; i < circle_size; i++) {
		temp.push_back(0);
	} 
	circle.push_back(temp);
	temp.clear();
	//1번원판부터 시작하기때문에 0번 원판 채움
	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			cin >> element;
			temp.push_back(element);
		}
		circle.push_back(temp);
		temp.clear();
	}
	for (int i = 0; i < rotate_num; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> info[j];
		}
		rotate_func(info[0], info[1], info[2]);
		initial_visit();
		for (int i = 1; i <= circle_num; i++) {
			for (int j = 0; j < circle_size; j++) {
				dfs(i, j);
			}
		}
		if (checked_visited() == 1) {
			del_val();
		}
		else {
			process();
		}
	}
	cout << sum_val();

} 
void del_val() {
	
	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			if (visited[i][j] == 2) {
				circle[i][j] = 0;
			}
		}
	}
}
void process() {

	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			if (circle[i][j] > 0) {
				if (float(circle[i][j]) > float(sum_val()) / float(survived_count())) {
					circle[i][j] = circle[i][j] - 1;
				}
				else {
					circle[i][j] = circle[i][j] + 1;
				}
			}
		}
	}
	
}
int survived_count() {
	int count=0;
	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			if (visited[i][j] == 2) {
				count++;
			}
		}
	}
	return count;
}
int checked_visited() {// flag 가 1이면 인접점 존재 0이면 없음
	int flag=0;

	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			if (visited[i][j] == 2) {
				flag = 1;
			}
		}
	}
	return flag;
}
int sum_val() {
	int sum = 0;

	for (int i = 1; i <= circle_num; i++) {
		for (int j = 0; j < circle_size; j++) {
			sum += circle[i][j];
		}
	}
	return sum;
}

void rotate_func(int number,int direct,int count) {// 회전후 삭제 까지 담당
	//direct 0 시계방향, direct 1 반시계방향
	switch (direct) {
		case 0:
			for (int i = 1; i <= circle_num; i++) {
				if (i%number == 0) {
					for (int j = 0; j < count; j++) {
						clockwise_rotate(i);
					}
				}
			}
			break;
		case 1:
			for (int i = 1; i <= circle_size; i++) {
				if (i%number == 0) {
					for (int j = 0; j < count; j++) {
						counterwise_rotate(i);
					}
				}
			}
			break;
		default:
			cout << "rotate error\n";
			break;
	}
}

void clockwise_rotate(int i) { // 정시계방향 회전
	int temp;
	temp = circle[i].back();
	circle[i].pop_back();
	circle[i].push_front(temp);
}
void counterwise_rotate(int i) { // 반시계방향 회전
	int temp;
	temp = circle[i].front();
	circle[i].pop_front();
	circle[i].push_back(temp);
}
void dfs(int row, int col) {
	
	location temp;
	location move;
	int flag = 0; //현재 stack 을 pop 시킬지 말지 결정
	initialized_navi();
	if (visited[row][col] == 0) {

		stk.push_back({ row,col });
		visited[row][col] = 1;
		while (!stk.empty()) {
			temp = stk.back();

			for (int i = 0; i < 4; i++) {
				move.row = temp.row + navi[i].row;
				move.col = temp.col + navi[i].col;
				if (move.col < 0) {
					move.col = circle_size - 1;
				}
				if (move.col >= circle_size) {
					move.col = 1;
				}
				if (move.row <= circle_num && move.row >= 1) {
					if (visited[move.row][move.col] == 0 && circle[move.row][move.col] == circle[temp.row][temp.col]) {
						stk.push_back(move);
						visited[move.row][move.col] = 2;
						if (visited[temp.row][temp.col] == 1) {
							visited[temp.row][temp.col] = 2;
						}
						flag = 1;
					}
				}
			}
			if (flag == 0) {
				stk.pop_back();
			}
			flag = 0;
		}

	}
}

void initialized_navi() {
	navi[0].row = -1;
	navi[0].col = 0;
	navi[1].row = 0;
	navi[1].col = 1;
	navi[2].row = 1;
	navi[2].col = 0;
	navi[3].row = 0;
	navi[3].col = -1;

}
void initial_visit() {
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			visited[i][j] = 0;
		}
	}
}