#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
int R, C, K;
vector<pair<int, int>> Num;//cnt,num
int num_cnt[101];
int map[101][101];
int max_row;
int max_col;
void order_map();
void OperRow();
void OperCol();

int main() {
	scanf("%d %d %d", &R, &C, &K);
	for (int i = 1; i <= 3; i++) {
		scanf("%d %d %d", &map[i][1], &map[i][2], &map[i][3]);
	}
	max_row = 3;
	max_col = 3;
	order_map();

}
void order_map() {
	int check = 0;
	for (int t = 0; t <= 100; t++) {
		if (map[R][C] == K) {
			printf("%d\n", t);
			return;
		}
		if (max_row >= max_col) {
			OperRow();
		}
		else {
			OperCol();
		}
	}
	printf("-1");

}
void OperRow() {
	for (int i = 1; i <= max_row; i++) {
		vector<pair<int, int>> Num;
		memset(num_cnt, 0, sizeof(num_cnt));
		for (int j = 1; j <= max_col; j++) {
			num_cnt[map[i][j]]++;
		}
		for (int j = 1; j <= 100; j++) {
			if (num_cnt[j] == 0)
				continue;
			Num.push_back(make_pair(num_cnt[j], j));
		}
		sort(Num.begin(), Num.end());
		for (int j = 1; j <= max_col; j++) {
			map[i][j] = 0;
		}
		int idx = 1;
		for (int j = 0; j < Num.size(); j++) {
			map[i][idx++] = Num[j].second;
			map[i][idx++] = Num[j].first;
		}
		idx--;
		if (max_col < idx) {
			max_col = idx;
			if (max_col > 100)
				max_col = 100;
		}
	}
}
void OperCol() {
	for (int j = 1; j <= max_col; j++) {
		vector<pair<int, int>> Num;
		memset(num_cnt, 0, sizeof(num_cnt));
		for (int i = 1; i <= max_row; i++) {
			num_cnt[map[i][j]]++;
		}
		for (int i = 1; i <= 100; i++) {
			if (num_cnt[i] == 0)
				continue;
			Num.push_back(make_pair(num_cnt[i], i));
		}
		sort(Num.begin(), Num.end());
		for (int i = 1; i <= max_row; i++) {
			map[i][j] = 0;
		}
		int idx = 1;
		for (int i = 0; i < Num.size(); i++) {
			map[idx++][j] = Num[i].second;
			map[idx++][j] = Num[i].first;
		}
		idx--;
		if (max_row < idx) {
			max_row = idx;
			if (max_row > 100)
				max_row = 100;
		}
	}
}