#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;
time_t makeTimeFormatFromInput(int YYYY, int MM, int DD, int hh, int mi, int ss);

string Testcase() {
	string binNum;
	int YYYY, MM, DD, hh, mi, ss;

	scanf("%d/%d/%d %d:%d:%d", &YYYY, &MM, &DD, &hh, &mi, &ss);
	cin >> binNum;
	int YYYYYY=0;
	if (YYYY > 2800) {
		YYYYYY = YYYY-2800;
		YYYY = 2800;
	}
	
	char result_date[100];
	time_t input_time = makeTimeFormatFromInput(YYYY, MM, DD, hh, mi, ss);
	long long addNum = strtoul(binNum.c_str(), NULL, 2);
	long long seconds = input_time;
	seconds = seconds +addNum;
	time_t t = seconds;
	string result="";
	if (YYYYYY > 0) {
		char result_year[100];
		strftime(result_year, 50, "%Y", localtime(&t));
		int year = atoi(result_year);
		year = YYYYYY + year;
		sprintf(result_year, "%d", year);
		strftime(result_date, 50, "/%m/%d %H:%M:%S", localtime(&t));
		result.append(result_year);
		result.append(result_date);
	}
	else {
		strftime(result_date, 50, "%Y/%m/%d %H:%M:%S", localtime(&t));
		result = result_date;
	}
	
	return result;
}

int main(void) {
	int testcase;
	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		cout << "#" << t << " " << Testcase() << endl;
	}

}

time_t makeTimeFormatFromInput(int YYYY, int MM, int DD, int hh, int mi, int ss)
{
	struct tm st_tm;

	st_tm.tm_year = YYYY - 1900;
	st_tm.tm_mon = MM - 1;
	st_tm.tm_mday = DD;
	st_tm.tm_hour = hh;
	st_tm.tm_min = mi;
	st_tm.tm_sec = ss;

	return mktime(&st_tm);

}

