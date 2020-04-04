# 모든것이 1이된다

## 문제 알고리즘

- 단순 구현 문제

## 풀이방법

1. 문제에서 요구하는 대로, 날짜를 받는다.
2. 그 후 이진법으로 받은 숫자를 10진수로 바꾸고 해결

* 시간 초과...

- 핵심 코드

~~~c++int board[MAX][MAX];						// array
#include	<iostream>
#include	<string>
#include	<cmath>
using namespace std;

typedef long long ll;
int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getMonthDate(int yyyy, int mm) {
	if (mm != 2)
		return month[mm];
	else {
		if ((yyyy % 400 == 0) || (yyyy % 100 != 0 && yyyy % 4 == 0))
			return 29;
		else
			return 28;
	}
}

void solution(int idx) {
	int yyyy=0, mm=0, dd=0, h=0, m=0, s=0;
	int time = 0;
	string s_time;
	scanf("%d/%d/%d %d:%d:%d", &yyyy, &mm, &dd, &h, &m, &s);
	cin >> s_time;

	int time_len = s_time.length();
	for(int i=0; i< time_len; i++)
		time += (int)pow(2, (time_len - i - 1));

	int day, hour, minute, second;
	day = time / 86400;		time %= 86400;
	hour = time / 3600;		time %= 3600;
	minute = time / 60;
	second = time % 60;

	dd += day;	
	h += hour;
	m += minute;	
	s += second;
	if (s >= 60) {
		s -= 60;
		m++;
	}
	if (m >= 60) {
		m -= 60;
		h++;
	}
	if (h >= 24) {
		h -= 24;
		dd++;
	}

	int day_len = getMonthDate(yyyy, mm);
	while (dd > day_len) {
		dd -= day_len;
		mm++;

		if (mm > 12) {
			yyyy++;
			mm = 1;
		}
		day_len = getMonthDate(yyyy, mm);
	}

	printf("#%d ", idx);
	printf("%d/%02d/%02d %02d:%02d:%02d\n", yyyy, mm, dd, h, m, s);
	return;
}


int main() {
	int N = 0;
	
	//freopen("input.txt", "r", stdin);
	
	string start_time, time;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		solution(i + 1);
	}

	return 0;
}
~~~

## 문제 후 느낀점

- 단순 구현이면, 시간을 고려해야하는 문제.
- 나중에 시간초과 고치기.