#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

int main()
{
    int num;
    int s[20][20];
    vector<int> select;
    vector<int> team_s;
    vector<int> team_l;

    scanf("%d",&num);
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            scanf("%d",&s[i][j]);
        }
    }

    for(int i=0; i<num; i++){
        if(i<num/2){
            select.push_back(1);
        }else{
            select.push_back(0);
        }
    }

    sort(select.begin(),select.end());

    int result=99999;
    do{
        for(int i=0; i<num; i++){
            if(select[i] == 1){
                // start팀
                team_s.push_back(i);
            }else{
                // link팀
                team_l.push_back(i);
            }
        }

        int start = 0;
        int link = 0;
        for(int i=0; i<team_s.size(); i++){
            for(int j=0; j<team_s.size(); j++){
                if(i != j){
                    start+= s[team_s[i]][team_s[j]];
                    link+= s[team_l[i]][team_l[j]];
                }
            }
        }

        int gap = abs(start - link);
        if(result > gap){
            result = gap;
        }
        team_s.clear();
        team_l.clear();

    }while(next_permutation(select.begin(),select.end()));

    printf("%d\n",result);
    return 0;
}
