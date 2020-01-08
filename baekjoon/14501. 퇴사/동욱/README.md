# 15686. 퇴사
> 삼성 sw 기출문제,dp문제

## 풀이과정
간단한 dp 문제이다 점화식이 포함된 메인 코드
~~~c++
schedules[0].term = -1;
dp[0] = 0;
for (int i = 1; i <= N; i++) {
	for (int j = 0; j < i; j++) {
		if (i - j >= schedules[j].term) {
			dp[i] = max(schedules[i].pay + dp[j], dp[i]);
			max_profit = max(max_profit, dp[i]);
		}
	}
}
~~~



초반에 신경써서 처리해야될 코드

상담 기간일보다 상담 종료일이 빠른경우에는 pay를 0으로 처리하여 최종 금액 계산에 영향을 가지 않게 했다.

~~~c++
if (i + schedules[i].term > N + 1) {//예외 이때는 이용못함 이때상담은 총상담일을 지나버림
    schedules[i].pay = 0;//이용못해서 pay 0처리
}
~~~

