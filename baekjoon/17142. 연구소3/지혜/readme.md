# 17142 연구소3👾

👾 이 시국에..조금 잘 어울리는 문제가 아닌가 싶슴다

누가 골랐는 지 참..;;^^;; 미래를 내다 본 문제인가,,? (눈물)



1. 빈칸이면 emptyNum ++ 해줌! 왜냐하면 이걸로 bfs 돌리다가 끝내줄거니까

2. 바이러스 위치 랜덤으로 고르기 해야해서 selectVirus 배열 만들어서 nextPermutation 돌림

3. 빈칸이 있으면 bfs돌려주기!

   ~~~c++
   do{
               queue<virus> q;
               int count = 0;
               int visit[50][50]={0};
               int endTime=99999;
               int endCheck = 0;
               for(int i=0; i<selectVirus.size(); i++){
                   if(selectVirus[i]==1){
                       q.push(virus(v[i].row,v[i].col,0));
                   }
               }
               
               while(!q.empty()){
                   if(endCheck == 1) break;
                   virus cur = q.front();
                   q.pop();
                   for(int i=0; i<4; i++){
                       int nextR = cur.row + dir_r[i];
                       int nextC = cur.col + dir_c[i];
                       if(nextR < 0 || nextR >=n || nextC <0 || nextC >= n || map[nextR][nextC]==1 || visit[nextR][nextC] == 1 ) continue;
                       
                       q.push(virus(nextR,nextC,cur.time+1));
                       visit[nextR][nextC]=1;
                       if(map[nextR][nextC] == 0) count+=1;
                       
                       if(count == emptyNum){
                           endTime=cur.time+1;
                           endCheck = 1;
                           break;
                       }
                   }
               }
               
               if(result > endTime){
                   result = endTime;
               }
               
           }while(next_permutation(selectVirus.begin(), selectVirus.end()));
   ~~~

   사실 처음에는 빈칸아니면 continue 해놨는데 그러면 안됨!

   비활성바이러스가 활성 바이러스 되는 경우 생각해야함! 그래서 map[ nextR ] [ nextC ] == 1 이면 continue로 바꿈

   벽인 경우만 지나가세오...

   빈칸을 바이러스로 채울때만 count++ 해서 count랑 emptyNum이랑 비교~ => endCheck까지해서 while문 빠져나오게 만들기!