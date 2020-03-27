# [2020카카오공채] 괄호 변환

## 문제 알고리즘
- 문제구현

## 풀이방법
- 문제에서 시키는대로 재귀함수 작성

- 핵심 코드
~~~c++
#include	<iostream>
#include	<string>
using namespace std;

// check 's' is balanced string
bool isCorrectBalanced(string s) {
	int lc = 0, rc = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(')	// (
			lc++;
		else				// )
			rc++;
		if (lc < rc)		// not balanced
			return false;
	}
	return true;
}

// get balanced substr 
string getSubString(string s) {
	int lc = 0, rc = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(')	// (
			lc++;
		else				// )
			rc++;
		if (lc == rc)		// if balanced
			break;
	}
	return s.substr(0, lc + rc);
}

// make correct & balanced String
string balancedString(string s) {
	string u = getSubString(s);
	string v = s.substr(u.length());
	if (s == "")
		return "";
	if (isCorrectBalanced(u))
		return (u + balancedString(v));
	else {
		string res = "";
		res += '(';
		res += balancedString(v);
		res += ')';
		string tu = u.substr(1, u.length() - 2);
		for (int i = 0; i < tu.length(); i++) {
			if (tu[i] == '(')
				tu[i] = ')';
			else
				tu[i] = '(';
		}
		res += tu;
		return res;
	}
}

string solution(string p) {
	if (p == "")
		return "";
	return balancedString(p);
}

int main() {
	cout << solution("(()())()") << "\n";
	cout << solution(")(") << "\n";
	cout << solution("()))((()") << "\n";

	return 0;
}
~~~

## 문제 후 느낀점
- 시키는대로 짤 수 있는 사람이 되자...


