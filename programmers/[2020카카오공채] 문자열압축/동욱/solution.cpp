#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int unit_mapping(string str, int unit) {
	string result = "";
	int same_cnt = 1;
	for (int i = 0; i < str.length(); ) {
		int cnt = 0;

		for (int j = 0; j < unit; j++) {
			if (i + (same_cnt*unit) + j > str.length()) break;
			if (str[i + j] == str[i + (same_cnt*unit) + j])
				cnt++;
			else break;//일치하지 않는다면
		}
		if (cnt == unit) { //일치하는 경우
			same_cnt++;
		}
		else {
			if (same_cnt == 1) {
				result += str.substr(i, unit);
				i += unit;
			}
			else {
				string int_str = to_string(same_cnt);
				result += int_str;
				result += str.substr(i, unit);
				i = i + same_cnt * unit;
				same_cnt = 1;
			}

		}
	}
	//cout << result << endl;
	return result.size();
}


int solution(string s) {
	int min_size = INT_MAX;
	int size = 0;
	if (s.length() == 0)
		min_size = 0;
	for (int i = 1; i <= s.length() / 2 + 1; i++) {
		size = unit_mapping(s, i);
		min_size = min(min_size, size);
	}
	return min_size;
}