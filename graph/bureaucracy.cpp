#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<vector<int>> G(100001);
vector<int> result;
bool used[100001];
int color[100001]{0};
int flag = 0;

void topological_sort(int v) {
    used[v] = true;
    for (int to : G[v]) {
        if (!used[to])
            topological_sort(to);
    }
    result.push_back(v);
}

void check_acyclic(int v) {
    color[v] = 1;
    for (int to : G[v]) {
        if (color[to] == 0)
            check_acyclic(to);
        if (color[to] == 1) {
            flag = -1;
        }
    }
    color[v] = 2;
}

int main() {
    int n, m;

    fin >> n >> m;

    int u, v;
    for (int i = 0; i < m; i++) {
        fin >> u >> v;
        G[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0)
            check_acyclic(i);
    }

    if (flag == -1)
        fout << flag;
    else {
        for (int i = 1; i <= n; i++) {
            if (!used[i])
                topological_sort(i);
        }
        for (int i = result.size() - 1; i >= 0; i--)
            fout << result[i] << ' ';
    }
}
