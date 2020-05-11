# 17281. ⚾



![img](https://k.kakaocdn.net/dn/cr2SDv/btqD6m4JFz7/mYjMrVK2cANd0JoPGvklGk/img.png)



문제 풀이링크 : https://dong-co.tistory.com/82

###  

### 문제풀이

 

시뮬레이션 문제이다. 순열을 만드는 방법은 next_permutation() 을 써도 되지만 여기서는 그냥 dfs를 이용하여 순열을 생성하였다.

 

순열을 생성하여 타순을 매번 정하여 해당 타순을 기준으로 점수를 산출한다. 

 

출루는 베이스에 1을 추가한뒤 배열을 미는 방식으로 점수를 산출한다. 1루이동을 매루에 적용하여 재사용하였다.

 



