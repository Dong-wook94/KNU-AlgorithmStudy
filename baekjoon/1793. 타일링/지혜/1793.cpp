#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

int tile[251]={0};
string tile2[251];



string bigNumAdd(string a , string b){
    vector<int> newA,newB,result;
    
    for(int i=0; i<a.length(); i++){
        newA.push_back(a.at(i) - '0');
    }
    
    for(int i=0; i<b.length(); i++){
        newB.push_back(b.at(i) - '0');
    }
    
    int nnA,nnB;
    int carry=0;
    while(!newA.empty() && !newB.empty()){
        nnA = newA.back();
        newA.pop_back();
        nnB = newB.back();
        newB.pop_back();
        result.push_back((nnA+nnB+carry)%10);
        carry = (nnA+nnB+carry)/10;
    }
    
    if(newA.empty()){
        while(!newB.empty()){
            nnB = newB.back();
            newB.pop_back();
            
            result.push_back((nnB + carry)%10);
            carry = (nnB + carry) / 10;
        }
    }else{
        while(!newA.empty()){
            nnA = newA.back();
            newA.pop_back();
            
            result.push_back((nnA + carry)%10);
            carry = (nnA + carry) / 10;
        }
    }
    
    if(carry) result.push_back(1);
    
    string real_result;
    for(int i=(int)result.size()-1; i>=0; i--){
        real_result += to_string(result[i]);
    }
    
    return real_result;
}

string mult2(string a){
    return bigNumAdd(a,a);
}

//int dp(int n){
//    if(n == 0) return 1;
//    if(tile[n] > 0 ) return tile[n];
//    return tile[n] = dp(n-1) + 2*dp(n-2);
//}



int main(){
    
//    tile[0]=1;
//    tile[1]=1;
//    tile[2]=3;
//
//    while(scanf("%d",&n) == 1){
//        printf("%d",dp(n));
//    }
    tile2[0]= 1+'0';
    tile2[1] = 1+'0';
    tile2[2] = 3+'0';
    
    for(int i=3; i<=250; i++){
        tile2[i] = bigNumAdd(tile2[i-1],mult2(tile2[i-2]));
    }

    int n;
    while(cin >> n)
        cout << tile2[n] << endl;
    return 0;
}
