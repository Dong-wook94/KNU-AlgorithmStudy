#include <stdio.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int map[21][21];
int N;
int result = INT_MAX;


void devide(int x, int y, int d1, int d2) {
	vector<int> section_sum(5, 0); //0으로 초기화된 5개 
	int section[21][21] = {0,};
//	printf("\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (r < x + d1 && c <= y) {//1  1 ≤ r < x+d1, 1 ≤ c ≤ y
				section[r][c] = 1;
			}
			else if (r<=x+d2 && y<c) {//2 1 ≤ r ≤ x+d2, y < c ≤ N
				section[r][c] = 2;
			}
			else if (x + d1<=r && c < y - d1 + d2) {//3  x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
				section[r][c] = 3;
			}
			else if (x + d2 < r && y - d1 + d2 <= c) {//4  x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
				section[r][c] = 4;
			}
		}
	//printf("\n");
	}

	//경게선
	for (int i = 0; i <= d1; i++) {
		section[x + i][y - i] = 5;
		section[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		section[x + i][y + i] = 5;
		section[x + d1 + i][y - d1 + i] = 5;
	}

	//안쪽채우기
	for (int i = 0; i < d2; i++) {
		int t = 1;
		while (section[x + i + t][y + i] != 5) {
			section[x + i + t][y + i] = 5; 
			t++;
		}
	}
	for (int i = 0; i < d1; i++) {
		int t = 1;
		while (section[x + i + t][y - i] != 5) {
			section[x + i + t][y - i] = 5;
			t++;
		}
	}

	//printf("\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			//printf("%d ", section[r][c]);
			switch (section[r][c]) {
			case 1:
				section_sum[0] += map[r][c];
				break;
			case 2:
				section_sum[1] += map[r][c];
				break;
			case 3:
				section_sum[2] += map[r][c];
				break;
			case 4:
				section_sum[3] += map[r][c];
				break;
			case 5:
				section_sum[4] += map[r][c];
				break;
			}
		}
		//printf("\n");
	}
	sort(section_sum.begin(), section_sum.end());
	int gap = section_sum[4] - section_sum[0];
	//printf("gap : %d\n", gap);
	result = min(result, gap);

}

//(d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
void brute_force() {//전체탐색
	for (int d1 = 1; d1 <= N; d1++) {
		for (int d2 = 1; d2 <= N; d2++) {
			for (int x = 1; x < N; x++) {
				for (int y = 1; y < N; y++) {
					if ((x + d1 + d2 <= N) && (y - d1 >= 1) && (y + d2 <= N))
						devide(x, y, d1, d2);
				}
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <=N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	brute_force();
	printf("%d\n", result);
}