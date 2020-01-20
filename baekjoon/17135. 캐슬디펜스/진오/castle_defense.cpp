#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define MAX 999999
using namespace std;
int row_siz;
int col_siz;
int range;

int max_kill=0;
int arr[16][16];
int back[16][16];

void Comb(int now, int count, int archer, vector <int> combo);
int BruteForce_kill(vector<int> combo);
void shoot(int archer, int*row,int*col);
int check();
void move_onetime();
void rollback_arr();

int main() {

	vector <int> combo;

	cin >> row_siz;
	cin >> col_siz;
	cin >> range;
	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			cin >> arr[i][j];
			back[i][j]=arr[i][j];
		}
	}
	Comb(-1, 0, col_siz-1, combo); //1 ~ 5까지

	cout << max_kill;
}

void Comb(int now, int count, int archer, vector <int> combo) { // now 는 지금 까지뽑은 배열위치, count 는 몇개 뽑았는지, chicken 은 현재 좌표가 들어가있는 곳, 조합된 좌표를 위해 combi 라는 vector 를 하나 더 만듬.
	int temp;

	if (count == 3) {
		temp=BruteForce_kill(combo);
		if (max_kill < temp) {
			max_kill = temp;
		}
		rollback_arr();
		
		return;
	}
	for (int i = now + 1; i <= archer; i++) {
		combo.push_back(i); // 일단 이자리를 대상으로 조합을 구할거다!
		Comb(i, count + 1, archer, combo); //다음 자리로 넘어간다.
		combo.pop_back();
		count = combo.size();
	}
}

int BruteForce_kill(vector<int> combo) {
	int firstrow;	
	int firstcol;
	int secondrow;
	int secondcol;
	int thirdrow;
	int thirdcol;
	int first=combo[0];
	int second = combo[1];
	int third= combo[2];
	int killcount = 0;

	while (check()>0) {

		shoot(first, &firstrow, &firstcol);
		shoot(second, &secondrow, &secondcol);
		shoot(third, &thirdrow, &thirdcol);
		if (firstrow >= 0 && firstcol >= 0) {
			if (arr[firstrow][firstcol] > 0) {
				arr[firstrow][firstcol] = 0;
				killcount++;
			}
		}
		if (secondrow >= 0 && secondcol >= 0) {
			if (arr[secondrow][secondcol] > 0) {
				arr[secondrow][secondcol] = 0;
				killcount++;
			}
		}
		if (thirdrow >= 0 && thirdcol >= 0) {
			if (arr[thirdrow][thirdcol] > 0) {
				arr[thirdrow][thirdcol] = 0;
				killcount++;
			}
		}
		move_onetime();
	}
	return killcount;
}
void shoot(int archer,int *row, int *col) { // 쏠 위치를 row col 에 저장해서 보내자
	
	int min = MAX;
	int temp=0;
	int flag = 0;

	*row = -1;// 없는경우를 가정
	*col = -1;
	
	for (int i = row_siz-1; i>= 0; i--) { // 0부터 배열 시작
		for (int j = 0; j < col_siz; j++) {
			if (arr[i][j] > 0) {
				temp = abs(i - row_siz) + abs(j - archer);
				if (min > temp&&temp<=range) {
					min = temp;
					*row = i;
					*col = j;
				}
				else if (min == temp && temp <= range && (*col) > j) {
					*row = i;
					*col = j;
				}
			}
		}
		if (range < row_siz - i) { // 직선조차 초과해버리면 더이상 돌릴 이유 없음
			break;
		}
	}
}
void move_onetime() {

	for (int i = row_siz-2; i >=0; i--) {//첫번째 칸은 따로 초기화 해줘야됨
		for (int j = 0; j < col_siz; j++) {
			arr[i + 1][j] = arr[i][j];
		}
	}
	for (int j = 0; j < col_siz; j++) {
		arr[0][j] = 0;
	}
}
int check() {

	int result = 0; 
	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			if (arr[i][j] > 0) {
				result = 1;
			}
		}
	}
	return result;
}
void rollback_arr() {
	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			arr[i][j] = back[i][j];
		}
	}
}