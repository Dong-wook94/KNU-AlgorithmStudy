//
//  parenthesisConversion.cpp
//  test
//
//  Created by 지혜 on 2020/04/05.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int checkCorrect(string s){
    stack<char> check;
    for(int i=0; i<s.length(); i++){
        if(s[i] == '(') check.push('(');
        else{
            if(check.empty()) return 0;
            else check.pop();
        }
    }
    return 1;
}

string solution(string p) {
    string answer = "";
    
    if(p.length() == 0 ) return answer;
    else{
        // 올바른 괄호 문자열 인지 check
        if(checkCorrect(p) == 1){
            return p;
        }else{
            // u v 로 나누기
            string u,v;
            stack<char> check;
            int count = 0;
            if(p[0] == '('){
                for(int i=0; i<p.length(); i++){
                    if(p[i] == ')'){
                        check.pop();
                        if(check.empty()){
                            count = i;
                            break;
                        }
                    }else check.push('(');
                }

            }else{
                for(int i=0; i<p.length(); i++){
                    if(p[i] == '('){
                        check.pop();
                        if(check.empty()){
                            count = i;
                            break;
                        }
                    }else check.push(')');
                }
            }
            u = p.substr(0,count+1); // 0번부터 count+1개 반환
            v = p.substr(count+1); // count+1부터 마지막까지 반환
//            cout << u;
//            printf(" / ");
//            cout << v;
            if(checkCorrect(u) == 1){
                string returnV = solution(v);
                u += returnV;
                answer = u;
            }else{
                answer+="(";
                string returnV = solution(v);
                answer+=returnV;
                answer+=")";
                string temp = "";
                for(int i=1; i<u.length()-1; i++){
                    if(u[i] == '(' ) temp+=")";
                    else temp+="(";
                }
                answer+=temp;
            }
        }
    }
    return answer;
}

int main(){
    string result = solution("))()))((((");
//    string result = solution(")(");
    cout << result;
    cout << endl;
    return 0;
}

