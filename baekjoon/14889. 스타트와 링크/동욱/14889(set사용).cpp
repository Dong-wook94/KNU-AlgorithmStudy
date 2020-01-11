#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#include <limits.h>

using namespace std;
int info[21][21];

int N;//작수임 무조건
vector<int> team;
int result = INT_MAX;

int sum_team(set<int> t) {//팀의 시너지 합구하기
	int sum = 0;;
	for (auto iter = t.begin(); iter != t.end(); iter++) {
		for (auto iter2 = t.begin(); iter2 != t.end(); iter2++) {
			sum += info[*iter][*iter2];
		}
	}
	return sum;
}

void comb() {//조합으로 팀나누기
	for (int i = 0; i < N / 2; i++)
		team.push_back(0);
	for (int i = 0; i < N / 2; i++)
		team.push_back(1);

	do {
		int sumA=0, sumB=0;
		set<int> teamA, teamB;
		for (int i = 0; i < N; i++) {//set에 삽입
			if (team[i] == 0)
				teamA.insert(i);
			else 
				teamB.insert(i);
		}
		sumA = sum_team(teamA);
		sumB = sum_team(teamB);
		result = min(result, abs(sumA - sumB));//최솟값 갱신
	} while (next_permutation(team.begin(), team.end()));
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &info[i][j]);
		}
	}
	comb();
	printf("%d\n", result);
}