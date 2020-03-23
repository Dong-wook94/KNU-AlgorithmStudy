# 17136. 색종이 붙이기

색종이 붙이고나서...다음 부분찾으러가는데 머리썼다가 망함ㅋ

괜히 쓸데없는데서 머리 굴리지 말자..그냥 for문 전체 돌리면 되는데..

그거 전체 안돌리겠다고 애쓰다가 헛짓거리함ㅠ



처음에 scan할때 1인 부분을 vector<pair<int,int>> hide 에 담아줬음 

그래서 Hide 배열 부분 index 넘기면서 했음

dfs 돌려봤읍니다...

~~~c++
void dfs(int hideNum, int cnt){

    if(hideNum >= hide.size()){
        if(checkEnd() == 1){
            if(result > cnt ){ result = cnt;}
        }
        return;
    }
    
    int curR = hide[hideNum].first;
    int curC = hide[hideNum].second;
    
    for(int i=5; i>=0; i--){
        if(paper[i]>0){
            if( checkAttach(curR,curC,i) == 1 ){
                // 종이 붙일 수 있음
                paper[i]-=1;
                vector<int> change = changeHide(hideNum,curR,curC,i);
                for(int j=0; j<change.size(); j++){
                    map[hide[change[j]].first][hide[change[j]].second] = 0;
                }
                int nextNum = findNextHideNum(hideNum);
                dfs(nextNum,cnt+1);
                for(int j=0; j<change.size(); j++){
                    map[hide[change[j]].first][hide[change[j]].second] = 1;
                }
                paper[i]+=1;
            }
        }
    }
    
}
~~~

