#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>
using namespace std;

typedef struct Home {
	int row;
	int col;
	int distance;
	Home(){}
	Home(int r, int c) { row = r; col = c; }
}Home;

typedef struct Chicken {
	int row;
	int col;
	Chicken() {}
	Chicken(int r, int c) { row = r; col = c; }
}Chicken;

vector<Home> homes;
vector<Chicken> chickens;
int N, M;
int min_distance = INT_MAX;

vector<int> Select;
vector<Chicken> choiced;

int cal_distance() {
	int sum_dist = 0;
	for (int i = 0; i < homes.size(); i++) {
		homes[i].distance = INT_MAX;
		for (int j = 0; j < choiced.size();j++) {
			homes[i].distance = min(homes[i].distance, abs(homes[i].row - choiced[j].row) + abs(homes[i].col - choiced[j].col));
		}
		sum_dist += homes[i].distance;
	}
	return sum_dist;
}

void comb() {
	
	for (int i = 0; i < chickens.size()-M; i++)
		Select.push_back(0);
	for (int i = 0; i < M; i++)
		Select.push_back(1);
	do {
		choiced.clear();
		for (int i = 0; i < Select.size(); i++) {
			if (Select[i] == 1)
				choiced.push_back(chickens[i]);
		}
		min_distance = min(min_distance, cal_distance());
		
	} while (next_permutation(Select.begin(), Select.end()));
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int input;
			scanf("%d", &input);
			if (input == 1) {
				homes.push_back(Home(i, j));
			}
			else if (input == 2) {
				chickens.push_back(Chicken(i, j));
			}
		}
	}
	comb();
	printf("%d\n", min_distance);

}