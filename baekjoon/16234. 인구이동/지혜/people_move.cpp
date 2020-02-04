#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <math.h>
using namespace std;

int n,l,r; // nxn크기 땅 두나라 인구 차이가 l명 이상 r명 이하면 국경선 열음
int dir_r[4] = {0,1,0,-1};
int dir_c[4] = {-1,0,1,0};

typedef struct location{
    int row;
    int col;
    location(){}
    location(int a,int b){row=a;col=b;}
}location;
int map[50][50];
queue<location> q;
int visited[50][50];
int end_check = 0;

void initVisited(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           visited[i][j]=0;
        }
    }
}

void bfs(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 들렸던 곳이면 패스
            if(visited[i][j] == 1) continue;
            
            // 합 저장
            int sum = map[i][j];
            
            // 개수 cnt
            int cnt = 1;
            
            // 연합 찾을 큐에 넣기
            q.push(location(i,j));
            
            // 연합 다 찾고 나서 바꿔 줘야할 애들 넣어둘 곳
            vector<location> change;
            change.push_back(location(i,j));
            
            // 연합 찾기
            while(!q.empty()){
                   location cur = q.front();
                   q.pop();
                   visited[cur.row][cur.col] = 1;
                   for(int i=0; i<4; i++){
                       int nextR = cur.row + dir_r[i];
                       int nextC = cur.col + dir_c[i];
                       if(nextR <0 || nextC<0 || nextR>=n || nextC>= n || visited[nextR][nextC] == 1)
                           continue;
                       int gap = abs(map[cur.row][cur.col] - map[nextR][nextC]);
                       if(gap >= l && gap <=r){
                           // 연합인 경우
                           sum+=map[nextR][nextC];
                           cnt+=1;
                           visited[nextR][nextC]=1;
                           q.push(location(nextR,nextC));
                           change.push_back(location(nextR,nextC));
                       }
                   }
            }
            
            // 연합팀 다 찾았음
            if(cnt != 1){
                // 연합팀을 찾은 경우
                int change_num = sum/cnt;
                for(int i=0; i<change.size(); i++){
                    map[change[i].row][change[i].col] = change_num;
                }
                change.clear();
                end_check++;
            }
            
        }
    }
}

int main(){
    scanf("%d %d %d",&n,&l,&r);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d",&map[i][j]);
        }
    }
    
    int result = 0;
    while(1){
        initVisited();
        bfs();
        if(end_check == 0) break;
        else{end_check = 0; result+=1;}
        
    }
    printf("%d\n",result);
    return 0;
}
