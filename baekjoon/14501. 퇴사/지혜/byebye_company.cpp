#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct job{
    int day;
    int time;
    int profit;
    job(){}
    job(int a,int b,int c){day=a;time=b;profit=c;}
}job;

int n; // n일까지 일함. n+1일 퇴사
vector<job> j;
int s[16]; // n은 1~15사이

int schedule(int d){
    if(d == n+1) return 0;
    if(d > n+1) return -9999;
    if(s[d] > 0) return s[d];
    return s[d] = max( schedule(d+1), schedule(d+j[d-1].time)+j[d-1].profit );
}

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        j.push_back(job(i,a,b)); //실제 index랑 day랑 차이남
    }
    schedule(1);
    printf("%d\n",s[1]);
}
