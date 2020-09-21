//
//  1916.cpp
//  test
//
//  Created by 지혜 on 2020/09/21.
//  Copyright © 2020 지혜. All rights reserved.
// 다익스트라 ㅎㅇㅎㅇ~~ priority queue 이용하기

#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;
typedef struct Bus{
    int end;
    int time;
    Bus(){}
    Bus(int a,int b){end=a;time=b;}
}Bus;

struct cmp{
    bool operator()(Bus a,Bus b){
        return a.time < b.time;
    }
};

int main(){
    int n,m;
    vector<vector<Bus>> v;
    priority_queue<Bus, vector<Bus>, cmp> pq;
    int s_city,e_city;
    
    // 스캔받기!
    cin >> n >> m;
    v.assign(n+1, vector<Bus>());
    
    for(int i=0; i<m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        v[a].push_back(Bus(b,c));
    }
    cin >> s_city >> e_city;
    
    // 초기화!
    int result[n+1];
    for(int i=1; i<n+1; i++){
        if(i == s_city) result[i] = 0;
        else result[i] = INT_MAX;
    }
    
    pq.push(Bus(s_city,0));
    while(!pq.empty()){
        Bus find = pq.top();
        pq.pop();
        for(int i=0; i<v[find.end].size(); i++){
            int sum = v[find.end][i].time + find.time;
            if(result[v[find.end][i].end] > sum){
                result[v[find.end][i].end] = sum;
                pq.push(Bus(v[find.end][i].end,sum));
            }
        }
    }
    
    cout << result[e_city] << endl;
    return 0;
}
