#include <iostream>
#include <map>
#include <string>

using namespace std;

int parent[1000001];
int friendsNum[1000001];
map<string,int> mapIndex;
int numRelationship;
int collapsingFind(int x){
    if(x==parent[x])
        return x;
    return parent[x] = collapsingFind(parent[x]);
}

int simpleUnion(int x, int y){
    x = collapsingFind(x);
    y = collapsingFind(y);
    
    if(x!=y){
        if(friendsNum[x] <friendsNum[y]){
            parent[x] = y;
            friendsNum[y] += friendsNum[x];
            friendsNum[x] = 1;
            return friendsNum[y];
        }
        else{
            parent[y] = x;
            friendsNum[x] += friendsNum[y];
            friendsNum[y]=1;
            return friendsNum[x];
        }
        
        //friendsNum[s1] =1;
    }
    return friendsNum[x];
}

void Testcase(){
    cin>>numRelationship;
    int idx=0;
    int limit=0;
    if(2*numRelationship>1000000){
        limit =1000000;
    }
    else
        limit = 2*numRelationship;
    for(int i=0;i<=limit;i++){
        parent[i] = i;
        friendsNum[i] = 1;
    }
    for(int i=0;i<numRelationship;i++){
        string id1,id2;
        cin>>id1>>id2;
        if(mapIndex.count(id1)==0)
            mapIndex[id1]=idx++;
        if(mapIndex.count(id2)==0)
            mapIndex[id2]=idx++;
        cout<<simpleUnion(mapIndex[id1], mapIndex[id2])<<"\n";
    }
}

int main() {
    //freopen("input.txt","r",stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int testcase;
    cin>>testcase;
    
    for(int i=0;i<testcase;i++){
        Testcase();
    }
    return 0;
}
