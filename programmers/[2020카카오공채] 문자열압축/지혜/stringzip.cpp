//
//  stringzip.cpp
//  test
//
//  Created by 지혜 on 2020/03/22.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
    int answer = 99999;
    int zipLength = 1;
    int stringLength = (int)s.length();

    if(stringLength == 1){
        answer = 1;
        return answer;
    }
    while(1){
        if(zipLength >= stringLength ) break;
        string zipS;
        string check = s.substr(0 ,zipLength);
        int start = zipLength;
        int count = 1;
        while(1){
            if(start >= stringLength ){
                if(count == 1) zipS+=check;
                else{
                    zipS+=to_string(count);
                    zipS+=check;
                }
                break;
            }
            string cmp = s.substr(start, zipLength);
            if(check.compare(cmp) == 0 ){
                count+=1;
            }else{
                if(count == 1){
                    zipS+=check;
                }else{
                    zipS+=to_string(count);
                    zipS+=check;
                }
                check.clear();
                check = cmp;
                count = 1;
            }
            start += zipLength;
        }
        if(answer > zipS.length()) answer = (int)zipS.length();
        zipLength += 1;
    }
    
    return answer;
}

int main(){
    int result = solution("xababcdcdababcdcd");
    printf("result : %d\n",result);
}
