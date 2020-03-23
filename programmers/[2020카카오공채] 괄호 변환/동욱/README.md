# [2020카카오공채] 문자열 압축

## 풀이

문제에서 요구한 조건대로 재귀 코드를 작성하면된다. 

## 소스코드

~~~c++
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


string divide_str(string str) {
	int cntl=0, cntr=0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			cntl++;
		else if (str[i] == ')')
			cntr++;
		if (cntr == cntl)
			break;
	}
	return str.substr(0, cntl + cntr);
}
bool check(string str){
	int cntl=0,cntr=0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			cntl++;
		else if (str[i] == ')')
			cntr++;
		if (cntr > cntl)
			return false;
	}
	return true;
}

string uv_routine(string str) {
	string u, v;
	u = divide_str(str);
	v = str.substr(u.length());
	if (str == "")
		return "";
	if (check(u)) {
		u +=uv_routine(v);
		//result += u;
		return u;
	}
	else {
		string result = "";
		result += "(";
		result += uv_routine(v);
		result += ")";
		u = u.substr(1, u.length() - 2);
		//reverse(u.begin(), u.end());
		for (auto iter = u.begin(); iter != u.end(); iter++) {
			if (*iter == '(') {
				*iter = ')';
			}
			else
				*iter = '(';
		}
		result += u;
		return result;
	}
	
	
}
string solution(string p) {
	string answer = "";
	string u, v;
	if (p.length() == 0)
		return answer;
	u = uv_routine(p);


	return u;
}
~~~

