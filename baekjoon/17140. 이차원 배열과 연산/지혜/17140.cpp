#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct countNum{
    int number;
    int count;
    countNum(){}
    countNum(int a,int b){number=a;count=b;}
}countNum;

int rSize = 3;
int cSize = 3;
int r,c,k;
int matrix[101][101]={0};

bool cmp(countNum &a, countNum &b){
    if(a.count == b.count ){
        return a.number < b.number;
    }
    return a.count<b.count;
}

void changMatrix(int newM[101][101]){
    for(int i=1; i<=rSize; i++){
        for(int j=1; j<=cSize; j++){
            matrix[i][j] = newM[i][j];
        }
    }
}

int main(){
    
    scanf("%d %d %d",&r,&c,&k);
    for(int i=1; i<=3; i++){
        for(int j=1; j<=3; j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    int result = 0;
    int end = 0;
    
    if(matrix[r][c] == k ){
        printf("%d\n",result);
        return 0;
    }else{
        while(result<=101){
            if(end == 1) break;
            result++;
            int newMatrix[101][101]={0};
            if(rSize >= cSize){
                // 모든 행 계산
                int newCSize = 0;
                for(int i=1; i<=rSize; i++){
                    vector<countNum> c;
                    int countMatrix[101]={0};
                    for(int j=1; j<=cSize; j++){
                        if(countMatrix[matrix[i][j]] == 0 && matrix[i][j] != 0) c.push_back(countNum(matrix[i][j],0));
                        countMatrix[matrix[i][j]]+=1;
                    }
                    
                    for(int j=0; j<c.size(); j++){
                        c[j].count = countMatrix[c[j].number];
                    }
                    
                    sort(c.begin(),c.end(),cmp);
                    
                    int rowCSize = (int)c.size()*2;
                    if(rowCSize > 100 ) rowCSize = 100;
                    if(newCSize < rowCSize ) newCSize = rowCSize;
                    
                    int index = 1;
                    for(int j=0; j<c.size(); j++){
                        if(index > rowCSize) break;
                        newMatrix[i][index] = c[j].number;
                        newMatrix[i][index+1] = c[j].count;
                        index+=2;
                    }
                }
                if(cSize < newCSize) cSize = newCSize;
            }else{
                // 모든 열 계산
                int newRSize = 0;
                for(int i=1; i<=cSize; i++){
                    vector<countNum> c;
                    int countMatrix[101]={0};
                    for(int j=1; j<=rSize; j++){
                        if(countMatrix[matrix[j][i]]== 0 && matrix[j][i] != 0)
                            c.push_back(countNum(matrix[j][i],0));
                        countMatrix[matrix[j][i]]+=1;
                    }
                    
                    for(int j=0; j<c.size(); j++){
                        c[j].count = countMatrix[c[j].number];
                    }
                    
                    sort(c.begin(),c.end(),cmp);
                    
                    int colRSize = (int)c.size()*2;
                    if(colRSize > 100 ) colRSize = 100;
                    if(newRSize < colRSize ) newRSize = colRSize;
                    
                    int index = 1;
                    for(int j=0; j<c.size(); j++){
                        if(index > colRSize) break;
                        newMatrix[index][i] = c[j].number;
                        newMatrix[index+1][i] = c[j].count;
                        index+=2;
                    }
                
                }
                if(rSize < newRSize) rSize = newRSize;
            }
            
            changMatrix(newMatrix);
            if(matrix[r][c] == k ) end = 1;
        }
    }
    if(result > 100 ) result = -1;
    printf("%d\n",result);
    
    return 0;
}
