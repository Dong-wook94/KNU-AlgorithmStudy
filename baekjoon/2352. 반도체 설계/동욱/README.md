# 2352. 반도체 설계

문제링크 : https://www.acmicpc.net/problem/2352

문제 풀이 링크 : https://dong-co.tistory.com/89



![img](https://k.kakaocdn.net/dn/OOPoj/btqEbbbRYs4/PhMneGLhWuT2tfrQG472b0/img.png)



### 문제풀이

c++로만 풀다가 첨으로 java로 푼 문제이다.

가장 긴 오름차순 수열을 찾는 LIS문제와 동일하다.

 

마지막 인덱스 접근을 위해 초기에 0을 넣어두고 사용한다.

마지막 인덱스를 size-1로 접근하는데 없으면 에러뜨기때문..

 

마지막보다 큰값이 들어오면 뒤에 삽입. 작거나 같은값이 들어오면 lower_bound값을 찾아 그값과 변경한다.

