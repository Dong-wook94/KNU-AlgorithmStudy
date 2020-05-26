# 1987 알파벳

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/82886699-dae10900-9f81-11ea-8ced-506647b8cf3b.png)

## 문제 알고리즘

- dfs

## 풀이방법

1. dfs를 돌린다.

- 생각할 것

  - 동일한 알파벳 체크를 할 것이므로 `visited[][]`를 구현하지 않아도 된다.

  - 꼭 `board[R-1][C-1]`가 끝이 아닐 수 있다. 요거를 생각을 못해서 정답률이 박살이 났다.

- 핵심 코드

```java
import java.util.*;
import java.io.*;

public class Main {
    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    // private static final BufferedWriter bw = new BufferedWriter(new
    // OutputStreamWriter(System.out));
    private static int dx[] = { -1, 0, 1, 0 };
    private static int dy[] = { 0, -1, 0, 1 };

    static int R, C;
    static int[][] board;
    static boolean[] alphabet;
    static int MaxValue = 0;

    public static void main(String[] args) throws IOException {
        init();
        solution();

        System.out.println(MaxValue);
    }

    public static void init() throws IOException {
        // init & input
        StringTokenizer st = new StringTokenizer(br.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        board = new int[R][];
        alphabet = new boolean[26];
        for (int i = 0; i < 26; i++)
            alphabet[i] = false;
        for (int i = 0; i < R; i++) {
            board[i] = new int[C];
        }

        for (int i = 0; i < R; i++) {
            String line = br.readLine();
            for (int j = 0; j < C; j++) {
                board[i][j] = line.charAt(j);
            }
        }
    }

    public static void solution() {
        dfs(0, 0, 0);
    }

    public static void dfs(int r, int c, int depth) {
        // end state, if duplicate alphabet
        if (alphabet[(board[r][c] - 'A')]) {
            if (MaxValue < depth)
                MaxValue = depth;
            return;
        }

        // loop
        for (int dir = 0; dir < 4; dir++) {
            int nextR = r + dy[dir];
            int nextC = c + dx[dir];

            // if out of board, update MaxValue
            if (isInBoard(nextR, nextC) == false) {
                if (MaxValue < depth + 1)
                    MaxValue = depth + 1;
                continue;
            }

            alphabet[(board[r][c] - 'A')] = true;
            dfs(nextR, nextC, depth + 1);
            alphabet[(board[r][c] - 'A')] = false;

        }
    }

    static boolean isInBoard(int r, int c) {
        if (r < 0 || r >= R)
            return false;
        if (c < 0 || c >= C)
            return false;
        return true;
    }

}

```

## 문제 후 느낀점

- 문제를 잘못 파악해서 정답률이 박살이 나버렸다.
