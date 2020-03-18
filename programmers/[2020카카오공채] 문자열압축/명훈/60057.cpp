#include	<iostream>
#include	<string>
#include	<vector>
#include	<algorithm>
using namespace std;

#define INF 1001

// get digitization
int getSize(int num) {
	int size = 0;
	while(num > 0) {
		num /= 10;
		size++;
	}
	return size;
}

// solution code
int solution(string s) {
	int slen = s.length();
	int ans = slen;
	
	// len--
	for (int len = slen / 2; len > 0; len--) {
		int start_pos = 0;
		int t_len = slen;
		int cnt = 0;

		while (start_pos + len <= slen) {
			// if sub string is same pattern
			if (s.substr(start_pos, len).compare(s.substr((start_pos + len), len)) == 0) {
				cnt++;
			}
			else {
				if (cnt >= 1) {
					t_len -= (cnt * len);		// delete same pattern
					t_len += getSize(cnt + 1);	// add num, +1 is (I'm not count original key)
				}
				cnt = 0;
			}
			start_pos += len;
		}
		ans = min(ans, t_len);
	}
	return ans;
}

int main() {
	string T = "xababcdcdababcdcd";

	cout << solution(T) << "\n";
}