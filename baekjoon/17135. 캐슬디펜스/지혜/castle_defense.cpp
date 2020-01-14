#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct target{
    int row;
    int col;
    int dis;
}target;

int n,m,d; // n행 m열 궁수 최대 공격 거리 d , n+1행에 성~궁수있음 궁수 3명 배치
int map[15][15];
int real_map[15][15];

void init_map(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            map[i][j] = real_map[i][j];
        }
    }
}

void map_down(){
    int tmap[15][15]={0};
    
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
            tmap[i+1][j]=map[i][j];
        }
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            map[i][j] = tmap[i][j];
        }
    }
}

int end_check(){
    int check = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(map[i][j] == 1){
                check +=1;
            }
        }
    }
    return check;
}

int main(){
    vector<int> select;
    
    scanf("%d %d %d",&n,&m,&d);
    
    for(int j=0; j<m; j++){
        if(j<3) select.push_back(1);
        else select.push_back(0);
    }
    
    sort(select.begin(),select.end());
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
            real_map[i][j] = map[i][j];
        }
    }
    
    int result=0;
    do{
        int count = 0;

        init_map();
        
        while(end_check()){
            target t[15]={0};
            for(int i=0; i<select.size(); i++){
                if(select[i] == 1){
                    t[i].dis = 99999;
                    for(int r=0; r<n; r++){
                        for(int c=0; c<m; c++){
                            if(map[r][c] == 1){
                                int dis = abs(n-r) + abs(c-i);
                                if(dis <= d){
                                    if(t[i].dis == dis){
                                        if( t[i].col > c){
                                            t[i].row = r;
                                            t[i].col = c;
                                        }
                                    }else if(t[i].dis > dis){
                                        t[i].row = r;
                                        t[i].col = c;
                                        t[i].dis = dis;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for(int i=0; i<m; i++){
                if(t[i].dis != 0 && t[i].dis != 99999 ){
                    if(map[t[i].row][t[i].col] != 0){
                        map[t[i].row][t[i].col] = 0;
                        count+=1;
                    }
                }
            }
            map_down();
            
        }

        if(result < count){
            result = count;
        }
        
    }while(next_permutation(select.begin(),select.end()));
    
    printf("%d\n",result);
    
    return 0;
}
