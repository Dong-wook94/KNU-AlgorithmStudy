#include	<iostream>
#include	<string>
#include	<cstring>
#include	<algorithm>
using namespace std;

#define MAX 250 + 1

int num;
string cache[MAX];

string bigNumAdd(string num1, string num2) {
	long long sum = 0;
	string result;

	while (!num1.empty() || !num2.empty() || sum) {
		if (!num1.empty()) {
			sum += num1.back() - '0';
			num1.pop_back();
		}
		if (!num2.empty()) {
			sum += num2.back() - '0';
			num2.pop_back();
		}
		result.push_back((sum % 10) + '0');
		sum /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}


int main() {
	// solution
	cache[0] = cache[1] = '1';
	for (int i = 2; i < MAX; i++)
		cache[i] = bigNumAdd(bigNumAdd(cache[i - 2], cache[i - 2]), cache[i - 1]);

	// input & output
	while (~scanf("%d", &num))
		cout << cache[num] << "\n";

	return 0;
}