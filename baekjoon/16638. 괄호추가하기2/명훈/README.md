# 괄호추가하기2

## 문제 알고리즘

- dfs문제

## 풀이방법

1. dfs를 통한 괄호를 만들어준다.
2. 괄호를 다 했는 경우에는 다음의 순서에 따라서 진행한다
   1. 괄호를 먼저 계산한다.
   2. 곱셈을 그 후 계산한다.
   3. 최종 결과 값을 돌려준 다음, 최종값과 비교하면서 문제를 해결한다.

- 핵심 코드

~~~c++int board[MAX][MAX];						// array
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
~~~

## 문제 후 느낀점

- dfs 문제....
- 여전히 부족한 실력. 노력하자