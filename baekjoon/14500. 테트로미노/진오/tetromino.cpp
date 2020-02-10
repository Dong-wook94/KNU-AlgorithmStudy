#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[502][502] = { 0, };
int row_num;
int col_num;
int I_block();
int m_block();
int z_block();
int L_block();
int h_block();
int main() {
	int max = 0;
	vector <int> a;
	cin >> row_num;
	cin >> col_num;

	for (int i = 0; i < row_num; i++) {
		for (int j = 0; j < col_num; j++) {
			cin >> arr[i][j];
		}
	}
	a.push_back(I_block());
	a.push_back(m_block());
	a.push_back(z_block());
	a.push_back(L_block());
	a.push_back(h_block());

	sort(a.begin(), a.end());
	cout << a[4];
	
	/*cout << I_block();//+" "+m_block();//+" "+z_block()+" "+L_block()+" "+ h_block()
	cout << " ";
	cout << m_block();
	cout << " ";
	cout << z_block();
	cout << " ";
	cout << L_block();
	cout << " ";
	cout << h_block();*/

}
int I_block() { // 1자 블럭
	int max = 0;
	int temp = 0;

	for (int i = 0; i < row_num - 3; i++) {// 세로
		for (int j = 0; j < col_num; j++) {
			for (int k = 0; k < 4; k++) {
				temp += arr[i + k][j];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num; i++) {// 가로
		for (int j = 0; j < col_num - 3; j++) {
			for (int k = 0; k < 4; k++) {
				temp += arr[i][j + k];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	return max;
}
int m_block() { //ㅁ 블럭
	int max = 0;
	int temp = 0;
	for (int i = 0; i < row_num - 1; i++) {
		for (int j = 0; j < col_num - 1; j++) {
			for (int k = 0; k < 2; k++) {
				for (int m = 0; m < 2; m++) {
					temp += arr[i + k][j + m];
				}
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	return max;
}

int z_block() { //Z블럭
	int max = 0;
	int temp = 0;
	for (int i = 1; i < row_num; i++) {
		for (int j = 0; j < col_num - 2; j++) {
			for (int k = 0; k < 2; k++) {
				temp += arr[i - k][j + k];
				temp += arr[i - k][j + 1 + k];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 2; i < row_num; i++) {
		for (int j = 1; j < col_num; j++) {
			for (int k = 0; k < 2; k++) {
				temp += arr[i - k][j - k];
				temp += arr[i - k - 1][j - k];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	// 거울버전
	for (int i = 1; i < row_num; i++) {
		for (int j = 2; j < col_num ; j++) {
			for (int k = 0; k < 2; k++) {
				temp += arr[i - k][j - k];
				temp += arr[i - k][j + 1 - k];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 2; i < row_num; i++) {
		for (int j = 0; j < col_num-1; j++) {
			for (int k = 0; k < 2; k++) {
				temp += arr[i - k][j + k];
				temp += arr[i - k - 1][j + k];
			}
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}


	return max;
}
int L_block() { // L모양 블럭
	int max = 0;
	int temp = 0;

	for (int i = 0; i < row_num - 2; i++) {//L
		for (int j = 0; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i + 1][j];
			temp += arr[i + 2][j];
			temp += arr[i + 2][j+1];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}

	for (int i = 1; i < row_num; i++) {//ㅢ
		for (int j = 0; j < col_num - 2; j++) {
			temp += arr[i][j];
			temp += arr[i][j+1];
			temp += arr[i][j+2];
			temp += arr[i-1][j+2];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num-2; i++) {//ㄱ
		for (int j = 0; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i][j + 1];
			temp += arr[i+1][j + 1];
			temp += arr[i+2][j + 1];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 1; i < row_num ; i++) {//ㅣㅡ
		for (int j = 0; j < col_num - 2; j++) {
			temp += arr[i][j];
			temp += arr[i-1][j];
			temp += arr[i - 1][j + 1];
			temp += arr[i - 1][j + 2];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	// 거울모드
	for (int i = 0; i < row_num - 2; i++) {//ㅢ
		for (int j = 1; j < col_num ; j++) {
			temp += arr[i][j];
			temp += arr[i + 1][j];
			temp += arr[i + 2][j];
			temp += arr[i + 2][j-1];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}

	for (int i = 0; i < row_num-1; i++) {//ㄴ
		for (int j = 0; j < col_num - 2; j++) {
			temp += arr[i][j];
			temp += arr[i+1][j];
			temp += arr[i+1][j+1];
			temp += arr[i+1][j+2];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num-2; i++) {//ㅣㅡ
		for (int j = 0; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i][j + 1];
			temp += arr[i+1][j];
			temp += arr[i+2][j];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num -1; i++) {//ㄱ
		for (int j = 0; j < col_num - 2; j++) {
			temp += arr[i][j];
			temp += arr[i][j+1];
			temp += arr[i][j + 2];
			temp += arr[i + 1][j + 2];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}


	return max;
}
int h_block() { //ㅗ 블럭
	int max=0;
	int temp = 0;

	for (int i = 0; i < row_num - 1; i++) { //ㅜ
		for (int j = 0; j < col_num - 2; j++) {
			temp += arr[i][j];
			temp += arr[i][j + 1];
			temp += arr[i + 1][j + 1];
			temp += arr[i][j + 2];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 1; i < row_num-1; i++) { //ㅓ
		for (int j = 0; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i][j + 1];
			temp += arr[i - 1][j + 1];
			temp += arr[i+1][j + 1];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num - 1; i++) {//ㅗ
		for (int j = 1; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i+1][j];
			temp += arr[i + 1][j + 1];
			temp += arr[i+1][j -1];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	for (int i = 0; i < row_num - 2; i++) {//ㅏ
		for (int j = 1; j < col_num - 1; j++) {
			temp += arr[i][j];
			temp += arr[i + 1][j];
			temp += arr[i + 1][j + 1];
			temp += arr[i + 2][j];
			if (max < temp) {
				max = temp;
			}
			temp = 0;
		}
	}
	return max;
}