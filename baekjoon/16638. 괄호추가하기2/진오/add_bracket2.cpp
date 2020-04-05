
// 미완성

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <char> operation;
vector <int> num;
int str_len;
int answer = 0;

void solve(int result, int nowOpIdx);
int calc(char op, int n1, int n2);

int main() {
	string s;

	cin >> str_len;
	cin >> s;


	for (int i = 0; i < str_len; i++) {
		if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
			num.push_back(s[i] - '0');
		}
		else operation.push_back(s[i]);
	}
	solve(num[0], 0);
	cout << answer;
}
void solve(int result, int nowOpIdx) {
	if (nowOpIdx >= operation.size()) {
		if (answer < result)
			answer = result;
		return;
	}
	int res1 = calc(operation[nowOpIdx], result, num[nowOpIdx + 1]);
	solve(res1, nowOpIdx + 1);

	if (nowOpIdx + 2 < operation.size()) {
		int res2 = calc(operation[nowOpIdx + 1], num[nowOpIdx + 1], num[nowOpIdx + 2]);
		res2 = calc(operation[nowOpIdx], result, res2);
		solve(res2, nowOpIdx + 2);
	}
}

int calc(char op, int n1, int n2) {
	if (op == '+')
		return n1 + n2;
	else if (op == '-')
		return n1 - n2;
	else
		return n1 * n2;
}

// 참조 사이트 :https://it-earth.tistory.com/72
//dfs 인 것 까지는 알았는데 구현에 어려움이있어 참조
//미완성
/*
void solve(int result, int nowOpIdx) {
	if (nowOpIdx >= operation.size()) {
		if (answer < result)
			answer = result;
		return;
	}
	int res1 = calc(operation[nowOpIdx], result, num[nowOpIdx + 1]);
	solve(res1, nowOpIdx + 1);

	if (nowOpIdx + 1 < operation.size()) {
		int res2 = calc(operation[nowOpIdx + 1], num[nowOpIdx + 1], num[nowOpIdx + 2]);
		solve(calc(operation[nowOpIdx], result, res2), nowOpIdx + 2);
	}
}
int calc(char op, int n1, int n2) {
	if (op == '+')
		return n1 + n2;
	else if (op == '-')
		return n1 - n2;
	else
		return n1 * n2;
}
*/