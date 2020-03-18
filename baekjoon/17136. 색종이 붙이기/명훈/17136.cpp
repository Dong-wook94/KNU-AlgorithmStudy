#include	<iostream>
#include	<algorithm>
using namespace std;

#define MAX 10
#define INF 999999999

int board[MAX][MAX];					// map
int confetti[6] = { 0, 5, 5, 5, 5, 5 };	// confetti count(count per paper)
int answer = INF, cnt = 0;					// answer

void dfs(int y, int x){
	// if line is end
	if (x == MAX) {
		dfs(y + 1, 0);
		return;
	}
	// end state
	if (y == MAX) {
		answer = min(answer, cnt);
		return;
	}
	// if board is empty, check the next position
	if (board[y][x] == 0) {
		dfs(y, x + 1);
		return;
	}

	// check all possibility (loop : len 5 -> 1)
	for (int l = 5; l >= 1; l--) {
		if (confetti[l] == 0 || y + l > MAX || x + l > MAX)
			continue;
		
		bool flag = false;
		for (int i = y; i < y + l; i++){
			for (int j = x; j < x + l; j++){
				if (board[i][j] == 0) {
					flag = true;
					break;
				}
			}
			if (flag == true)
				break;
		}
		if (flag == true)
			continue;

		confetti[l]--;
		cnt++;
		for (int i = y; i < y + l; i++)
			for (int j = x; j < x + l; j++)
				board[i][j] = 0;

		// efficient way
		dfs(y, x + l);

		for (int i = y; i < y + l; i++)
			for (int j = x; j < x + l; j++)
				board[i][j] = 1;
		cnt--;
		confetti[l]++;
	}
}

int main() {
	// input
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			scanf("%d", &board[i][j]);

	// solution
	dfs(0, 0);
	if (answer == INF)
		answer = -1;

	// output
	cout << answer << "\n";

	return 0;
}