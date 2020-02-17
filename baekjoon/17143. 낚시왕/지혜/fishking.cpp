#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;
typedef struct shark{
    int row;
    int col;
    int speed;
    int direction;
    int size;
    int live;
    shark(){}
    shark(int a,int b,int c,int d,int e){row=a;col=b;speed=c;direction=d;size=e;live=1;}
}shark;

int r,c,m;
vector<shark> s;
                // 1 2 3 4
int dir_r[5] = {0,-1,1,0,0};
int dir_c[5] = {0,0,0,1,-1};
int map[101][101];

void initMap(){
    if(s.size()){
        for(int i=0; i<s.size(); i++){
            if(s[i].live == 1){
                map[s[i].row][s[i].col] = -1;
            }
        }
    }
}

void shark_move(){

    int originPositionC = 2*(c-1);
    int originPositionR = 2*(r-1);

    if(s.size()){
        for(int i=0; i<s.size(); i++){
            if(s[i].live == 1){
                if(s[i].direction <= 2){
                    if(originPositionR <= s[i].speed) s[i].speed = s[i].speed%originPositionR;
                    for(int j=0; j<s[i].speed; j++){
                        int nextR = s[i].row + dir_r[s[i].direction];
                        if(nextR < 1 ){
                            s[i].direction = 2;
                            nextR += 2;
                        }
                        if(nextR > r){
                            s[i].direction = 1;
                            nextR -=2;
                        }
                        s[i].row = nextR;
                    }
                }else{
                    if(originPositionC <= s[i].speed) s[i].speed = s[i].speed%originPositionC;
                    for(int j=0; j<s[i].speed; j++){
                        int nextC = s[i].col + dir_c[s[i].direction];
                        if(nextC < 1){
                            s[i].direction = 3;
                            nextC +=2;
                        }
                        if(nextC > c){
                            s[i].direction = 4;
                            nextC -=2;
                        }
                        s[i].col = nextC;
                    }
                }

                if(map[s[i].row][s[i].col] == -1){
                    map[s[i].row][s[i].col] = i;
                }else{
                    int index = map[s[i].row][s[i].col];
                    if(s[index].size < s[i].size){
                        s[index].live = 0;
                        map[s[i].row][s[i].col] = i;
                    }else{
                        s[i].live = 0;
                    }
                }
                
            }
        }
    }
}


int main(){

    scanf("%d %d %d",&r,&c,&m);

    for(int i=1; i<=r; i++){
        for(int j=1; j<=c; j++){
            map[i][j] = -1;
        }
    }

    for(int i=0; i<m; i++){
        int a,b,c,d,e;
        scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
        s.push_back(shark(a,b,c,d,e));
        map[a][b] = i;
    }

    int result = 0;
    for(int i=1; i<=c; i++){
        if(s.size()){
            // 낚시왕 상어 잡음
            for(int j=1; j<=r; j++){
                if(map[j][i] != -1){
                    result += s[map[j][i]].size;
                    int index = map[j][i];
                    map[j][i] = -1;
                    s[index].live = 0;
                    break;
                }
            }


            initMap();

            // 상어 이동
            shark_move();

        }
    }
    printf("%d\n",result);
    return 0;
}
