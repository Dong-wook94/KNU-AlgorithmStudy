#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>

using namespace std;

deque<int> dq;

bool Permutation(vector<int> dist,int cnt){
    sort(dist.begin(),dist.end()); //큰게 앞에오게
    do{
        int start_idx = 0;
//        cout<<"dq"<<" : ";
//        for(int i=0;i<dq.size();i++)
//            cout<<dq[i]<<" ";
//        cout<<endl;
        for(int i=0;i<cnt;i++){
            int able_dist =dq[start_idx]+dist[i];
//            cout<<start_idx<<","<<dist[i]<<endl;
            int j=start_idx;
            for(;j<dq.size();){
                if(dq[j]<=able_dist){
                    j++;
                }
                else{
                    start_idx = j;
                    break;
                }
            }
            if(j==dq.size()){//끝까지 간경우
//                cout<<"success"<<endl;
//                for(int i=0;i<dist.size();i++){
//                    cout<<dist[i]<<" ";
//                }
//                cout<<"\n";
                cout<<cnt<<endl;
                return true;
            }
        }
    }while(next_permutation(dist.begin(), dist.end()));
    
    return false;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 0;
    //cout<<"!!!"<<endl;

 
    
    //한번씩 시작지점이 되도록
    //앞에서 한번 뒤에서한번 시작해 줄거임.
    for(int i=1;i<=dist.size();i++){
        for(int i=0;i<weak.size();i++){
             dq.push_back(weak[i]);
        }
        for(int j=0;j<=weak.size();j++){
            if(Permutation(dist,i))
                return i;
            int temp = dq.front();
            temp += n;
            dq.pop_front();
            dq.push_back(temp);
        }
        dq.clear();
        
    }
    
    return -1;
}

int main(){
    int n = 12;
    vector<int> weak = {1,3,4,9,10};
    vector<int> dist = {3,5,7};
    cout<<solution(n,weak,dist)<<endl;
}
