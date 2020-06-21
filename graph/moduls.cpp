#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> G(100000);
bool used[100000];

void dfs(int v) {
    used[v] = true;
    for (int to : G[v]) {
        if (!used[to])
            dfs(to);
    }

}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;

    fin >> n >> m;

    int u, v;
    for (int i = 0; i < m; i++) {
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> result;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i);
            result.push_back(i);
        }

    }

    fout << result.size();
}
