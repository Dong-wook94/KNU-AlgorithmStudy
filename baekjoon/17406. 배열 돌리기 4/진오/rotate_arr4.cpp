#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int row_siz;
int col_siz;
int rotate_num;
int arr[51][51];
int back_up[51][51];
int rotate_arr[7][3] = { 0, };
void rotate(int row, int col, int count);
void move(int row, int col, int count);
void back_arr();
int min_val();

int main() {
	int N, M, K;
	int min = 999999;
	int temp;
	vector <int> perm;
	cin >> row_siz;
	cin >> col_siz;
	cin >> rotate_num;

	for (int i = 1; i <= row_siz; i++) {
		for (int j = 1; j <= col_siz; j++) {
			cin >> arr[i][j];
			back_up[i][j] = arr[i][j];
		}
	}
	for (int i = 1; i <= rotate_num;i++) {
		cin >> N;
		cin >> M;
		cin >> K;
		rotate_arr[i][0] = N;
		rotate_arr[i][1] = M;
		rotate_arr[i][2] = K;
		perm.push_back(i);
	}
	//move(rotate_arr[1][0], rotate_arr[1][1], rotate_arr[1][2]);
	
	do {

		for (int i = 0; i < perm.size(); i++) {
			move(rotate_arr[perm[i]][0], rotate_arr[perm[i]][1], rotate_arr[perm[i]][2]);
			
		}
		temp = min_val();
		if (min > temp) {
			min = temp;
		}
		back_arr();
		//여기서 최소값 구하고 백업한걸로 돌리기
		
	} while (next_permutation(perm.begin(), perm.end()));
	cout << min;
	return 0;

}
void back_arr() {
	for (int i = 1; i <= row_siz; i++) {
		for (int j = 1; j <= col_siz; j++) {
			arr[i][j] = back_up[i][j];
		}
	}
}
int min_val() {
	int min=99999;
	int sum=0;
	for (int i = 1; i <=row_siz; i++) {
		for (int j = 1; j <=col_siz; j++) {
			sum += arr[i][j];
		}
		if (min > sum) {
			min = sum;
		}
		sum = 0;
	}
	return min;
}
void move(int row, int col, int count) {
	while (count > 0) {
		rotate(row, col, count);
		count--;
	}
}
void rotate(int row, int col, int count) {
	int temp1;
	int temp2;
	//위쪽
	temp1 = arr[row - count][col-count];
	for (int i = col - count; i < col + count; i++) {
		temp2 = arr[row - count][i+1];
		arr[row - count][i + 1] = temp1;
		temp1 = temp2;
	}
	//오른쪽
	//temp1 = arr[row - count][col + count];
	for (int i = row - count; i < row + count; i++) {
		temp2 = arr[i+1][col+count];
		arr[i+1][col+count] = temp1;
		temp1 = temp2;
	}
	//아래쪽
	//temp1 = arr[row + count][col + count];
	for (int i = col + count; i > col - count; i--) {
		temp2 = arr[row+count][i-1];
		arr[row + count][i - 1] = temp1;
		temp1 = temp2;
	}
	//왼쪽
	//temp1 = arr[row + count][col - count];
	for (int i = row + count; i > row - count; i--) {
		temp2 = arr[i-1][col-count];
		arr[i - 1][col - count] = temp1;
		temp1 = temp2;
	}
	


}