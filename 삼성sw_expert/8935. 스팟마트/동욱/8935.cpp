#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int numN;
int numM;
int N[3001];
int M[101];
int dp[3001][101][101][2];

bool cmp_desc(const int a, const int b) {
	return a > b;
}


int findMaxResult(int iterN, int iter_selectedM, int iter_passM, int selected) {
	//끝
	if (iterN >= numN && (iter_selectedM + iter_passM) >= numM)
		return 0;
	int &result = dp[iterN][iter_selectedM][iter_passM][selected]; //result로 별칭
	if (result != 0) //이미계산한곳
		return result;
	if (selected) {//여기가 선택됐을때
		if (iterN < numN) { //뒤에 선택안하고 뒤에 N올때
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//뒤에 선택안하고 뒤에 M올때
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	else {//여기가 선택 안됐을때
		if (iterN < numN) {//뒤에 N올때
			//뒤에 선택
			result = max(result, N[iterN] + findMaxResult(iterN + 1, iter_selectedM, iter_passM, 1));
			//뒤에 선택안함
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//뒤에 M올때
			//뒤에 선택
			result = max(result, M[iter_selectedM] + findMaxResult(iterN, iter_selectedM + 1, iter_passM, 1));
			//뒤에 선택안함
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	return result;
}

int Testcase() {

	scanf("%d", &numN);
	for (int i = 0; i < numN; i++) {
		scanf("%d", &N[i]);
	}
	scanf("%d", &numM);
	for (int i = 0; i < numM; i++) {
		scanf("%d", &M[i]);
	}
	for (int i = 0; i <=numN; i++) {
		for (int j = 0; j <= numM; j++) {
			for (int k = 0; k <= numM; k++) {
				dp[i][j][k][0] = dp[i][j][k][1] = 0;
			}
		}
	}
	sort(M, M + numM, cmp_desc);
	return findMaxResult(0, 0, 0, 0);
}

int main() {
	int testcase;
	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		printf("#%d %d\n", t, Testcase());
	}
}