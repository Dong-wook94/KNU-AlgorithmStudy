//
//  blockGame.cpp
//  test
//
//  Created by 지혜 on 2020/04/05.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
typedef struct tetris{
    vector<pair<int,int>> b;
    pair<int,int> empty[2];
    int check = 1;
}tetris;
tetris block[9999];
int blockNum=0;


vector<int> findDelete(int n, vector<vector<int>> board){
    vector<int> deleteB;
    
    for(int i=1; i<=blockNum; i++){
        if(block[i].check == 1){
            int check = 1;
            int searchC1 = block[i].empty[0].second;
            int searchC2 =block[i].empty[1].second;
            int searchR1 = block[i].empty[0].first;
            int searchR2 = block[i].empty[1].first;
            if(searchC1 == searchC2){
                for(int j=0; j<=searchR2; j++){
                    if(board[j][searchC1] != 0){
                        check = 0;
                        break;
                    }
                }
            }else{
                for(int j=0; j<=searchR1; j++){
                    if(board[j][searchC1] != 0 || board[j][searchC2] != 0){
                        check = 0;
                        break;
                    }
                }
            }
            
            if(check == 1 ) deleteB.push_back(i);
        }
    }
    
    return deleteB;
}
int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = (int)board[1].size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j] != 0){
                if(blockNum < board[i][j]) blockNum = board[i][j];
                block[board[i][j]].b.push_back(make_pair(i,j));
            }
        }
    }
    
    // 글러먹은..애들..체크해놓기
    for(int i=1; i<=blockNum; i++){
        int row = block[i].b[0].first;
        int row2 = block[i].b[1].first;
        int row3 = block[i].b[2].first;
        int row4 = block[i].b[3].first;
        if(row == row2) block[i].check = 0;
        if(row2 == row3){
            if(row != row4 && row != row2 && row4 != row2) block[i].check=0;
        }
    }
    
    // 어디를 채워줘야하나..아 이런 하드코딩이 어디있음..
    for(int i=1; i<=blockNum; i++){
        if(block[i].check == 1){
            int row1 = block[i].b[0].first;
            int row2 = block[i].b[1].first;
            int row3 = block[i].b[2].first;
            int row4 = block[i].b[3].first;
            int col1 = block[i].b[0].second;
            int col2 = block[i].b[1].second;
            int col3 = block[i].b[2].second;
            int col4 = block[i].b[3].second;
            if( row2 == row3 && row3 == row4){
                block[i].empty[0].first = row1;
                block[i].empty[1].first = row1;
                if(col1 == col2){
                    block[i].empty[0].second = col3;
                    block[i].empty[1].second = col4;
                }else if(col1 == col4){
                    block[i].empty[0].second = col2;
                    block[i].empty[1].second = col3;
                }else{
                    block[i].empty[0].second = col2;
                    block[i].empty[1].second = col4;
                }
            }else{
                block[i].empty[0].first = row1;
                block[i].empty[1].first = row2;
                if(col3 == col1){
                    block[i].empty[0].second = col4;
                    block[i].empty[1].second = col4;
                }else{
                    block[i].empty[0].second = col3;
                    block[i].empty[1].second = col3;
                }
            }
        }
    }
    
    while(1){
        vector<int> deleteB = findDelete(n,board);
        if(deleteB.empty()) break;
        else{
            answer+= (int)deleteB.size();
            for(int i=0; i<deleteB.size(); i++){
                for(int j=0; j<block[deleteB[i]].b.size(); j++){
                    board[block[deleteB[i]].b[j].first][block[deleteB[i]].b[j].second] = 0;
                }
                block[deleteB[i]].check = 0;
            }
        }
    }
    
    return answer;
}

int main(){
    vector<vector<int>> board = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,4,0,0,0},
        {0,0,0,0,0,4,4,0,0,0},
        {0,0,0,0,3,0,4,0,0,0},
        {0,0,0,2,3,0,0,0,5,5},
        {1,2,2,2,3,3,0,0,0,5},
        {1,1,1,0,0,0,0,0,0,5}};
    cout << solution(board) << endl;
    return 0;
}
