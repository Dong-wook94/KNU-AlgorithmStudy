# 기둥과 보 설치

## 문제 알고리즘
- 구현 문제

## 풀이방법
1. 삽입의 경우는 문제에서 요구하는 대로 가능 여부를 확인해서 값을 넣는 구조이다.
2. 삭제의 경우는 해당 칸을 저장하고, 삭제한 후 그 주변을 다시 삽입이 가능한 경우 삭제한다 -> 틀린부분 찾는 중

- 현재 점수 : 36점

- 핵심 코드
~~~c++
// 건설 가능한지 확인
bool isValidBuild(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "보"
        // 보의 왼쪽이나 오른쪽 둘 중에 하나라도 기둥인 경우
        if ((y >= 1 && board[y - 1][x] % 2 == PILLAR) || (isInRange(y - 1, x + 1, n) && board[y - 1][x + 1] % 2 == PILLAR))
            return true;
        // 보의 양쪽이 보인 경우
        if ((x >= 1 && board[y][x - 1] >= FLOOR) && (x < n && board[y][x + 1] >= FLOOR))
            return true;
        // 그 외에는 항상 거짓
        return false;
    }
    else {                   // "기둥"
        // 기둥이 바닥에 있는 경우
        if (y == 0)
            return true;
        // 기둥의 아래가 보인 경우
        if (board[y][x] >= FLOOR || (x >= 1 && board[y][x - 1] >= FLOOR))
            return true;
        // 기둥의 아래가 기둥인 경우
        if (y >= 1 && board[y - 1][x] % 2 == PILLAR)
            return true;
        // 그 외에는 항상 거짓
        return false;
    }
}

// 삭제 가능한지 확인 후 삭제
void BuildDelete(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "보"
        int tmp = board[y][x];  // 현재 상태 잠시 보관하고
        if (tmp == BOTH)        // 없었던 상태로 가정하고
            board[y][x] = PILLAR;
        else if (tmp == FLOOR && btype == FLOOR)
            board[y][x] = -1;
        else
            return;
        // 보의 왼쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 보의 오른쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + 1 + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 가능하므로 삭제한 부분을 유지해서 return
        return;
    }
    else {               // "기둥"
        int tmp = board[y][x];  // 현재 상태 잠시 보관하고
        if (tmp == BOTH)        // 없었던 상태로 가정하고
            board[y][x] = FLOOR;
        else if (tmp == PILLAR && btype == PILLAR)
            board[y][x] = -1;
        else
            return;
        // 보의 아래쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 보의 위쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + 1 + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 가능하므로 삭제한 부분을 유지해서 return
        return;
    }
}
~~~

## 문제 후 느낀점
- 아직 틀린점이 많아서 수정 중...
- 추후 추가 예정
