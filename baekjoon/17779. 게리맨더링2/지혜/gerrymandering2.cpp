#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct land{
    int population;
    int ward;
}land;

typedef struct devide_input{
    int x;
    int y;
    int d1;
    int d2;
    devide_input(){}
    devide_input(int a,int b,int c,int d){x=a;y=b;d1=c;d2=d;}
}devide_input;

int n;
land a[21][21];
vector<devide_input> d;

void clear_ward(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            a[i][j].ward = 0;
        }
    }
}

void devide(int x, int y, int d1, int d2){

    for(int r=1; r<=n; r++){
        for(int c=1; c<=n; c++){
            if(r < x+d1 && c <= y){
                a[r][c].ward = 1;
            }else if( r <= x+d2 && y<c){
                a[r][c].ward = 2;
            }else if( x+d1<= r && c<y-d1+d2){
                a[r][c].ward = 3;
            }else if( x+d2<r && y-d1+d2<=c){
                a[r][c].ward = 4;
            }
        }
    }

    // 5구역 넣기
    for(int i=0; i<=d1; i++){
        a[x+i][y-i].ward = 5;
        a[x+d2+i][y+d2-i].ward = 5;
    }
    for(int i=0; i<=d2; i++){
        a[x+i][y+i].ward = 5;
        a[x+d1+i][y-d1+i].ward =5;
    }
    for(int i=x+1; i<=n; i++){
        vector<int> check;
        for(int j=1; j<=n; j++){
            if(a[i][j].ward == 5){
                check.push_back(j);
            }
        }
        if(check.size() > 0 ){
            for(int k=check[0]; k<check[1]; k++){
                a[i][k].ward = 5;
            }
            check.clear();
        }
    }

}

int main(){

    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&a[i][j].population);
        }
    }

    for(int d1=1; d1<=n; d1++){
        for(int d2=1; d2<=n; d2++){
            for(int x=1; x<n; x++){
                for(int y=2; y<n; y++){
                    if( x+d1+d2 <= n && y-d1 >= 1 && y+d2 <= n)
                        d.push_back(devide_input(x,y,d1,d2));
                }
            }
        }
    }

    int result = 99999;
    for(int i=0; i<d.size(); i++){

        devide(d[i].x,d[i].y,d[i].d1,d[i].d2);

        vector<int> sum;
        for(int i=0; i<5; i++){
            sum.push_back(0);
        }

        // 인구수 더하기
        for(int r=1; r<=n; r++){
            for(int c=1; c<=n; c++){
                if(a[r][c].ward == 1){
                    sum[0]+=a[r][c].population;
                }else if(a[r][c].ward == 2){
                    sum[1]+=a[r][c].population;
                }else if(a[r][c].ward == 3){
                    sum[2]+=a[r][c].population;
                }else if(a[r][c].ward == 4){
                    sum[3]+=a[r][c].population;
                }else sum[4]+=a[r][c].population;
            }
        }
        sort(sum.begin(),sum.end());
        int gap = sum[4]-sum[0];
        if(result > gap) result=gap;
        sum.clear();
        clear_ward();
    }
    printf("%d",result);
    return 0;
}
