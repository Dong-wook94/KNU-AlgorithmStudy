#include <stdio.h>
#include <map>
#include <algorithm>
#include <queue>
#include <string>
#include <iostream>
#define GOAL 123456789
using namespace std;

map<int, int> distances; //퍼즐 각모양별 최소 distances
queue<int> q;
int dir_row[4] = { 1,0,-1,0 };
int dir_col[4] = { 0,-1,0,1 };

bool isRange(int r, int c) {
	if (r < 0 || r >= 3 || c < 0 || c >= 3)
		return false;
	return true;
}

void bfs() {
	while (!q.empty()) {
		int state = q.front();
		//cout << q.size()<<","<<distances.size()<< endl;
		q.pop();
		if (state == GOAL) {
			printf("%d\n", distances.find(state)->second);
			return;
		}
		string str = to_string(state);
		int cur_pos = str.find('9');
		int row = cur_pos / 3;
		int col = cur_pos % 3;
		for (int i = 0; i < 4; i++) {
			int next_row = row + dir_row[i];
			int next_col = col + dir_col[i];
			if (isRange(next_row, next_col)) {
				int next_pos = next_row * 3 + next_col;
				string next_state_str = str;
				swap(next_state_str[cur_pos], next_state_str[next_pos]);
				int next_state = stoi(next_state_str);
				auto cur_dist = distances.find(state)->second;
				auto iter = distances.find(next_state);
				if (iter == distances.end()) { //방문체크
					distances.insert(make_pair(next_state, cur_dist + 1));
					q.push(next_state);
				}
			}
		}
	}
	printf("-1\n");
}

int main() {
	int puzzle = 0;
	for (int i = 0; i < 9; i++) {
		int input;
		scanf("%d", &input);
		if (input == 0)
			input = 9;
		puzzle = puzzle * 10 + input;
	}
	distances.insert(make_pair(puzzle, 0));
	q.push(puzzle);
	bfs();
}