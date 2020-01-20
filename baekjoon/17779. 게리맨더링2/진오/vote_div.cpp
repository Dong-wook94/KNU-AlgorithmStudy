#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 99999
using namespace std;

int arr[21][21];
int back[21][21] = { 0, };
int arr_siz;
//vector <condition> cond;
vector <int> population;
int min_popul;

void div_sect(int x, int y, int d1, int d2);
void initial_back();
int div_popul(int div);
int solv_min();

struct condition {
	int x;
	int y;
	int d1;
	int d2;
};
int main() {

	min_popul = MAX;
	int temp;
	cin >> arr_siz;

	for (int i = 1; i <= arr_siz; i++) {
		for (int j = 1; j <= arr_siz; j++) {
			cin >> arr[i][j];
		}
	}
	for (int x = 1; x <= arr_siz; x++) {
		for (int y = 1; y <= arr_siz; y++) {
			for (int d1 = 1; d1 < arr_siz; d1++) {
				for (int d2 = 1; d2 < arr_siz; d2++) {
					if (x + d1 + d2 <= arr_siz && y + d2 <= arr_siz&&y-d1>=1) {
						div_sect(x, y, d1, d2);
						temp = solv_min();
						if (min_popul > temp) {
							min_popul = temp;
						}
					}
				}
			}
		}
	}

	cout << min_popul;
}
void div_sect(int x,int y,int d1, int d2) {
	initial_back();
	//1구역
	for (int i = 1; i < x + d1; i++) {
		if (i < x) {
			for (int j = 1; j <= y; j++) {
				back[i][j] = 1;
			}
		}
		else{
			for (int j = 1; j <= y-(i-x+1); j++) {
				back[i][j] = 1;
			}
		}
	}
	//2구역
	for (int i = 1; i <= x + d2; i++) {
		if (i < x) {
			for (int j = y + 1; j <= arr_siz; j++) {
				back[i][j] = 2;
			}
		}
		else {
			for (int j =y+1+(i-x) ; j <= arr_siz; j++) {
				back[i][j] = 2;
			}
		}
	}
	//3구역
	for (int i = x+d1; i <= arr_siz; i++) {
		if (i > x+d1 + d2) {
			for (int j = 1; j < y - d1 + d2; j++) {
				back[i][j] = 3;
			}
		}
		else {
			for (int j = 1; j < y - d1 + d2-(d2-(i-x-d1)); j++) {
				back[i][j] = 3;
			}
		}
	}
	//4구역
	for (int i = x+d2+1; i <=arr_siz; i++) {
		if (i >x+ d1 + d2) {
			for (int j = y - d1 + d2; j <= arr_siz; j++) {
				back[i][j] = 4;
			}
		}
		else {
			for (int j = y - d1 + d2+(d1-(i-x-d2-1)); j <= arr_siz; j++) {
				back[i][j] = 4;
			}
		}
	}
	for (int i = 1; i <= arr_siz; i++) {
		for (int j = 1; j <= arr_siz; j++) {
			if (back[i][j] == 0) {
				back[i][j] = 5;
			}
		}
	}
	//사이사이 에 5구역 끼워넣고 0이면 5로 하자
}
void initial_back() {
	for (int i = 1; i <= arr_siz; i++) {
		for (int j = 1; j <= arr_siz; j++) {
				back[i][j] = 0;
			
		}
	}
}
int div_popul(int div) {
	int sum=0;
	for (int i = 1; i <= arr_siz; i++) {
		for (int j = 1; j <= arr_siz; j++) {
			if (back[i][j] == div) {
				sum += arr[i][j];
			}
		}
	}
	return sum;
}
int solv_min() {
	population.clear();
	for (int i = 1; i <= 5; i++) {
		population.push_back(div_popul(i));
	}
	sort(population.begin(), population.end());
	return population[4] - population[0];
}