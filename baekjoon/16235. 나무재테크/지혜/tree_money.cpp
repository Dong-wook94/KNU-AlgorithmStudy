#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct land{
    int food;
    vector<int> trees;
}land;

int n,m,k; // nxn 땅, 심은 나무 m개 , k년 지난 후 살아남은 나무 수?
int dir_r[8] = {-1,-1,-1,0,0,1,1,1};
int dir_c[8] = {-1,0,1,-1,1,-1,0,1};
land map[11][11];
int add_foodmap[11][11];

bool desc(int a,int b){
    return a>b;
}
int main(){

    scanf("%d %d %d",&n,&m,&k);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&add_foodmap[i][j]);
            map[i][j].food = 5; // 처음 양분 값 설정
        }
    }

    for(int i=0; i<m; i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        map[x][y].trees.push_back(z);
    }

    int result=0;

    for(int i=0; i<k; i++){

        // 봄 ~ 여름
        for(int r=1; r<=n; r++){
            for(int c=1; c<=n; c++){
                if(map[r][c].trees.size()){
                     int deadTree_sum=0;
                    // 나무 나이 순서대로 sorting
                    sort(map[r][c].trees.begin(),map[r][c].trees.end());
                    for(int k=0; k<map[r][c].trees.size(); k++){
                        if(map[r][c].food >= map[r][c].trees[k]){
                            map[r][c].food -= map[r][c].trees[k];
                            map[r][c].trees[k] += 1;
                        }else{
                            deadTree_sum += map[r][c].trees[k]/2;
                            map[r][c].trees.erase(map[r][c].trees.begin()+k);
                            k--;
                        }
                    }
                    map[r][c].food += deadTree_sum;
                }
            }
        }

        // 가을
        for(int r=1; r<=n; r++){
            for(int c=1; c<=n; c++){
                if(map[r][c].trees.size()){
                    for(int k=0; k<map[r][c].trees.size(); k++){
                        if(map[r][c].trees[k] %5 == 0 ){
                            for(int m=0; m<8; m++){
                                int dirR = r+dir_r[m];
                                int dirC = c+dir_c[m];
                                if( dirR>=1 && dirR<=n && dirC>=1 && dirC <=n){
                                    map[dirR][dirC].trees.push_back(1);
                                }
                            }
                        }
                    }
                }
            }
        }

        // 겨울
        for(int r=1; r<=n; r++){
            for(int c=1; c<=n; c++){
                map[r][c].food += add_foodmap[r][c];
            }
        }

        // 살아남은 나무 수 count;
        int count =0;
        for(int r=1; r<=n; r++){
            for(int c=1; c<=n; c++){
                count += map[r][c].trees.size();
            }
        }
        result = count;
    }
    printf("%d\n", result);
    return 0;
}
