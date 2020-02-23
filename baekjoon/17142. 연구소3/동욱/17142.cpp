#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

typedef struct Virus {
	int row;
	int col;
	int time;
	Virus() {};
	Virus(int rr, int cc, int tt) {
		row = rr;
		col = cc;
		time = tt;
	}
};
queue<Virus> q;
int visited[51][51];
int map_size, n_acvirus;
int map[51][51];
int temp_map[51][51];
vector<Virus> virus;
int Spread_Virus();
void Select_Virus();
int check0();
void copyMap(int m[][51], int tpm[][51]);
int dir_row[4] = { 0,1,0,-1 };
int dir_col[4] = { 1,0,-1,0 };
int min_time = 99999;
int main() {
	//input
	scanf("%d %d", &map_size, &n_acvirus);
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
				virus.push_back(Virus(i, j, 0));
		}
	}
	Select_Virus();
	if (min_time == 99999)
		min_time = -1;
	printf("%d\n", min_time);
	
}
int Spread_Virus() {
	Virus cur,next;

	int max_time = 0;
	copyMap(map, temp_map);

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			next.row = cur.row + dir_row[i];
			next.col = cur.col + dir_col[i];
			
			if (next.row >= 0 && next.col >= 0 && next.row < map_size&&next.col < map_size&&visited[next.row][next.col] == 0) {
				if (temp_map[next.row][next.col] != 1) {
					temp_map[next.row][next.col] = 2;
					visited[next.row][next.col] = 1;
					next.time = cur.time + 1;
					if (max_time < next.time&&map[next.row][next.col]==0)
						max_time = next.time;
					q.push(next);
				}
			}
		}
	}
	return max_time;
}
void Select_Virus() {
	vector<int> select;
	int time=-1;
	int check = 0;
	for (int i = 0; i < n_acvirus; i++)
		select.push_back(1);
	for (int i = 0; i < (virus.size() - n_acvirus); i++)
		select.push_back(0);
	sort(select.begin(), select.end());

	do {
		for (int i = 0; i < map_size; i++) {
			memset(visited[i], 0, sizeof(int)*map_size);
		}
		for (int i = 0; i < select.size(); i++) {
			if (select[i] == 1) {
				visited[virus[i].row][virus[i].col] = 1;
				q.push(virus[i]);
			}
		}
		time = Spread_Virus();
		check = check0();
		if (time < min_time&&check != 0) {
			min_time = time;
		}
	} while (next_permutation(select.begin(), select.end()));
}
void copyMap(int m[][51],int tpm[][51]) {
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			tpm[i][j] = m[i][j];
		}
	}
}

int check0(){
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (temp_map[i][j] == 0)
				return 0;
		}
	}
	return 1;
}