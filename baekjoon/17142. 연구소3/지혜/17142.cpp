#include <vector>
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct virus{
    int row;
    int col;
    int time;
    virus(){}
    virus(int a,int b){row=a;col=b;time=0;}
    virus(int a,int b,int c){row=a;col=b;time=c;}
}virus;

int n,m;
int map[50][50];
vector<virus> v;
vector<int> selectVirus;
int emptyNum=0;
int result = 99999;
int dir_r[4] = {0,-1,0,1};
int dir_c[4] = {-1,0,1,0};

int main(){
    
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d",&map[i][j]);
            
            if(map[i][j] == 0){
                emptyNum+=1;
            }
            
            if(map[i][j] == 2){
                v.push_back(virus(i,j));
            }
        }
    }
    
    for(int i=0; i<v.size(); i++){
        if(i<m) selectVirus.push_back(1);
        else selectVirus.push_back(0);
    }
    
    sort(selectVirus.begin(),selectVirus.end());
    
    if(emptyNum == 0){
        result=0;
    }else{

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
    }
    
    if(result == 99999){
        result = -1;
    }
    
    printf("%d\n",result);
    return 0;
}
