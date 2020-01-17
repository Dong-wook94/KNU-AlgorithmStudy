#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
/*
1. 조합을 이용하여 궁수배치하기
2. kill procss 진행
3. 최대수 갱신
*/
typedef struct Enemy {
	int row;
	int col;
	int distance;
	int choice = 0;
	Enemy(int r, int c) {
		row = r;
		col = c;
	}
}Enemy;

int N, M, limit;
int max_kill=0;
bool cmp(Enemy e1, Enemy e2) {
	return e1.col < e2.col;
}

int Game(int map[][16], vector<Enemy> enemies,vector<int> select) {
	int kill_cnt = 0;
	int castle_line = N;
	for (;enemies.size()>0;) {
		for (int i = 0; i < M; i++) {
			if (select[i] == 1) {
				int target=0;
				for (int j = 0; j < enemies.size(); j++) {
					enemies[j].distance = abs(castle_line - enemies[j].row) + abs(i - enemies[j].col);
					if (enemies[j].distance < enemies[target].distance) {
						target = j;
					}
				}
				if (enemies[target].distance <= limit)
					enemies[target].choice = 1;
			}
		}
		for (auto iter =enemies.begin(); iter!=enemies.end(); ) {
			if (iter->choice == 1) {
				iter = enemies.erase(iter);
				kill_cnt++;
			}
			else if (iter->choice == 0 && iter->row == castle_line - 1) {
				iter = enemies.erase(iter);
			}
			else {
				iter++;
			}
				
		}
		//printf("!!:%d\n", kill_cnt);
		castle_line--;
	}
	//printf("@@@@@\n",kill_cnt);
	return kill_cnt;
}

void combination(int map[][16],vector<Enemy> enemies) { //궁수뽑기
	vector<int> select;
	for (int i = 0; i < (M - 3); i++)
		select.push_back(0);
	for (int i = 0; i < 3; i++) {
		select.push_back(1);
	}
	do {
		max_kill = max(max_kill, Game(map, enemies, select));
	} while (next_permutation(select.begin(), select.end()));
}

int main() {
	int map[16][16];
	vector<Enemy> enemies;
	scanf("%d %d %d", &N, &M, &limit);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				enemies.push_back(Enemy(i, j));
				//enemies[enemies.size() - 1].choice = 0;
			}
		}
	}
	stable_sort(enemies.begin(), enemies.end(),cmp);
	combination(map,enemies);
	printf("%d\n", max_kill);
}