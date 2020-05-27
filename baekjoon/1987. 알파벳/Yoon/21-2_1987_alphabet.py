from collections import deque


r, c = map(int, input().split())
board = []
check = []

#위치 인덱스
dx = [-1, 0, 1, 0]
dy = [0, 1, 0,-1]

def dfs(x,y,maxlen) :
    global len_

    len_ = max(maxlen, len_)

    for i in range(4) :
        nx = x + dx[i]
        ny = y + dy[i]
        if (0<=nx<r) and(0<=ny<c) and (board[nx][ny] not in check) :
            check.append(board[nx][ny])
            dfs(nx,ny,maxlen+1)
            check.remove(board[nx][ny])


for _ in range(r) :
    board.append(list(input()))
len_=1
check.append(board[0][0])
dfs(0,0,len_)

print(len_)