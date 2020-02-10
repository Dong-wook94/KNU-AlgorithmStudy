#include <iostream>
#include <queue>
#include <cstdlib>
using namespace std;

int arr[52][52] = { 0, };
int visited[52][52] = { 0, };
int min_val;
int max_val;
int arr_siz;
struct location {
	int row;
	int col;
};
int connection(int i, int j);
void calcul();
void initial_visit();

int main() {
	int count = 0;
	int flag = 0;
	int temp;
	cin >> arr_siz;
	cin >> min_val;
	cin >> max_val;
	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			cin >> arr[i][j];
		}
	}
	while (1) {
		for (int i = 0; i < arr_siz; i++) {
			for (int j = 0; j < arr_siz; j++) {
				if (visited[i][j] == 0) {
					temp= connection(i, j);
					if (temp > 0) {
						flag = 1;
					}
					calcul();
				}
			}
		}
		if (flag == 0) {
			break;
		}
		else {
			count += 1;
		}
		flag = 0;
		initial_visit();
	}
	
	cout << count;
}
int connection(int i, int j) {
	queue<location> a; //현재 연결된 연합들의 값을 넣기 위해서
	location temp;
	location cur;
	int flag=0;

	temp.row = i;
	temp.col = j;

	a.push(temp);
	visited[temp.row][temp.col] = 1;

	while (!a.empty()) {
		cur = a.front();
		a.pop();
		
		temp.row = cur.row - 1; //위
		temp.col = cur.col;

		if (temp.row >= 0) {
			if (visited[temp.row][temp.col] == 0) {
				if (abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) >= min_val && abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) <= max_val) {
					a.push(temp);
					visited[temp.row][temp.col] = 1;
					flag = 1;
				}
			}
		}


		temp.row = cur.row + 1; //아래
		temp.col = cur.col;

		if (temp.row <arr_siz ) {
			if (visited[temp.row][temp.col] == 0) {
				if (abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) >= min_val && abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) <= max_val) {
					a.push(temp);
					visited[temp.row][temp.col] = 1;
					flag = 1;
				}
			}
		}

		temp.row = cur.row; //왼쪽
		temp.col = cur.col-1;

		if (temp.col >=0) {
			if (visited[temp.row][temp.col] == 0) {
				if (abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) >= min_val && abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) <= max_val) {
					a.push(temp);
					visited[temp.row][temp.col] = 1;
					flag = 1;
				}
			}
		}

		temp.row = cur.row; //오른쪽
		temp.col = cur.col + 1;

		if (temp.col < arr_siz) {
			if (visited[temp.row][temp.col] == 0) {
				if (abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) >= min_val && abs(arr[cur.row][cur.col] - arr[temp.row][temp.col]) <= max_val) {
					a.push(temp);
					visited[temp.row][temp.col] = 1;
					flag = 1;
				}
			}
		}
	}
	return flag;
}
void calcul() {
	int sum=0;
	int count=0;

	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			if (visited[i][j] == 1) {
				sum += arr[i][j];
				count++;
			}
		}
	}
	
	sum = sum / count;
	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			if (visited[i][j] == 1) {
				arr[i][j] = sum;
				visited[i][j] = 2;
			}
		}
	}
}

void initial_visit() {
	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			visited[i][j] = 0;
		}
	}
}