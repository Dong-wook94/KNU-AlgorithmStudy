#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct chess{
    int row;
    int col;
    int direction; // 1 오 2 왼 3 위 4 아래
}chess;
typedef struct m{
    int color; // 0 흰 1 빨 2 파
    vector<int> horse;
}m;

int dir_r[5] ={0,0,0,-1,1};
int dir_c[5] ={0,1,-1,0,0};
m map[13][13];
chess inputChess[11];
int n,k;

void print_map(){
    printf("\n");
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printf("[");
            for(int k=0; k<map[i][j].horse.size(); k++){
                printf("%d ",map[i][j].horse[k]);
            }
            printf("]");
        }
        printf("\n");
    }
    printf("\n");
}

int move(int number,chess turn){
    int curR = turn.row;
    int curC = turn.col;
    int dir = turn.direction;
    vector<int> upHorse;
    
    int nextR = curR + dir_r[dir];
    int nextC = curC + dir_c[dir];
    if(nextR < 1 || nextR > n || nextC < 1 || nextC > n || map[nextR][nextC].color == 2){
        if(dir == 1) dir = 2;
        else if(dir == 2) dir = 1;
        else if(dir == 3) dir = 4;
        else dir = 3;

        nextR = curR + dir_r[dir];
        nextC = curC + dir_c[dir];

        if(map[nextR][nextC].color == 2 || nextR < 1 || nextR > n || nextC < 1 || nextC > n ){
            inputChess[number].direction = dir;
            if(map[nextR][nextC].horse.size()>=4) return 1;
            else return 0;
        }
    }

    // 자기 위에 있는 말 번호 들고오기 나부터~내위에 말 전부!
    if(!map[curR][curC].horse.empty()){
        for(int i=0; i<map[curR][curC].horse.size(); i++){
            if(map[curR][curC].horse[i] == number){
                upHorse.assign(map[curR][curC].horse.begin()+i,map[curR][curC].horse.end());
                map[curR][curC].horse.erase(map[curR][curC].horse.begin()+i,map[curR][curC].horse.end());
                break;
            }
        }
    }
    
    // 위치 바꿔주기!
    for(int i=0; i<upHorse.size(); i++){
        inputChess[upHorse[i]].row = nextR;
        inputChess[upHorse[i]].col = nextC;
        if(upHorse[i] == number) inputChess[upHorse[i]].direction = dir;
    }

    // map에 이동한 거 추가하기
    if(map[nextR][nextC].color == 1){
        // 빨강 거꾸로 추가
        for(int i=(int)upHorse.size()-1; i>=0; i--)
            map[nextR][nextC].horse.push_back(upHorse[i]);
    }else{
        // 나머지..빨 파..
        for(int i=0; i<upHorse.size(); i++)
            map[nextR][nextC].horse.push_back(upHorse[i]);
    }

    if(map[nextR][nextC].horse.size() >= 4) return 1;
    else return 0;
}

int main(){

    scanf("%d %d",&n,&k);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&map[i][j].color);
        }
    }

    for(int i=0; i<k; i++){
        scanf("%d %d %d",&inputChess[i].row,&inputChess[i].col,&inputChess[i].direction);
        map[inputChess[i].row][inputChess[i].col].horse.push_back(i);
    }

    int result = 0;
    int end = 0;
    
    while(1){
        result+=1;
        for(int i=0; i<k; i++){
            if(move(i,inputChess[i]) == 1){ end=1; break;}
        }
        if(end == 1 || result > 1000) break;
    }

    if(result > 1000) result = -1;
    printf("%d\n",result);
    return 0;
}
