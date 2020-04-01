#include	<iostream>
#include	<string>
#include	<vector>
#include	<algorithm>
#include	<climits>
using namespace std;

typedef long long ll;
#define MAX 20

int N;
ll max_score = LLONG_MIN;
char numstr[MAX];
bool bracket[MAX];

ll getCalculate(ll a, string op, ll b) {
	if (op == "+")	return a + b;
	if (op == "-")	return a - b;
	if (op == "*")	return a * b;
	return -1;
}

ll calculate() {
	vector<string> v1;
	vector<string> v2;
	// 괄호 먼저 계산
	for (int i = 0; i < N; ) {
		if (bracket[i]) {
			string str1 = "", str2 = "", op="";
			str1 += numstr[i];
			op += numstr[i + 1];
			str2 += numstr[i + 2];
			ll sol_num = getCalculate((ll)(stoi(str1)), op, (ll)(stoi(str2)));
			v1.push_back(to_string(sol_num));
			i += 3;
		}
		else {
			string str1 = "";
			str1 += numstr[i];
			v1.push_back(str1);
			i++;
		}
	}
	// 곱셈 먼저 계산
	for (int i = 0; i < v1.size(); ) {
		if (v1[i] == "*") {
			ll sol_num = getCalculate((ll)(stoi(v2[v2.size() - 1])), v1[i], (ll)(stoi(v1[i+1])));
			v2.pop_back();
			v2.push_back(to_string(sol_num));
			i += 2;
		}
		else {
			v2.push_back(v1[i]);
			i++;
		}
	}
	// 결과값 계산
	ll ans = (ll)(stoi(v2[0]));
	for (int i = 1; i < v2.size(); i+=2) {
		if (v2[i] == "+")	ans += stoi(v2[i + 1]);
		else if (v2[i] == "-")	ans -= stoi(v2[i + 1]);
	}
	return ans;
}

void dfs(int cnt) {
	if (cnt >= N) {
		max_score = max(max_score, calculate());
		return;
	}
	for (int i = cnt; i < N; i += 2) {
		if (i + 2 < N) {	// 괄호 체크
			if (!bracket[i] && !bracket[i + 2]) {
				bracket[i] = true;
				bracket[i + 2] = true;
				dfs(cnt + 2);
				bracket[i + 2] = false;
				bracket[i] = false;
			}
		}
		else {
			dfs(i + 1);
		}
	}
}

int main() {
	string line;
	// input
	cin >> N;
	cin >> line;
	for (int i = 0; i < N; i++)
		numstr[i] = line[i];

	// solution
	dfs(0);

	// output
	cout << max_score << "\n";
	return 0;
}
