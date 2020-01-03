#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct chicken{
    int row;
    int col;
    int distance;
    chicken(){}
    chicken(int a,int b){row=a;col=b;}
    chicken(int a,int b,int c){row=a;col=b;distance=c;}
}chicken;

typedef struct home{
    int row;
    int col;
    vector <chicken> dis;
    int min;
    home(){}
    home(int a,int b,int c){row=a;col=b;min=c;}
}home;

int m,n;
int map[51][51];
vector<home> h;
vector<chicken> c;

int main(){
    vector<int> select;
    int min_citydis;
    scanf("%d %d",&m,&n);

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
            if(map[i][j] == 1){
                h.push_back(home(i,j,99999));
            }else if(map[i][j] == 2){
                c.push_back(chicken(i,j));
                select.push_back(0);
            }
        }
    }
    
    for(int i=0; i<n; i++){
        select[i]=1;
    }

    sort(select.begin(),select.end());
   
    for(int i=0; i<h.size(); i++){
        for(int j=0; j<c.size(); j++){
            int c_row = c[j].row;
            int c_col = c[j].col;
            int cal_dis = abs(h[i].row - c_row) + abs(h[i].col - c_col);
            h[i].dis.push_back(chicken(c_row,c_col,cal_dis));
            //printf("(%d %d) : %d\n", c_row,c_col,cal_dis);
        }
    }
    
    
    int result = 99999;
    do{
        min_citydis=0;
        for(int i=0; i<h.size(); i++){
            h[i].min=99999;
            for(int j=0; j<select.size(); j++){
                if(select[j] == 1){
                    if(h[i].min > h[i].dis[j].distance){
                        h[i].min = h[i].dis[j].distance;
                    }
                }
            }
            min_citydis += h[i].min;
        }
        
        if(result > min_citydis){
            result = min_citydis;
        }
    }while(next_permutation(select.begin(),select.end()));
    
    printf("%d",result);
    
    return 0;
}
