# [2019카카오공채] 무지의 먹방 라이브

문제 풀이 링크 : https://dong-co.tistory.com/77

![img](https://k.kakaocdn.net/dn/lOhHK/btqDY0WxIOO/cR4gzoHEcnq5sMIUK8YmIK/img.png)



### 문제풀이

그냥 회전을 시키면 시간초과가 나는문제이다. 

인덱스와 food time을 포함한 구조체(food)를 만들어 정렬한뒤 food time이 낮은거 부터 삭제해나간다.

food time 이 낮은수는 그다음 높은 food time 에서 빼가며 계산해 주는걸 잊어서는 안된다. 왜냐하면 그만큼은 다 돌았기 때문에 이러한 점을 고려하여 돌다가 차이만큼 뺄 수없을때 모듈러 연산을 진행한다.

 

말이 너무 복잡하니 코드를 보면 이해가 쉬울거 같다. '

 

accumulate는 누적된 시간이라 생각하면되고

spend는 한번에 넘길 턴? 한번에 소비할 시간이라 보면된다. 