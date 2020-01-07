#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define MAX 999
using namespace std;

struct location {
	int row;
	int col;
};
bool CompareLocation(const location &x, const location &y);
void Comb( int now, int count, vector<location> chicken, vector <location> combo);
int BruteForce_dist(vector<location> combo);
int min_distance(int row, int col, vector<location>combo);

int max_chick;
int arr[50][50];
int min_dist=MAX;
vector<location> min_combo;
int arr_sized=0;

int main() {
	

	vector < location> chicken;
	location temp;
	vector < location> combo;


	cin >> arr_sized;
	cin >> max_chick;

	for (int i = 0; i < arr_sized; i++) {
		for (int j = 0; j < arr_sized; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				temp.row = i;
				temp.col = j;
				chicken.push_back(temp);
			}
		}
	}
	sort(chicken.begin(), chicken.end(), CompareLocation);
	Comb(-1,0, chicken,combo);
	cout << " min value : " << min_dist;
}
bool CompareLocation(const location &x, const location &y) {
	if (x.row == y.row) {
		return x.col < y.col;
	}
	else
		return x.row < y.row;
}
void Comb(int now,int count,vector<location> chicken,vector <location> combo) { // now 는 지금 까지뽑은 배열위치, count 는 몇개 뽑았는지, chicken 은 현재 좌표가 들어가있는 곳, 조합된 좌표를 위해 combi 라는 vector 를 하나 더 만듬.
	
	if (count == max_chick) {
		for (auto it = combo.begin(); it != combo.end(); it++) {
			cout << "(" << (*it).row << ",";
			cout << (*it).col << ") ";
		}
		cout << "\n";
		if (min_dist > BruteForce_dist(combo)){
			min_dist = BruteForce_dist(combo);
			min_combo = combo;
		}
		return;
	}
	for (int i = now+1; i < chicken.size(); i++) {
			combo.push_back(chicken[i]); // 일단 이자리를 대상으로 조합을 구할거다!
			Comb(i, count + 1, chicken, combo); //다음 자리로 넘어간다.
			combo.pop_back();
			count = combo.size();
	}
}
int BruteForce_dist(vector<location> combo) {
	int sum = 0;
	for (int i = 0; i < arr_sized; i++) {
		for (int j = 0; j < arr_sized; j++) {
			if (arr[i][j] == 1) {
				sum += min_distance(i, j, combo);
			}
		}
	}
	return sum;
}
int min_distance(int row, int col, vector<location>combo) {
	int min = MAX;
	int temp;

	for (auto it = combo.begin(); it != combo.end(); it++) {
		temp = abs((*it).row - row) + abs((*it).col - col);
		if (min > temp)
			min = temp;
	}
	return min;
}
