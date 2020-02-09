# 스팟마트

### 시간초과

처음에는 풀이를 순열로 생각했다.

1. 먼저 n봉지는 0으로 m봉지는 값그대로 vector에 저장
2. sort한다
3. 그리고 순차적으로 next_permutation으로 돌리며 max값을 받아오려했으나
4. 좀만생각해보면 시간복잡도가 너무 안좋아 시간초과날게 뻔한데 일단 그냥 풀어서 시간초과가 났다.

~~~c++
#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int numN;
int numM;
vector<int> orderN;
vector<int> cookies;
 
 
int findMaxResult() {
    int max_sum = 0;
    do {
        int sum = 0;
        int iterN = 0;
        for (int i = 0; i < cookies.size(); i++) {
            if (cookies[i] == 0) {//N봉지
                if (i % 2 == 0) {
                    sum += orderN[iterN];
                }
                iterN++;
            }
            else {//M봉지
                if (i % 2 == 0) {
                    sum += cookies[i];
                }
            }
        }
        max_sum = max(sum, max_sum);
    } while (next_permutation(cookies.begin(), cookies.end()));
    return max_sum;
}
 
int Testcase() {
     
    scanf("%d", &numN);
    for (int i = 0; i < numN; i++) {
        int input;
        scanf("%d", &input);
        cookies.push_back(0);
        orderN.push_back(input);
    }
    scanf("%d", &numM);
    for (int i = 0; i < numM; i++) {
        int input;
        scanf("%d", &input);
        cookies.push_back(input);
    }
    sort(cookies.begin(), cookies.end());
 
    return findMaxResult();
}
 
int main() {
    int testcase;
    //freopen("input.txt", "r", stdin);
    scanf("%d", &testcase);
 
    for (int t = 1; t <=testcase; t++) {
        printf("#%d %d\n", t, Testcase());
    }
}
~~~



### 통과한 풀이

> dp를 이용한 재귀적인 풀이

1. 먼저 M봉지를 크기별로 내림차순정렬한다.
2. 그리고 dp 를 시작한다
3. 이렇게 나눈다
   1. 현재가 선택되었을때, 뒤에선택안하고 뒤에 N봉지올때
   2. 현재가 선택되었을때 ,뒤에선택안하고 뒤에 M봉지 올때
   3. 현재가 선택안되었을때, 뒤에 선택하고 뒤에 N봉지올때
   4. 현재가 선택안되었을때, 뒤에 선택안하고 뒤에 N봉지올때
   5. 현재가 선택안되었을때, 뒤에 선택하고 뒤에 M봉지올때
   6. 현재가 선택안되었을때, 뒤에 선택안하고 뒤에 M봉지올때
4. 이들중 Max값을 가지게하여 dp진행한다.

~~~c++
int findMaxResult(int iterN, int iter_selectedM, int iter_passM, int selected) {
	//끝
	if (iterN >= numN && (iter_selectedM + iter_passM) >= numM)
		return 0;
	int &result = dp[iterN][iter_selectedM][iter_passM][selected]; //result로 별칭
	if (result != 0) //이미계산한곳
		return result;
	if (selected) {//여기가 선택됐을때
		if (iterN < numN) { //뒤에 선택안하고 뒤에 N올때
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//뒤에 선택안하고 뒤에 M올때
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	else {//여기가 선택 안됐을때
		if (iterN < numN) {//뒤에 N올때
			//뒤에 선택
			result = max(result, N[iterN] + findMaxResult(iterN + 1, iter_selectedM, iter_passM, 1));
			//뒤에 선택안함
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//뒤에 M올때
			//뒤에 선택
			result = max(result, M[iter_selectedM] + findMaxResult(iterN, iter_selectedM + 1, iter_passM, 1));
			//뒤에 선택안함
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	return result;
}

~~~

