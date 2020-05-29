# 11967. 불켜기

문제링크 : https://www.acmicpc.net/problem/11967

![img](https://k.kakaocdn.net/dn/ttaiD/btqEu6a2x4P/tLXcGAEyOyRbpyNcocAuR0/img.png)



### 문제풀이

불이 켜진곳만 갈수 있고 불을 켜는 곳은 다른방이다. 

그래서 갔던 곳도 다시 가보면 갈 수 있는 곳이 늘었을 수도 있다.

 

그래서 bfs를 반복해서 돌려야된다. 언제까지 돌려야되냐면 count가 증가하지 않을 때 까지 돌려야 된다. 

 

불을 켜는 정보는 2차원으로 이루어진 vector로 구현된 adjacencyList 에 저장한다.



문제 풀이 링크 : https://dong-co.tistory.com/106