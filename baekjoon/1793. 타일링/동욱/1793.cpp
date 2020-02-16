#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string dp[251];


string bigNumAdd(string n1, string n2) {
	int sum = 0;
	string result;
	while (!n1.empty() || !n2.empty() || sum) {
		if (!n1.empty()) {
			sum += n1.back() - '0';
			n1.pop_back();
		}
		if (!n2.empty()) {
			sum += n2.back() - '0';
			n2.pop_back();
		}
		result.push_back((sum % 10) + '0');
		sum /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}

string mult2(string a) {
	return bigNumAdd(a, a);
}
int main() {
	dp[1] = 1+'0';
	dp[2] = 3+'0';
	int num;
	

	for (int i = 3; i <=250; i++) {
		dp[i] = bigNumAdd(mult2(dp[i - 2]), dp[i - 1]);
	}
	int n;
	while (cin >> n) 
		cout << dp[n] << endl;

	return 0;
}