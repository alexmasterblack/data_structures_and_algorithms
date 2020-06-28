#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define max 10001

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int vertices, edges;
    fin >> vertices >> edges;

    vector<vector<int>> G(vertices + 1, vector<int>(vertices + 1, max));

    int v, u, w;
    for (int i = 1; i <= edges; i++) {
        fin >> v >> u >> w;
        G[v][u] = w;
    }

    for (int i = 1; i <= vertices; i++)
        G[i][i] = 0;

    for (int k = 1; k <= vertices; k++) {
        for (int i = 1; i <= vertices; i++) {
            for (int j = 1; j <= vertices; j++) {
                if (G[i][k] < max && G[k][j] < max) {
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
    }

    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            if (G[i][j] != max)
                fout << G[i][j] << ' ';
        }
        fout << endl;
    }
}
