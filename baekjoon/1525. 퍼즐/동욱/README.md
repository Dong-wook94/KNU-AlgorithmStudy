# 1525 퍼즐

문제가 되게 참신한것 같다.

처음에는 메모리제한이 적길래 bfs를 쓰지말라는 건줄 알았는데 그게 아니였다.

그냥 visit배열 둬버리면 방문체크할때 너무 방대해진다.

그래서 `map을 이용하여 방문체크` 를 하였다



## 풀이방법

1. 입력을 int로 받는다.
   * 여기서 0은 9로 변경하여 받는다
     * 왜냐하면 012345678 처럼 0이 맨앞에오는 경우에는 int로 처리했을때 12345678이되기 때문
2. 방문체크는 map을 이용한다.
   * 메모리 제한이 있기때문 그냥 배열에 넣으면 터짐 9!의 경우를 모두 배열에 넣을수 없기때문
   * map이 또 탐색도 빠르다
3. 현재 9의 위치는 string으로 변환한뒤 find하여 찾는다. 여기서 9 말고 0으로 했으면 문제있었음...
4. 나머지는 평범한 bfs와 동일하다. 종료조건을 123456789와 동일할때로 주고 그때의 최소 거리를 map에서 가져온다.
   * bfs를 사용한이유는 퍼지면서 최초 방문한게 최소거리기 때문에 여기서 적합하다. 

