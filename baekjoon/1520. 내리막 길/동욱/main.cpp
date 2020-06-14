#include <stdio.h>

int visit[501][501];
int map[501][501];
int directon_col[4] = { 1,0,-1,0 };
int direction_row[4] = { 0,1,0,-1 };
int search(int row, int col, int max_row, int max_col);
int main() {
    int max_row, max_col, i, j;

    scanf("%d %d", &max_row, &max_col);
    for (j = 1; j <= max_row; j++) {
        for (i = 1; i <= max_col; i++) {
            scanf("%d", &map[j][i]);
            visit[j][i] = -1;
        }
    }

    printf("%d\n", search(1, 1, max_row, max_col));


}
int search(int row, int col, int max_row, int max_col) {

    int i, next_col, next_row;
    if (col == max_col&row == max_row) {
        return 1;
    }
    if (visit[row][col]!=-1) return visit[row][col];
    visit[row][col] = 0;
    for (i = 0; i < 4; i++) {
        next_col = col + directon_col[i];
        next_row = row + direction_row[i];
        if (map[row][col] > map[next_row][next_col] && next_col>0 && next_row>0 && next_col <= max_col&&next_row <= max_row) {
            visit[row][col] += search(next_row, next_col, max_row, max_col);
        }
    }
    return visit[row][col];
}
