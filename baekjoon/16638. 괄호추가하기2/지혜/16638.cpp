//
//  16638.cpp
//  test
//
//  Created by 지혜 on 2020/04/04.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>
#include <limits.h>
using namespace std;

int n;
int result = INT_MIN;
string s;

int check_operator(int cur){
    if(s[cur] == '*' || s[cur] == '+' || s[cur] == '-') return 0;
    return 1;
}

int priority(char c){
    if(c == '+' || c == '-'){
        return 2;
    }else if(c == '*'){
        return 3;
    }else if(c == '('){
        return 1;
    }
    return -1;
}

int cmpPriority(char a, char b){
    int p1 = priority(a);
    int p2 = priority(b);
    if( p1 >= p2) return 1;
    else return 0;
}

int calculate(){
    string changePostfix="";
    stack<char> st;

    // postfix로 변환
    for(int i=0; i<s.length(); i++){
        if(s[i] == '(') st.push(s[i]);
        else if( s[i] == ')'){
            while(1){
                char top = st.top();
                st.pop();
                if(top == '(') break;
                else changePostfix += top;
            }
        }else if(check_operator(i) == 1){
            changePostfix+=s[i];
        }else{
            // 연산자일 때
            while(!st.empty() && cmpPriority(st.top(),s[i])){
                changePostfix+=st.top();
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while (!st.empty()) {
        char top = st.top();
        st.pop();
        changePostfix+=top;
    }
    
//    printf("~");
//    cout << changePostfix;
//    cout << endl;
    
    // 찐 계산
    int value = 0;
    stack<int> cal;
    for(int i=0; i<changePostfix.length(); i++){
        if(changePostfix[i] == '+' || changePostfix[i] == '-' || changePostfix[i] == '*'){
            int b = cal.top();
            cal.pop();
            int a = cal.top();
            cal.pop();
            switch (changePostfix[i]) {
                case '+':
                    cal.push(a+b);
                break;
                case '-':
                    cal.push(a-b);
                break;
                case '*':
                    cal.push(a*b);
                break;
                default:
                break;
            }
        }else{
            cal.push(changePostfix[i]-'0');
        }
    }
    value = cal.top();
//    printf("value : %d\n",value);
    return value;
}

void add_bracket(int type, int cur){
    
    if(cur >= s.size()-1){
        if(type == 1) s.insert(s.size(),")");
//        cout << s;
//        cout << endl;
        int value = calculate();
        if(result < value) result = value;
        return;
    }
    
    if(s[cur] == '*' || s[cur] == '+' || s[cur] == '-' ){
        add_bracket(type,cur+1);
    }else{
        string temp = s;
        if(type == 0){
            // ( 추가
            for(int i=cur; i<s.size(); i++){
                if(check_operator(i) == 1){
                    s.insert(i,"(");
                    add_bracket(1,i+2);
                    s = temp;
                }
            }
        }else{
            // ) 추가
            for(int i=cur; i<s.size(); i++){
                if(check_operator(i) == 1){
                    s.insert(i+1,")");
                    add_bracket(0,i+2);
//                    s = temp;
                    break;
                }
            }
        }
    }
}

int main(){
    
    cin >> n;
    cin >> s;
    add_bracket(0,0);
    printf("%d\n",result);
    return 0;
}
