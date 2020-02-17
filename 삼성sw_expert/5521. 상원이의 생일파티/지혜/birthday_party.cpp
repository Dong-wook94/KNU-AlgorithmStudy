#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef struct friends{
    int pair1;
    int pair2;
    friends(){}
    friends(int a,int b){pair1 = a; pair2 = b;}
}friends;

int main(){
    int t;

    scanf("%d", &t);
    for(int i=1; i<=t; i++){
        int n,m; // n명 있음 1번은 상원이~!!! m = 친한 친구 관계 수
        int visit[501]={0};
        vector<friends> f;
        int result = 0;

        scanf("%d %d",&n,&m);

        for(int j=0; j<m; j++){
            int a,b;
            scanf("%d %d",&a,&b);
            f.push_back(friends(a,b));
        }

        queue<int> q;
        q.push(1);
        visit[1] = 1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int j=0; j<f.size(); j++){
                if(f[j].pair1 == cur && visit[f[j].pair2] == 0){
                    visit[f[j].pair2] = 1;
                    result++;
                    if(cur == 1){
                        q.push(f[j].pair2);
                    }
                }
                if(f[j].pair2 == cur && visit[f[j].pair1] == 0){
                    visit[f[j].pair1] = 1;
                    result++;
                    if(cur == 1){
                        q.push(f[j].pair1);
                    }
                }
            }
        }
        printf("#%d %d\n",i,result);
    }
    return 0;
}
