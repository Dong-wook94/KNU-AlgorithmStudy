# 17825. 주사위 윷놀이

> 삼성 SW 기출문제

### 풀이방법

문제를 처음보고 순열인가? 라고 생각을 했지만 시간이 오래걸리는줄 알고 DP로 문제를 시도했었다. 오답이었다..
그래서 그냥 중복순열로 말을 1개움직일때, 2개움직일때, 3개움직일떄, 4개움직일때 이렇게 각각 계산후에 max값을 출력시켰다.

이 문제를 풀 때 제일 관건은 처음에 path를 어떻게 설정해주는가 와 한칸에는 말이 한개만 있어야하므로 이를 검사하는 부분을 잘 짜야된다고 생각했다.

나는 path를 총 4개로 나눠서 짰는데, 
{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,-1},
            {10,13,16,19,25,30,35,40,-1},
            {20,22,24,25,30,35,40,-1},
            {30,28,27,26,25,30,35,40,-1}}; 이렇게 4개의 길로 나눠서 짰다. 
            

 처음에는 이게 편하겠구나 해서 이렇게 코딩을 하다가 중복 검사를 하는 곳에서 생각 보다 많은 예외가 생겨서 별로 좋지 않은 path 설정인 것 같다는 생각이 들었다.


                        if(cur_value==horse[other_horse].value){ // 중복탐색

                        if(cur_value==25 || cur_value ==35 || cur_value == 40){ // 25,35,40은 pathline 1,2,3에 다같이 존재하기때문에, 그리고 윷놀이판에 1개만존재
                                return -1;
                        }
                        else if(cur_value == 30){ // 30같은경우는 pathline 3에도 존재하는데 이는 같은 칸이 아니다.

                            if(horse[horse_index].cur_pathline==3 && horse[other_horse].cur_pathline==3)
                                return -1;
                            else if(horse[horse_index].cur_pathline!=3 && horse[other_horse].cur_pathline!=3)
                                return -1;
                        }
                        else{
                            if(horse[horse_index].cur_pathline==horse[other_horse].cur_pathline) // 나머지 수 같은 경우는 postion만 같으면 값이 중복된다.
                                return -1;
                        }
                    }

나의 중복 판단하는 부분인데 너무 더럽다.. pathline을 4개로 두고 4개로 두는 바람에 30같은 경우는 모든 라인에 다 존재하게 된다.
하지만  pathline 1,2에 존재하는 30과 pathline 3에 존재하는 맨 앞의 30은 서로 다른칸에 있는 값이다.. 이를 예외 처리 해주어야한다.


문제를 풀때는 처음을 잘 생각해야 한다는 것을 다시 한번 깨달았다.


public static void repermutation(int number,int cnt,int horse_cnt){  => 중복순열 몇번째 주사위에 몇번째 말을 정하기 위해서 중복순열로 탐색을 한다.

        if(cnt==dice.length){
                if(max_value<calculate(horse_cnt)){
                    max_value=calculate(horse_cnt);
                    for(int i=0;i<selected.size();i++)
                        route[i]=selected.get(i);
                }
                return;

        }
        else{

            for(int index=number;index<horse_cnt;index++){
                selected.add(index);
                repermutation(number,cnt+1,horse_cnt);
                selected.remove(selected.size()-1); // Last delete
            }

        }


    }



