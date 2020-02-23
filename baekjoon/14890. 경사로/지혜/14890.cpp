#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
int n,l;
int map[100][100];
int result = 0;

int check_slope(int array[] ,int startIdx, int endIdx){
    
    for(int i=startIdx; i<=endIdx; i++){
        if(array[i] == 1 ){
            return 0;
        }
    }
    return 1;
}

int main(){
    
    scanf("%d %d",&n,&l);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d",&map[i][j]);
        }
    }
    
    // 가로
    for(int i=0; i<n; i++){
        vector<int> change;
        int check=0;
        for(int j=0; j<n-1; j++){
            if(abs(map[i][j]-map[i][j+1]) == 1){
                change.push_back(j+1);
            }else if(abs(map[i][j]-map[i][j+1]) >=2){
                change.clear();
                check = 1;
                break;
            }
        }
        
        if(check == 1) continue;
        if(change.size() == 0) result+=1;
        else if(change.size() == 1){
            if(map[i][0] < map[i][change[0]] && change[0] >= l) result+=1;
            if(map[i][0] > map[i][change[0]] && n-change[0] >= l) result +=1;
        }
        else{
            int slope[100] = {0};
            
            for(int k=0; k<change.size(); k++){
                if(k==0){
                    // 앞 경사로
                    if(map[i][0] < map[i][change[k]]){
                        if(change[k] < l){
                            check = 1;
                            break;
                        }else{
                            for(int s=change[k]-l; s<=change[k]-1; s++){
                                slope[s] = 1;
                            }
                        }
                    }
                    
                    //뒷 경사로
                    if(map[i][0] > map[i][change[k]]){
                        if(change[k+1] - change[k] < l){
                            check = 1;
                            break;
                        }else{
                            for(int s=change[k]; s<change[k]+l; s++){
                                slope[s]=1;
                            }
                        }
                    }
                    
                }else if(k == change.size()-1){
                    if(map[i][change[k]-1] > map[i][change[k]]){
                        // 앞이 더 높음
                        // 뒷 경사로
                        if(n-change[k] < l ){
                            check =1; break;
                        }else{
                            for(int s=change[k]; s<change[k]+l; s++){
                                slope[s]=1;
                            }
                        }
                    }else{
                        // 뒤가 더 높음
                        // 앞 경사로
                        if(change[k] - change[k-1] < l){
                            check =1; break;
                        }else{
                            if(check_slope(slope, change[k]-l, change[k]-1)){
                                for(int s=change[k]-l; s<=change[k]-1; s++){
                                    slope[s] = 1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }
                }else{
                    if(map[i][change[k]-1] > map[i][change[k]]){
                        // 앞이 더 높음
                        // 뒷 경사로
                        if(change[k+1] - change[k] < l ){
                            check =1; break;
                        }else{
                            if(check_slope(slope,change[k],change[k]+l-1)){
                                for(int s=change[k]; s<change[k]+l; s++){
                                    slope[s]=1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }else{
                        // 뒤가 더 높음
                        // 앞 경사로
                        if(change[k] - change[k-1] < l){
                            check =1; break;
                        }else{
                            if(check_slope(slope, change[k]-l, change[k]-1)){
                                for(int s=change[k]-l; s<=change[k]-1; s++){
                                    slope[s] = 1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }
                }
            }
            
            if(check == 0) result+=1;
        }
        
    }
    
    // 세로
    for(int i=0; i<n; i++){
        vector<int> change;
        int check=0;
        for(int j=0; j<n-1; j++){
            if(abs(map[j][i]-map[j+1][i]) == 1){
                change.push_back(j+1);
            }else if(abs(map[j][i]-map[j+1][i]) >=2){
                change.clear();
                check = 1;
                break;
            }
        }
        
        if(check == 1)continue;
        if(change.size() == 0) result+=1;
        else if(change.size() == 1){
            if(map[0][i] < map[change[0]][i] && change[0] >= l) result+=1;
            if(map[0][i] > map[change[0]][i] && n-change[0] >= l) result +=1;
        }
        else{
            int slope[100] = {0};
            
            for(int k=0; k<change.size(); k++){
                if(k==0){
                    // 앞 경사로
                    if(map[0][i] < map[change[k]][i]){
                        if(change[k] < l){
                            check = 1;
                            break;
                        }else{
                            for(int s=change[k]-l; s<=change[k]-1; s++){
                                slope[s] = 1;
                            }
                        }
                    }
                    
                    //뒷 경사로
                    if(map[0][i] > map[change[k]][i]){
                        if(change[k+1] - change[k] < l){
                            check = 1;
                            break;
                        }else{
                            for(int s=change[k]; s<change[k]+l; s++){
                                slope[s]=1;
                            }
                        }
                    }
                    
                }else if(k == change.size()-1){
                    if(map[change[k]-1][i] > map[change[k]][i]){
                        // 앞이 더 높음
                        // 뒷 경사로
                        if(n-change[k] < l ){
                            check =1; break;
                        }else{
                            for(int s=change[k]; s<change[k]+l; s++){
                                slope[s]=1;
                            }
                        }
                    }else{
                        // 뒤가 더 높음
                        // 앞 경사로
                        if(change[k] - change[k-1] < l){
                            check =1; break;
                        }else{
                            if(check_slope(slope, change[k]-l, change[k]-1)){
                                for(int s=change[k]-l; s<=change[k]-1; s++){
                                    slope[s] = 1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }
                }else{
                    if(map[change[k]-1][i] > map[change[k]][i]){
                        // 앞이 더 높음
                        // 뒷 경사로
                        if(change[k+1] - change[k] < l ){
                            check =1; break;
                        }else{
                            if(check_slope(slope,change[k],change[k]+l-1)){
                                for(int s=change[k]; s<change[k]+l; s++){
                                    slope[s]=1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }else{
                        // 뒤가 더 높음
                        // 앞 경사로
                        if(change[k] - change[k-1] < l){
                            check =1; break;
                        }else{
                            if(check_slope(slope, change[k]-l, change[k]-1)){
                                for(int s=change[k]-l; s<=change[k]-1; s++){
                                    slope[s] = 1;
                                }
                            }else{
                                check=1; break;
                            }
                        }
                    }
                }
            }
            
            if(check == 0) result+=1;
        }
        
    }
    printf("%d\n",result);
    return 0;
}
