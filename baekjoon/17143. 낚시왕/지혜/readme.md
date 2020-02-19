# 17143. 낚시왕

🦈 상어는 먹어서 없애기로 결정 지은 문제 🦈

앞으로 봐주지 않고 샥스핀이랑 캐비어를 왕창 먹어서 상어 멸종하게 만들 것

그리고 저는..다시는 벡터를 지우지 않겠습니다...

벡터 지우면..눈물 나는 일이 많음ㅠㅠ



벡터 지우면 모다? 나는 멍청이..😡



1. 상어 이동

~~~c++
void shark_move(){

    int originPositionC = 2*(c-1);
    int originPositionR = 2*(r-1);

    if(s.size()){
        for(int i=0; i<s.size(); i++){
            if(s[i].live == 1){
                if(s[i].direction <= 2){
                    if(originPositionR <= s[i].speed) s[i].speed = s[i].speed%originPositionR;
                    for(int j=0; j<s[i].speed; j++){
                        int nextR = s[i].row + dir_r[s[i].direction];
                        if(nextR < 1 ){
                            s[i].direction = 2;
                            nextR += 2;
                        }
                        if(nextR > r){
                            s[i].direction = 1;
                            nextR -=2;
                        }
                        s[i].row = nextR;
                    }
                }else{
                    if(originPositionC <= s[i].speed) s[i].speed = s[i].speed%originPositionC;
                    for(int j=0; j<s[i].speed; j++){
                        int nextC = s[i].col + dir_c[s[i].direction];
                        if(nextC < 1){
                            s[i].direction = 3;
                            nextC +=2;
                        }
                        if(nextC > c){
                            s[i].direction = 4;
                            nextC -=2;
                        }
                        s[i].col = nextC;
                    }
                }

                if(map[s[i].row][s[i].col] == -1){
                    map[s[i].row][s[i].col] = i;
                }else{
                    int index = map[s[i].row][s[i].col];
                    if(s[index].size < s[i].size){
                        s[index].live = 0;
                        map[s[i].row][s[i].col] = i;
                    }else{
                        s[i].live = 0;
                    }
                }
                
            }
        }
    }
}

~~~

원래 자기자리로 자기방향 그대로 돌아오는 경우 계산해서 나눠주고 돌리기~~~