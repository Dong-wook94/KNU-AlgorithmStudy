//
//  17406.cpp
//  test
//
//  Created by 지혜 on 2020/03/15.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct rotatee{
    int r;
    int c;
    int s;
}rotatee;

int arr[51][51];
int temp2[51][51];
rotatee rotation[6];
int dir_r[4]={0,0,-1,1}; // 오 왼 위 아래 순으로~
int dir_c[4]={1,-1,0,0};
int n,m,k;

void printArr(){
    printf(">>>>>\n");
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void move(rotatee a){
    int temp[51][51]={0};
    int startR = a.r - a.s;
    int startC = a.c - a.s;
    int endR = a.r+a.s;
    int endC = a.c+a.s;
    int saveSR = startR;
    int saveER = endR;
    int saveSC = startC;
    int saveEC = endC;

    while(1){
        if(startR == endR && startC == endC){
            temp[startR][startC] = temp2[startR][startC];
            break;
        }
        if(startR > endR && startC > endC ) break;

        for(int i=startC; i<=endC; i++){
            // 오른쪽 움직이기
            int nextC = i + dir_c[0];
            if( nextC > endC ) continue;
            temp[startR][nextC] = temp2[startR][i];
        }

        for(int i=startC; i<=endC; i++){
            // 왼쪽 움직이기
            int nextC = i + dir_c[1];
            if(nextC < startC) continue;
            temp[endR][nextC] = temp2[endR][i];
        }

        for(int i=startR; i<=endR; i++){
            // 위쪽 움직이기
            int nextR = i + dir_r[2];
            if( nextR < startR) continue;
            temp[nextR][startC] = temp2[i][startC];
        }

        for(int i=startR; i<=endR; i++){
            // 아래 움직이기
            int nextR = i + dir_r[3];
            if( nextR > endR ) continue;
            temp[nextR][endC] = temp2[i][endC];
        }

        startR+=1;
        startC+=1;
        endR-=1;
        endC-=1;
    }

    for(int i=saveSR; i<=saveER; i++){
        for(int j=saveSC; j<=saveEC; j++){
            temp2[i][j] = temp[i][j];
        }
    }

}

int main(){

    scanf("%d %d %d",&n,&m,&k);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d",&arr[i][j]);
            temp2[i][j] = arr[i][j];
        }
    }
    for(int i=0; i<k; i++){
        scanf("%d %d %d",&rotation[i].r,&rotation[i].c,&rotation[i].s);
    }

    vector<int> v(k);

    for(int i=0; i<k; i++){
        v[i] = i;
    }

    int result = 99999;
    do{
        for(int i=0; i<k; i++){
            move(rotation[v[i]]);
        }

        for(int i=1; i<=n; i++){
           int sum = 0;
           for(int j=1; j<=m; j++){
               sum+=temp2[i][j];
           }
           if( result > sum ) result = sum;
        }

        // temp2 - arr랑 똑같이 만들어주기
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++)
                temp2[i][j] = arr[i][j];
        }
    }while(next_permutation(v.begin(), v.end()));

    printf("%d\n",result);
    return 0;
}
