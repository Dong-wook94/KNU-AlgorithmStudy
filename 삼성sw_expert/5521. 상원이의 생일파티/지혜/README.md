# 상원이의 생일파티

왜 문제조건에.. a,b a<b 적어놨는가..🤔
부수고싶다...
1 2
3 2 
input 들어오면 2장임
나는.. 3 2 가 들어오는지 몰랐쒀요...
a<b라면서요...거짓말했냬....

상원이 생일파티 제대로 하기 싫은거같음ㅎ



상원이의 베스트 프렌드만 q에 넣어주고 visit 체크해서 초대장 개수 쁠쁠함

~~~c++
queue<int> q;
        q.push(1);
        visit[1] = 1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int j=0; j<f.size(); j++){
                if(f[j].pair1 == cur && visit[f[j].pair2] == 0){
                    visit[f[j].pair2] = 1;
                    result++;
                    if(cur == 1){
                        q.push(f[j].pair2);
                    }
                }
                if(f[j].pair2 == cur && visit[f[j].pair1] == 0){
                    visit[f[j].pair1] = 1;
                    result++;
                    if(cur == 1){
                        q.push(f[j].pair1);
                    }
                }
            }
        }

~~~