# 14888. 연산자 우선순위

감사한 과거의 지혜에게 치얼스 🥂

INT_MIN 과 INT_MAX를 쓰고 싶다면.. <limits.h>임. 암튼 그럼

행복했다...

~~~C++
void cal(int front, int cur){
    if(cur >= n ){
        if(front > result_max) result_max = front;
        if(front < result_min) result_min = front;
        return;
    }
    
    int new_front = front;
    for(int i=0; i<4; i++){
        if(op[i] == 0) continue;
        if(i == 0){
            // 덧
            new_front += num[cur];
        }else if(i == 1){
            // 뺄
            new_front -= num[cur];
        }else if(i == 2){
            // 곱
            new_front *= num[cur];
        }else{
            // 나누기
            new_front /= num[cur];
        }
        op[i]-=1;
        cal(new_front, cur+1);
        op[i]+=1;
        new_front = front;
    }
}

~~~

