#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
int row_size;
int col_size;
int Map[301][301];
bool visited[301][301];


typedef struct Ice{
    int height;
    int row;
    int col;
    Ice(int h,int r,int c){
        height =h;
        row =r;
        col =c;
    }
}Ice ;

vector<Ice> ices;
int dir_row[4] = {-1,0,1,0};
int dir_col[4] = {0,1,0,-1};
int connected_cnt=0;
bool cmp(Ice &a, Ice &b){
    return a.height>b.height;
}

int getReducedHeight(Ice ice){
    int cnt=0;
    for(int i=0;i<4;i++){
        int next_row = ice.row+dir_row[i];
        int next_col = ice.col+dir_col[i];
        if(Map[next_row][next_col]<=0){
            cnt++;
        }
    }
    return cnt;
}

void meltIces(){
    for(int i=0;i<ices.size();i++){
        int reduced_height = getReducedHeight(ices[i]);
        ices[i].height -=reduced_height;
    }
    for(int i=0;i<ices.size();i++){
        Map[ices[i].row][ices[i].col] =ices[i].height<0?0:ices[i].height;
    }
}

void initVisited(){
    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            visited[i][j] = false;
        }
    }
}
void dfs(int row, int col){
    for(int i=0;i<4;i++){
        int next_row = row + dir_row[i];
        int next_col = col + dir_col[i];
        if(Map[next_row][next_col]>0 && visited[next_row][next_col]==false){
            connected_cnt++;
            visited[next_row][next_col]=true;
            dfs(next_row,next_col);
        }
    }
}

int main() {
    cin>>row_size>>col_size;
    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            cin>>Map[i][j];
            if(Map[i][j] !=0){
                ices.push_back(Ice(Map[i][j],i,j));
            }
        }
    }
    int year=0;
    while(1){
        year++;
        meltIces();
//        cout<<year<<"년"<<endl;
//        for(int i=0;i<row_size;i++){
//            for(int j=0;j<col_size;j++){
//                cout<<Map[i][j]<<" ";
//            }
//            cout<<endl;
//        }
        sort(ices.begin(),ices.end(),cmp);
        while(!ices.empty()&&ices[ices.size()-1].height<=0){
            ices.pop_back();
        }
        if(ices.empty()){
            cout<<"0"<<endl;
            return 0;
        }
        connected_cnt=1;
        initVisited();
        visited[ices[0].row][ices[0].col]=true;
        dfs(ices[0].row,ices[0].col);
        if(connected_cnt<ices.size()){
//            cout<<connected_cnt<<","<<ices.size()<<endl;
            cout<<year<<endl;
            return 0;
        }
    }
    
    
    
    return 0;
}
