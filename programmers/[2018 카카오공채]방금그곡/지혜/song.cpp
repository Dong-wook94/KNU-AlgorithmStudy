//
//  song.cpp
//  test
//
//  Created by 지혜 on 2020/04/07.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
typedef struct song{
    int t;
    string name;
    string music;
}song;


song parse(string s){
    song value;
    vector<string> parse;
    string token;
    stringstream ss(s);
    
    while(getline(ss, token,',')){
        parse.push_back(token);
    }
    
    // 곡 이름 넣기
    value.name = parse[2];
    
    // 재생시간 넣기
    string start_h = parse[0].substr(0,2);
    string start_m = parse[0].substr(3,2);
    string end_h = parse[1].substr(0,2);
    string end_m = parse[1].substr(3,2);
    
    int h = atoi(end_h.c_str()) - atoi(start_h.c_str());
    int m;
    int time;
    if( h == 0){
        m = atoi(end_m.c_str()) - atoi(start_m.c_str());
        time = m;
    }else{
        m = (60 - atoi(start_m.c_str())) + atoi(end_m.c_str());
        time = h*60+m;
    }
    value.t = time;
    
    // 음악 넣기
    int cnt = 0;
    vector<int> sharp;
    for(int i=0; i<parse[3].size(); i++){
        if(parse[3][i] == '#'){
            sharp.push_back(cnt);
        }else cnt++;
    }

    int real_length = (int)parse[3].size()-(int)sharp.size();

    if(time >= real_length){
        int repeat = time/real_length;
        for(int i=0; i<repeat; i++){
            value.music+=parse[3];
        }
    }
    
    int remain = time%real_length;
    if(remain != 0){
        int plus = 0;
        for(int i=0; i<sharp.size(); i++){
            if(sharp[i] <= remain) plus++;
        }
        remain += plus;
        value.music+=parse[3].substr(0,remain);
    }
    
//    cout << value.music << endl;
    
    return value;
}

string solution(string m, vector<string> musicinfos) {
    vector<song> ssong;
    vector<song> result;
    string answer = "(None)";
    
    for(int i=0; i<musicinfos.size(); i++){
        ssong.push_back(parse(musicinfos[i]));
    }
    
    for(int i=0; i<ssong.size(); i++){
        for(int j=0; j<ssong[i].music.size(); ){
            int find = (int)ssong[i].music.find(m,j);
            if(find != -1){
             if( ssong[i].music[find+m.size()] != '#'){
                result.push_back(ssong[i]);
             }
             j = find+1;
            }else break;
        }
    }
    
    int choice = 0;
    if(result.size() > 1){
        for(int i=1; i<result.size(); i++){
            if(result[choice].t < result[i].t) choice = i;
        }
    }
    if(!result.empty()) answer = result[choice].name;
    
    return answer;
}

int main(){
    vector<string> m = {"12:00,12:09,HELLO,ABC#","13:00,13:05,WORLD,ABC#DEF"};
//    vector<string> m = {"03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B"};
//    vector<string> m = {"12:00,12:14,HELLO,C#DEFGAB", "13:00,13:06,WORLD,ABCDEF"};
//    vector<string> m = {"04:00,04:02,ZERO,#BCC", "15:00,15:02,FIRST,#BCC", "04:00,04:02,SECOND,#BCC", "04:00,04:03,THIRD,#BCC"};
    string result = solution("ABC", m);
    cout << result;
    return 0;
}
