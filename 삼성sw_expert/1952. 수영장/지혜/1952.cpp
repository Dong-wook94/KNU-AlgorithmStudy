
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int swim[12];
int daysum = 0;
int day,month,month3,year;
int result = 9999999;

void dfs(int m, int pay){
    
    if(m >= 12){
        result = min(result, pay);
        return;
    }

    if(swim[m]){
        int curDay = swim[m];
        dfs(m+1,pay+month);
        dfs(m+1,pay+curDay*day);
        int check =0;
        for(int i=m; i<m+3; i++){
            if(swim[m]) check++;
        }
        if(check == 3) dfs(m+3,pay+month3);
    }else dfs(m+1,pay);
}

int main(){
    
    int testCase;
    cin >> testCase;
    
    for(int testN=1; testN<=testCase; testN++){
        cin >> day >> month >> month3 >> year;
        for(int i=0; i<12; i++){
            cin >> swim[i];
            daysum+=swim[i];
        }
        result = min(result, daysum*day);
        dfs(0,0);
        result = min(result, year);
        printf("#%d %d\n",testN, result);
        result = 9999999;
    }
    return 0;
}
