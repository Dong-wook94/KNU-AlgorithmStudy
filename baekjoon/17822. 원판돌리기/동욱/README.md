# 17822. 원판돌리기

> 삼성 sw 기출문제, 시뮬레이션

## 풀이

**순서는 이러하다**

1. 원판을 돌린다.
2. 인접한 곳 체크 후 값이 같을경우 변경한다.(dfs 이용)
3. 2번에서 전부 체크후 값이 변경되지 않았을시 평균보다 큰경우 -1, 작은경우 +1으로 값을 재조정한다.



**인접한곳 체크및 변경은 dfs를 통해 진행하였다.**

~~~c++
void dfs(int r,int c,int cmp) {
	for (int i = 0; i < 4; i++) {
		int next_row = r + dir_row[i];
		int next_col = c + dir_col[i];
		if (next_col == 0) //원판이니 끝처리위해
			next_col = M;
		else if (next_col == M+1)
			next_col = 1;
		if (circles[next_row][next_col] == cmp) {//비교는 항상 초기 값과한다
			check = 1;//변경시 check 값 변경
			circles[next_row][next_col] = 0;
			circles[r][c] = 0;
			dfs(next_row, next_col, cmp);
		}
	}
}
~~~



**원판이라 끝처리는 다음과 같이 처리하였다.**

~~~c++
if (next_col == 0) //원판이니 끝처리위해
			next_col = M;
		else if (next_col == M+1)
			next_col = 1;
~~~

이렇게 되면 오른쪽끝의 오른쪽은 1번째 인덱스 1번째 인덱스의 왼쪽은 오른쪽 끝이된다.



