#include <stdio.h>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

int dir_r[4] = {0,0,-1,1};
int dir_c[4] = {1,-1,0,0};

int main(){
    string input;
    string correct = "123456780";
    
    for(int i=0; i<9; i++){
        int a;
        scanf("%d",&a);
        input += a+'0';
    }
    
//    cout << input;
    
    set<string> visit;
    queue<pair<string,int>> q;
    
    visit.insert(input);
    q.push(make_pair(input,0));
    
    while(!q.empty()){
        string cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        
//        cout << cur;
//        printf("\n");
        
        if(cur == correct){
            printf("%d\n",cnt);
            return 0;
        }
        
        // 0 자리 찾기
        int zeroPos = 0;
        for(int i=0; i<cur.size(); i++){
            if(cur[i] == '0') zeroPos = i;
        }
        
        // row,col 변환
        int row = zeroPos/3;
        int col = zeroPos%3;
        
        // 움직일 수 있는 위치 찾기
        for(int i=0; i<4; i++){
            int nextR = row + dir_r[i];
            int nextC = col + dir_c[i];
            if(nextR < 0 || nextR >=3 || nextC < 0 || nextC >=3 ) continue;
            int nextPos = nextR*3+nextC;
            string next = cur;
            swap(next[zeroPos],next[nextPos]);
            if(visit.find(next) == visit.end()){
                visit.insert(next);
                q.push(make_pair(next,cnt+1));
            }
        }
    }
    
    printf("-1\n");
    return 0;
}
