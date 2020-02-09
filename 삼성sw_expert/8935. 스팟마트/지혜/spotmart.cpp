#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;

int test_num;
int n,m;
int A[3001];
vector<int> B_list;
int select_B[101]={0};
int B[101];
int result = 0;


int select_snack(int idxA, int idxB,int sum,int mode){
    
    printf("%d %d %d %d\n",idxA,idxB,mode,sum);
    if(mode ==  0 && idxA >= n) return sum;
    if(mode == 1 &&  idxB >= m  ) return sum;
    if(mode == 1 && idxA-1 >= n) return sum;
    if(mode == 0){
        return max(select_snack(idxA+2,idxB, sum+A[idxA], 0), select_snack(idxA+2,idxB, sum+A[idxA], 1));
    }else{
        return max(select_snack(idxA+1,idxB+1,sum+B_list[idxB], 0) , select_snack(idxA,idxB+2, sum+B_list[idxB], 1));
    }
    
}

void make_Blist(int cnt){
    
    if(cnt == m){
        int r = max(select_snack(0,0,0,0) , select_snack(0,0,0,1));
//        printf("%d\n",r);
        if(result < r ) result = r;
        return;
    }
    
    for(int i=0; i<m; i++){
        if(select_B[i] == 1) continue;
        select_B[i] = 1;
        B_list.push_back(B[i]);
        make_Blist(cnt+1);
        B_list.pop_back();
        select_B[i] = 0;
    }
}

int main(){
    
    scanf("%d",&test_num);
    for(int i=1; i<=test_num; i++){
        scanf("%d",&n);
        for(int j=0; j<n; j++){
            scanf("%d",&A[j]);
        }
        scanf("%d",&m);
        for(int j=0; j<m; j++){
            scanf("%d",&B[j]);
        }
        
        make_Blist(0);
        printf("#%d %d\n",i,result);
    }
    return 0;
}
