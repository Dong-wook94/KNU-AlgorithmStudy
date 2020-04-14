#include <iostream>
#include <vector>
#include <queue>
#define MAX 100001
using namespace std;

int N,K,M;

vector<int> graph[MAX+1000];
bool visited[MAX+1000];

typedef struct Info{
    int station;
    int cnt;
    Info(int s, int c){station =s;cnt=c;}
}Info;

int BFS(){
    queue<Info> q;
    q.push(Info(1,1));
    visited[1] = true;
    
    while(!q.empty()){
        Info cur = q.front();
        q.pop();
        if(cur.station==N){
            return cur.cnt;
        }
        for(int i=0;i<graph[cur.station].size();i++){
            int next= graph[cur.station][i];
            if(!visited[next]){
                if(next>N){ //가상역
                    q.push(Info(next,cur.cnt));
                }
                else{
                    visited[next] = true;
                    q.push(Info(next,cur.cnt+1));
                }
               
            }
        }
    }
    return -1;
}

int main() {
    cin>>N>>K>>M;
    for(int i=1;i<=M;i++){
        for(int j=0;j<K;j++){
            int a;
            cin>> a;
            graph[a].push_back(i+N);
            graph[i+N].push_back(a);
        }
    }
    
    cout<<BFS()<<endl;
    
    return 0;
}
