#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<vector<int>> G(100001);
vector<int> result;

int n, m;

int flag = 0;

void eulerian_cycle(int v = 1) {
    for (int i = 0; i < G[v].size(); i++) {
        int top = G[v][i];
        G[v].erase(G[v].begin() + i);
        G[top].erase(find(G[top].begin(), G[top].end(), v));
        eulerian_cycle(top);
    }
    fout << v << ' ';
}

void check() {
    for (int i = 1; i <= n; i++) {
        if (G[i].size() % 2 == 1)
            flag = -1;
    }
    if (flag == -1)
        fout << flag;
    else
        eulerian_cycle();
}


int main() {
    fin >> n >> m;

    int u, v;
    for (int i = 0; i < m; i++) {
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    check();
}
