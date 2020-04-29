2753. 빙산


### 문제풀이


1. 맵 INit() 해주고
2. 각 노드마다 동서남북 탐색하여 얼음이 녹는 CNT 체크
3. CNT만큼 height 낮추기
4. mapping하여 덩어리가 두개로 나눠지면 return.
    그게 아니라면, 각 노드마다 동서남북 다시 탐색하여 얼음이 녹는 CNT를 체크
    => mapping은 BFS를 이용하여 탐색을 진행하였다.
    mapping을 실행할때, 현재 남아있는 노드들을 meltCnt로 계산하고 만약 meltCnt가 1개이상이 있으면, 덩어리가 두개로 나눠진거니깐 true. 아니면 false(덩어리 1개 있다는 뜻)



### 느낀점
단순 탐색문제였다.


문제 링크 : https://www.acmicpc.net/problem/2573

문제 풀이 링크 : https://dong-co.tistory.com/58



