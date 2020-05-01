#include	<iostream>
#include	<vector>
#include	<algorithm>
#include <limits.h>
using namespace std;

// static
const int MAX = 11;

// variable
int N;
int numList[MAX], signCount[4];
vector<int> signList;
int max_num = INT_MIN, min_num = INT_MAX;

void solution( ) {
	do {
		int sum = numList[0];
		for (int i = 0; i < signList.size(); i++) {
			switch (signList[i])
			{
			case 0:
				sum += numList[i + 1];
				break;
			case 1:
				sum -= numList[i + 1];
				break;
			case 2:
				sum *= numList[i + 1];
				break;
			case 3:
				sum /= numList[i + 1];
				break;
			}
		}

		if (sum > max_num)
			max_num = sum;
		if (sum < min_num)
			min_num = sum;

	} while (next_permutation(signList.begin(), signList.end()));
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++)
		scanf("%d", &numList[i]);
	for (int i = 0; i < 4; i++)
		scanf("%d", &signCount[i]);

	// solution
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < signCount[i]; j++)
			signList.push_back(i);
	
	solution();

	// output
	cout << max_num << "\n" << min_num << "\n";

	return 0;
}