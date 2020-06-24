#include <iostream>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> coordinates;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, x_first, y_first, x_last, y_last;

    fin >> n >> x_first >> y_first >> x_last >> y_last;

    bool **used = new bool *[n + 2];
    int **path = new int *[n + 2];


    for (int i = 0; i < n + 2; i++) {
        used[i] = new bool[n + 2];
        path[i] = new int[n + 2];
    }

    char sup;
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < n + 2; j++) {
            if ((i >= 1 && i <= n) && (j >= 1 && j <= n)) {
                fin >> sup;
                used[i][j] = sup == '#';
            } else {
                used[i][j] = true;
                path[i][j] = 101;
            }
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    queue<coordinates> line;

    line.push(make_pair(y_first, x_first));
    used[y_first][x_first] = true;
    path[y_first][x_first] = 0;

    while (!line.empty()) {
        coordinates v = line.front();
        line.pop();
        for (int i = 0; i < 4; i++) {
            if (!used[v.first + dy[i]][v.second + dx[i]]) {
                used[v.first + dy[i]][v.second + dx[i]] = true;
                path[v.first + dy[i]][v.second + dx[i]] = path[v.first][v.second] + 1;
                line.push(make_pair(v.first + dy[i], v.second + dx[i]));
            }
        }
    }

    fout << path[y_last][x_last];
}
