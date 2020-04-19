//
//  5214.cpp
//  test
//
//  Created by 지혜 on 2020/04/19.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
typedef struct tube{
    vector<int> connect;
}tube;
tube t[1000];
tube station[100001];
int visit[100001];
int n,k,m;

int main(){
    
    scanf("%d %d %d",&n,&k,&m);
    for(int i=0; i<m; i++){
        for(int j=0; j<k; j++){
            int a;
            scanf("%d",&a);
            t[i].connect.push_back(a);
            station[a].connect.push_back(i);
        }
    }
    
    queue<int> q;
    q.push(1);
    visit[1] = 1;
    while(!q.empty()){
        int cur = q.front();
        int curV = visit[cur];
        q.pop();
        
        if(cur == n ){
            printf("%d\n",curV);
            return 0;
        }
        
        for(int i=0; i<station[cur].connect.size(); i++){
            int hyperTube = station[cur].connect[i];
            for(int j=0; j<k; j++){
                if(visit[t[hyperTube].connect[j]] == 0){
                    q.push(t[hyperTube].connect[j]);
                    visit[t[hyperTube].connect[j]] = curV+1;
                }
            }
        }
    }
    
    printf("-1\n");
    return 0;
}
