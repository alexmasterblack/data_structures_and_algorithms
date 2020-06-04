#include <fstream>
#include <string>
#include <vector>

#define len 30
using namespace std;

int n;
vector<string> support;
vector<string> result;
int best_number = 0, sup_row, sup_col;

string str_coords(int row, int col) {
    return char(col + 94) + to_string(row - 2);
}

void check(char **board, int row, int col, int number = 0) {
    int s_row[4] = {1, 1, -1, -1};
    int s_col[4] = {-1, 1, -1, 1};
    for (int i = 0; i < 4; i++) {
        if (board[row + s_row[i]][col + s_col[i]] == 'O') {
            board[row + s_row[i]][col + s_col[i]] = '.';
            support[number] = str_coords(row, col);
            check(board, row + 2 * s_row[i], col + 2 * s_col[i], number + 1);
            board[row + s_row[i]][col + s_col[i]] = 'O';
        }
    }

    if (number > best_number) {
        result.assign(support.begin(), support.end());
        best_number = number;
        sup_col = col;
        sup_row = row;
        return;
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n;
    support.resize(len);

    char **board = new char *[n + 4];
    for (int i = 1; i <= n + 4; i++)
        board[i] = new char[n + 4];

    char sup;
    for (int i = n + 2; i >= 2; i--) {
        for (int j = 3; j <= n + 2; j++) {
            fin >> sup;
            board[i][j] = sup;
        }
    }

    for (int row = n + 2; row >= 2; row--) {
        for (int col = 3; col <= n + 2; col++) {
            if (board[row][col] == 'X') {
                check(board, row, col);
            }
        }
    }

    if (result.empty())
        fout << "Impossible";
    else {
        for (const auto &element : result)
            if (!element.empty())
                fout << element << '-';
        fout << str_coords(sup_row, sup_col);
    }
}
