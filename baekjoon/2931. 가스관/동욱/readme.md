# 2931. 가스관

문제링크 : https://www.acmicpc.net/problem/2931

문제 풀이 링크 : https://dong-co.tistory.com/97



![img](https://k.kakaocdn.net/dn/bKHEPm/btqEgQe5ADC/BK7bKOq0rHGRprb9iZuKp0/img.png)



### 문제풀이

매우 복잡하게 푼거 같은느낌이 든 문제이다.

 

\1. 탐색은 bfs를 사용하였고 bfs를 사용하여 계속 파이프를 따라간다.

\2. 파이프가 이어져야 하는 곳에 파이프가 없을때('.' 일때)

\3. 해당 위치에서 사방을 탐색하여 적절한 파이프를 기존에 저장해놓았던 map에서 반환한다. 

 

모든 걸 넣어보고 문제없는지 확인하는 방법도 있겠지만 더 효율적으로 짜보고자 map을 활용하였다.