# 감시

cctv는..벽이 아님을...문제를 졔발...잘 읽으세요..

그리고 왜이렇게 더럽게 풀었는지는 1도모름



그냥..방향대로 바꿀 위치 리턴해줬음..

~~~c++
vector<pair<int,int>> changeMap(int row,int col,int dir){
    vector<pair<int,int>> change;
    switch (dir) {
        case 0:
            // 위
            for(int i=row-1; i>=0; i--){
                if(map[i][col] == 6) break;
                else if(map[i][col] == 0) change.push_back(make_pair(i,col));
            }
            break;
        case 1:
            // 아래
            for(int i=row+1; i<n; i++){
                if(map[i][col] == 6) break;
                else if(map[i][col] == 0) change.push_back(make_pair(i,col));
            }
            break;
        case 2:
            // 왼
            for(int i=col-1; i>=0; i--){
                if(map[row][i] == 6) break;
                else if(map[row][i] == 0) change.push_back(make_pair(row,i));
            }
            break;
        case 3:
            // 오른
            for(int i=col+1; i<m; i++){
                if(map[row][i] == 6) break;
                else if(map[row][i] == 0) change.push_back(make_pair(row,i));
            }
            break;
        default:
            break;
    }
    return change;
}
~~~

그리고..그냥ㅠ일단 모든 방향 바꿀수있는 위치 다 받아놓고 

cctv 타입마다 방향 돌려가면서..이용해 봤읍니다...

복붙복붙..너무 혼미해서 눈물남;-; 