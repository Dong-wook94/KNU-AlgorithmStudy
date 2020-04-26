# 14891. 톱니바퀴

톱니바퀴 상태 string 으로 받음. 반시계 시계 회전할때는 substr 이용해서 잘라서 이어붙이기

톱니바퀴 돌아가면 r_left, r_right 로 주변애들 돌릴지 체크함 

r_left -> 자기 왼쪽 애들 돌리기 

r_right -> 자기 오른쪽 애들 돌리기 

~~~c++
void r_right(int cur){
    if(cur >= 3) return;
    if(s[cur][2] != s[cur+1][6]){
        if(r[cur] == -1) r[cur+1] = 1;
        else r[cur+1] = -1;
        r_right(cur+1);
    }else return;
}

void r_left(int cur){
    if(cur < 1) return;
    if(s[cur][6] != s[cur-1][2]){
        if(r[cur] == -1 ) r[cur-1] = 1;
        else r[cur-1] = -1;
        r_left(cur-1);
    }else return;
}
~~~

