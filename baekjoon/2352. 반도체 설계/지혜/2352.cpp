//
//  2352.cpp
//  test
//
//  Created by 지혜 on 2020/05/17.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
using namespace std;


int main(){
    int arry[40000]={0};
    int n;
    vector<int> v;
    scanf("%d",&n);

    for(int i=1; i<=n; i++){
        scanf("%d",&arry[i]);
    }

    v.push_back(arry[1]);
    for(int i=2; i<=n; i++){
        if(v.back() < arry[i]) v.push_back(arry[i]);
        else{
            int last = (int)v.size();
            for(int j=0; j<last; j++){
                if(v[j] >= arry[i] ){
                    v[j] = arry[i];
                    break;
                }
            }
        }
    }
    printf("%d\n",(int)v.size());
    return 0;
}
