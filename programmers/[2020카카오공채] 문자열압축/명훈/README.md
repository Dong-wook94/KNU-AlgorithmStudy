# [2020 카카오 공채] 문자열 압축

## 문제 알고리즘
- 구현 문제

## 풀이방법
1. 해당 문자열의 크기의 반부터 1까지 반복되는 경우를 단순 비교한다.
2. 비교한 문자열의 길이가 더 짧은 경우 반복한다.

* 반복되는 숫자가 10이상인 경우를 더 고려해줘야 한다.

- 핵심 코드
~~~c++
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
					t_len -= (cnt * len);		    // delete same pattern
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
~~~



