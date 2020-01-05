#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>

using namespace std;

typedef struct fish{
    int row;
    int col;
    int size;
    int dis;
    fish(){}
    fish(int a,int b,int c){row=a;col=b;dis=c;}
}fish;

typedef struct shark{
    int row;
    int col;
    int size;
    int eat_count;
    int time;
    shark(){}
    shark(int a,int b,int c){row=a;col=b;time=c;}
}shark;


int map_size;
int Map[21][21];
int visit[21][21];
int dir_row[4]={0,1,0,-1};
int dir_col[4]={-1,0,1,0};
shark s;
queue<shark> q;

vector<fish> fishes;

void init_visit(){
    for(int i=0; i<map_size; i++){
        for(int j=0; j<map_size; j++){
            visit[i][j]=0;
        }
    }
}

void bfs(){
    q.push(s);
    init_visit();
    while(!q.empty()){
        shark cur = q.front();
        q.pop();
        visit[cur.row][cur.col]=1;
        for(int i=0; i<4; i++){
            int next_row = cur.row + dir_row[i];
            int next_col = cur.col + dir_col[i];
            if(next_row <0 || next_col <0 || next_row >=map_size || next_col>=map_size || visit[next_row][next_col] == 1)
                continue;
            if(Map[next_row][next_col]==0 || Map[next_row][next_col] == s.size){
                q.push(shark(next_row,next_col,cur.time+1));
            }else if(Map[next_row][next_col] < s.size){
                fishes.push_back(fish(next_row,next_col,cur.time+1));
            }
            visit[next_row][next_col] = 1;
        }
    }
}

bool cmp(fish &a,fish &b){
    if(a.dis == b.dis){
        if(a.row == b.row){
            return a.col<b.col;
        }
        return a.row<b.row;
    }
    return a.dis<b.dis;
}

int main(){
    scanf("%d",&map_size);
    for(int i=0; i<map_size; i++){
        for(int j=0; j<map_size; j++){
            scanf("%d",&Map[i][j]);
            if(Map[i][j] == 9){
                s.row=i;
                s.col=j;
                s.size=2;
                s.eat_count=0;
                s.time=0;
                Map[i][j]=0;
            }
        }
    }


    bfs();
    //printf("size : %d",fishes.size());
    while(!fishes.empty()){
        sort(fishes.begin(),fishes.end(),cmp);
        s.row = fishes[0].row;
        s.col = fishes[0].col;
        Map[s.row][s.col]=0;
        s.time = fishes[0].dis;
        s.eat_count++;
        if(s.size == s.eat_count){
            s.size++;
            s.eat_count=0;
        }
        fishes.clear();
        //printf("(%d,%d,%d) : %d\n",s.row,s.col,s.size,s.time);
        bfs();
    }

    printf("%d\n",s.time);


    return 0;
}
