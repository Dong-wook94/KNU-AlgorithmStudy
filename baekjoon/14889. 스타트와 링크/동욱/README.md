# 14889. 스타트와 링크
> 삼성 역량테스트 기출문제

문제링크 : https://www.acmicpc.net/problem/14889

## 풀이과정

>1. 조합으로 팀을 나눈다 
>2. 팀을나눈후 팀 끼리 능력치조합의 합을 구하고 차이를 계산.
>3. 차이의 최소를 갱신한다.

1. **조합으로 팀을 나눈다 **
   next_permutation 을 사용 하였다.
   
2. **팀을나눈후 팀 끼리 능력치조합의 합을 구하고 차이를 계산.**
   불필요한 for문연산을 없애기 위해 set 을 사용하였지만 오히려 그게더 시간이 많이 걸렸다.

   set을 사용

   ~~~c++
   int sum_team(set<int> t) {//팀의 시너지 합구하기
   	int sum = 0;;
   	for (auto iter = t.begin(); iter != t.end(); iter++) {
   		for (auto iter2 = t.begin(); iter2 != t.end(); iter2++) {
   			sum += info[*iter][*iter2];
   		}
   	}
   	return sum;
   }
   
   void comb() {//조합으로 팀나누기
   	for (int i = 0; i < N / 2; i++)
   		team.push_back(0);
   	for (int i = 0; i < N / 2; i++)
   		team.push_back(1);
   
   	do {
   		int sumA=0, sumB=0;
   		set<int> teamA, teamB;
   		for (int i = 0; i < N; i++) {//set에 삽입
   			if (team[i] == 0)
   				teamA.insert(i);
   			else 
   				teamB.insert(i);
   		}
   		sumA = sum_team(teamA);
   		sumB = sum_team(teamB);
   		result = min(result, abs(sumA - sumB));//최솟값 갱신
   	} while (next_permutation(team.begin(), team.end()));
   }
   ~~~

   그냥 조건으로 갈라서 합구하기

   ~~~c++
   do {
   		sumA = 0;
   		sumB = 0;
   		for (int i = 1; i <=N; i++) {
   			for (int j = 1; j <= N; j++) {
   				if (comb[i - 1] == 1 && comb[j - 1] == 1)
   					sumA += Arr[i][j];
   				else if (comb[i - 1] == 0 && comb[j - 1] == 0)
   					sumB += Arr[i][j];
   			}
   		}
   		result = min(result, abs(sumA - sumB))
   	} while (next_permutation(comb.begin(), comb.end()));
   ~~~

   

3. **차이의 최소를 갱신한다.**

   > 알고리즘 라이브러리 min,max 사용하면 최솟값 갱신 편하다.

   ~~~c++
   result = min(result, abs(sumA - sumB));//최솟값 갱신
   ~~~

   





