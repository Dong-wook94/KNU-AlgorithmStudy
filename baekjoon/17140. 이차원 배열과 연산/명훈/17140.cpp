#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 100

int r, c, k, ans = -1;
int row_size, col_size;
int board[MAX + 1][MAX + 1];

int main(int argc, const char* argv[]) {
    // input
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            scanf("%d", &board[i][j]);
    row_size = 3;
    col_size = 3;

    // solution
    for (int cnt = 0; cnt <= MAX; cnt++) {
        // end state
        if (board[r][c] == k) {
            ans = cnt;
            break;
        }

        if (row_size >= col_size) {   // R, row >= colr
            for (int i = 1; i <= row_size; i++) {
                vector<int> board_count(MAX + 1);
                vector<pair<int, int>> board_set;
                for (int j = 1; j <= col_size; j++) board_count[board[i][j]]++;
                for (int j = 1; j <= MAX; j++)
                    if (board_count[j])
                        board_set.push_back({ board_count[j], j });
                for (int j = 0; j <= col_size; j++) board[i][j] = 0;
                sort(board_set.begin(), board_set.end());
                int j_pos = 1;
                for (int j = 0; j < board_set.size(); j++) {
                    board[i][j_pos++] = board_set[j].second;
                    board[i][j_pos++] = board_set[j].first;
                }
                j_pos--;
                if (j_pos > MAX)
                    col_size = MAX;
                else
                    col_size = max(col_size, j_pos);
            }
        }
        else {    // C, row < col
            for (int j = 1; j <= col_size; j++) {
                vector<int> board_count(MAX + 1);
                vector<pair<int, int>> board_set;
                for (int i = 1; i <= row_size; i++) board_count[board[i][j]]++;
                for (int i = 1; i <= MAX; i++)
                    if (board_count[i])
                        board_set.push_back({ board_count[i], i });
                for (int i = 1; i <= row_size; i++) board[i][j] = 0;
                sort(board_set.begin(), board_set.end());
                int i_pos = 1;
                for (int i = 0; i < board_set.size(); i++) {
                    board[i_pos++][j] = board_set[i].second;
                    board[i_pos++][j] = board_set[i].first;
                }
                i_pos--;
                if (i_pos > MAX)
                    row_size = MAX;
                else
                    row_size = max(row_size, i_pos);
            }
        }
    }

    // output
    cout << ans << "\n";

    return 0;
}
