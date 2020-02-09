# ❌스팟마트❌

### 왜 안되긴.. 글러먹은 생각때문...



1. 추가 과자 순열 만들기.. (뭔가 필요할 거 같아서 함ㅠ 여기서 부터 잘못됨)

~~~c++
void make_Blist(int cnt){
    
    if(cnt == m){
        int r = max(select_snack(0,0,0,0) , select_snack(0,0,0,1));
//        printf("%d\n",r);
        if(result < r ) result = r;
        return;
    }
    
    for(int i=0; i<m; i++){
        if(select_B[i] == 1) continue;
        select_B[i] = 1;
        B_list.push_back(B[i]);
        make_Blist(cnt+1);
        B_list.pop_back();
        select_B[i] = 0;
    }
}
~~~

2. dpdpdpdpdpdp

~~~c++
int select_snack(int idxA, int idxB,int sum,int mode){
    
    printf("%d %d %d %d\n",idxA,idxB,mode,sum);
    if(mode ==  0 && idxA >= n) return sum;
    if(mode == 1 &&  idxB >= m  ) return sum;
    if(mode == 1 && idxA-1 >= n) return sum;
    if(mode == 0){
        return max(select_snack(idxA+2,idxB, sum+A[idxA], 0), select_snack(idxA+2,idxB, sum+A[idxA], 1));
    }else{
        return max(select_snack(idxA+1,idxB+1,sum+B_list[idxB], 0) , select_snack(idxA,idxB+2, sum+B_list[idxB], 1));
    }
    
}
~~~

mode = 0이면 A 과자 에서 고르고..

mode = 1이면 추가 과자에서 선택하게 했는데...

글러먹은 이유가 다 있음...

글러먹은 코딩인거는 알겠는데 시간이 너무 많이 들었고..너무 힘들어서 관두겠읍니다....

ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ

ㅠ

ㅠ

ㅠㅠ

ㅠㅠㅠㅠㅠㅠㅠㅠㅠ

ㅠㅠㅠㅠㅠㅠ

나중에 언젠가 고침 

🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨😡🤨