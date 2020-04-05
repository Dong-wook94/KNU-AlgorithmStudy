#include <string>
#include <vector>
#include <string>

using namespace std;
int solution(vector<vector<int>> board);

int main() {
	vector <vector <int>> board;
	int n;
	vector <int > temp;

	for (int i = 0; i < 10; i++) {
		cin >> n;
		temp.push_back(n);
		board.push_back(temp);
		for (int j = 1; j < 10; ++) {
			cin >> n;
			board[i].push_back(n);
		}

	}
	return 0;
}
int solution(vector<vector<int>> board) {
	int answer = 0;
	return answer;
}