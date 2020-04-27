# [2020 카카오 공채] 블록 이동하기

[블로그 풀이](https://dong-co.tistory.com/9)

![img](https://k.kakaocdn.net/dn/dCOp3y/btqCOzd6aka/iYLgdV2BuiKAgMridEBnk0/img.png)





### 풀이

1. bfs를 사용한다. 이유는 특정 depth의 모든 경우를 탐색하기 위함.
2. 방문 위치 표시 방법 : 가로모드 1개, 세로 모드 1개 고려한 2차원 visted 배열로 구성
3. 한 번에 할 수 있는 것들 : 상하좌우 이동, 회전



![img](https://k.kakaocdn.net/dn/bNQUQA/btqCNHjnOLP/yACRaKJj87KV6vly4b9FlK/img.png)



회전 경우의 수는 위와 같이 그려서 케이스를 분리해 보았다. 

검사 시 중복을 최소화하는 방향으로 묶어주었다. 

 

파란색 동그라미는 저장되는 좌표 빨간 글씨는 거치는 점이다.

1,2,3,4의 경우 가로에서 세로 5,6,7,8의 경우는 세로에서 가로로 이동하는 경우이다. 

 

 

문제 링크 : https://programmers.co.kr/learn/courses/30/lessons/60063