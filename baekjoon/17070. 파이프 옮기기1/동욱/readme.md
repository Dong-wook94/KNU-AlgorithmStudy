# 17070. 파이프 옮기기 1

문제링크 : https://www.acmicpc.net/problem/17070

문제 풀이 링크 : https://dong-co.tistory.com/96

![img](https://k.kakaocdn.net/dn/mApgV/btqEequlHq7/c7HCALvAQjVWGGtW8m9ESk/img.png)



### 문제풀이

 

카카오에 블록이동과 비슷한것 같지만 다른 문제입니다. 그때는 기준을 왼쪽 위(목적지와 상대적으로 가까운 지점)를 기준으로 잡았지만 이번에는 목적지와 상대적으로 가까운 지점을 기준으로 잡습니다.

 

그리고 현재 방향, 다음 방향을 모두 고려하여 불가능한 케이스를 제거해주고, 다음 위치의 벽유무, 범위 체크등을 해주며 dfs를 진행해 주면 되는 문제입니다.