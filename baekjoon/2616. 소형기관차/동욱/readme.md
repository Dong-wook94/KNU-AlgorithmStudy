# 소형기관차

![img](https://k.kakaocdn.net/dn/p2TOm/btqEtuJWeQS/UaIqtFNPx2JH770x2jSVnk/img.png)



### 문제풀이

 dp를 이용해서 푸는 문제이다.

 

문제가 어려워서 다른 풀이를 참고하였다

 

이전 객차까지의 최댓값(dp[i][j-1])과 현재 객차를 포함했을 때의 최댓값(sum[j] - sum[j-maxLength]) + dp[i-1][j-maxLength]) 중 큰 값이 현재.i번째 기관차가 1~j객실중 끌 수 있는 승객의 최댓값이 된다.



문제 풀이 링크 : https://dong-co.tistory.com/105