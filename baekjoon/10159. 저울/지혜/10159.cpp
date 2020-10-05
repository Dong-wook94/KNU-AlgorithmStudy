//
//  10159.cpp
//  test
//
//  Created by 지혜 on 2020/10/05.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int d[101][101];

int main(){
    int n,m;
    cin >> n >> m;
    
    for(int i=1; i<=m; i++){
        int a,b;
        // a가 b보다 무거움 (a>b)
        cin >> a >> b;
        d[b][a] = 1;
    }
    
    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(d[i][k] && d[k][j]) d[i][j]=1;
            }
        }
    }
    
//    for(int i=1; i<=n; i++){
//        for(int j=1; j<=n; j++){
//            printf("%d ",d[i][j]);
//        }
//        printf("\n");
//    }
    
    for(int i=1; i<=n; i++){
        int cnt = 1;
        for(int j=1; j<=n; j++){
            if(d[i][j]) cnt++;
            if(d[j][i]) cnt++;
        }
        printf("%d\n",n-cnt);
    }
    return 0;
}
