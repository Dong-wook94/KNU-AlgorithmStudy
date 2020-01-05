#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<int>> g;
vector<int> visit;
int ver,edge,start;
queue<int> q;

void dfs(int v){
    visit[v] = 1;
    printf("%d ",v);
    for(int i=0; i<g[v].size(); i++){
        if(!visit[g[v][i]]){
            dfs(g[v][i]);
        }
    }
}

void bfs(){
    q.push(start);
    visit[start] = 1;
    while(!q.empty()){
        int a=q.front();
        printf("%d ",a);
        q.pop();
        for(int i=0; i<g[a].size(); i++){
            if(visit[g[a][i]] == 0){
                q.push(g[a][i]);
                visit[g[a][i]] = 1;
            }
        }
    }

}

int main(){

    scanf("%d %d %d",&ver,&edge,&start);
    g.assign(ver+1,vector<int>(0,0));
    visit.assign(ver+1,0);

    for(int i=1; i<=edge; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i=1; i<=ver; i++){
        sort(g[i].begin(),g[i].end());
    }

    dfs(start);
    printf("\n");
    bfs();

    return 0;
}
