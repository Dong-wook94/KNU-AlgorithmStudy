#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int N;
stack<int> s;
vector<int> dir_order;
int Map[101][101];

int dir_x[4] = {1,0,-1,0};
int dir_y[4] = {0,-1,0,1};


void MakeDirOrder(int generation){
    s.push(dir_order[0]);
    for(int i=0;i<generation;i++){
        while(!s.empty()){
            int next_dir = (s.top()+1)%4;
            dir_order.push_back(next_dir);
            s.pop();
        }
        for(int j=0;j<dir_order.size();j++){
            s.push(dir_order[j]);
        }
    }
    while(!s.empty())
        s.pop();
}
void makeDragonCurve(int start_x,int start_y){
    int next_x = start_x;
    int next_y = start_y;
    
    Map[next_y][next_x] = 1;
    for(int i=0;i<dir_order.size();i++){
        next_x = next_x+dir_x[dir_order[i]];
        next_y = next_y+dir_y[dir_order[i]];
        
        Map[next_y][next_x]=1;
    }
    
}

void findSquare(){
    int cnt=0;
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            if(Map[j][i]==1 && Map[j+1][i]==1 && Map[j][i+1]==1 && Map[j+1][i+1]==1)
                cnt++;
        }
    }
    cout<<cnt<<"\n";
}
int main() {
    int start_x, start_y, dir,generation;
    
    cin>>N;
    
    for(int i=0;i<N;i++){
        cin>>start_x>>start_y>>dir>>generation;
        dir_order.push_back(dir);//방향 저장하여 순서대로 그리기 위함
        MakeDirOrder(generation);
        makeDragonCurve(start_x, start_y);
        dir_order.clear();
    }
    findSquare();
    return 0;
}
