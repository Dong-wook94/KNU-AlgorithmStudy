#include <stdio.h>
#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

int arr[11][11] = { 0, };
int map[11][11];
vector <int>tree[11][11];
int N; // 배열갯수
int M; // 나무갯수
int K; // 최종 년도
int x; // 나무위치
int y; //나무위치2
int z; //나이

void initialized_map();
void spring();
void eating_food(int i, int j);
void fall();
void spread_condition(int i, int j);
void spread(int i, int j, int k);
void winter();
int count_tree();
int main() {


	cin >> N;
	cin >> M;
	cin >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
	initialized_map();
	for (int i = 0; i < M; i++) {
		cin >> x;
		cin >> y;
		cin >> z;
		tree[x][y].push_back(z);
	}
	for (int i = 0; i < K; i++) {
		spring();
		fall();
		winter();
	}
	cout << count_tree();

}

void initialized_map() {
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++) {
			map[i][j] = 5;
		}
	}
}

void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!tree[i][j].empty()) { // tree 비었는지 확인
				eating_food(i, j);
			}
		}
	}
}
void eating_food(int i, int j) {
	int k;
	sort(tree[i][j].begin(), tree[i][j].end());
	for ( k = 0; k < tree[i][j].size(); k++) { // k 는 현재 어느것 까지먹었는지 나타냄
		if (map[i][j] - tree[i][j][k] >= 0) {
			map[i][j] = map[i][j] - tree[i][j][k];
			tree[i][j][k]++;
		}
		else {
			break;
		}
	}
	while (true) {
		if (tree[i][j].size() <= k) // k 보다 떨어져나간 지금이 작으면
		{
			break;
		}
		else {
			map[i][j] += tree[i][j].back() / 2;
			tree[i][j].pop_back();
		}
	}
}
void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!tree[i][j].empty()) { // tree 비었는지 확인
				spread_condition(i, j);
			}
		}
	}
}
void spread_condition(int i, int j) {
	sort(tree[i][j].begin(), tree[i][j].end());
	for (int k = 0; k < tree[i][j].size(); k++) { // k 는 현재 어느것 까지먹었는지 나타냄
		if (tree[i][j][k] % 5 == 0) {
			spread(i, j, k);
		}
	}
}
void spread(int i, int j, int k) {
	if (i - 1 >= 1 && j - 1 >= 1) {
		tree[i - 1][j - 1].push_back(1);
	}
	if (i - 1 >= 1 ) {
		tree[i - 1][j].push_back(1);
	}
	if (i-1 >= 1 && j + 1 <= N) {
		tree[i - 1][j + 1].push_back(1);
	}
	if ( j - 1 >=1) {
		tree[i][j - 1].push_back(1);
	}
	if ( j + 1 <= N) {
		tree[i][j + 1].push_back(1);
	}
	if (i + 1 <= N && j - 1 >= 1) {
		tree[i + 1][j - 1].push_back(1);
	}
	if (i + 1 <= N) {
		tree[i+1][j].push_back(1);
	}
	if (i + 1 <= N && j + 1 <= N) {
		tree[i + 1][j + 1].push_back(1);
	}
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += arr[i][j];
		}
	}
}
int count_tree() {
	int count=0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!tree[i][j].empty()) { // tree 비었는지 확인
				count += tree[i][j].size();
			}
		}
	}
	return count;
}