#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string divide_str(string str) {
	int cntl = 0, cntr = 0;
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
bool check(string str) {
	int cntl = 0, cntr = 0;
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
		u += uv_routine(v);
		return u;
	}
	else {
		string result = "";
		result += "(";
		result += uv_routine(v);
		result += ")";
		u = u.substr(1, u.length() - 2);
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