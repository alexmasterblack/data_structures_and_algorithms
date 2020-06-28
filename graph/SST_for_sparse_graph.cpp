#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define max 10001

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<vector<pair<int, int>>> G(100001);
bool used_one[100001];

void dfs(int v) {
    used_one[v] = true;
    for (auto &i : G[v]) {
        int to = i.first;
        if (!used_one[to])
            dfs(to);
    }
}

void prim(int vertices) {
    //завели массив юзд, чтобы хранить вершины, в которые не можем походить
    vector<bool> used_two(vertices + 1, false);
    vector<int> min_edge(vertices + 1, max);
    min_edge[1] = 0;
    
    //хранятся все рассматриваемые вершины
    set<pair<int, int>> score;
    score.insert(make_pair(0, 1));
    
    //пока скор не пуст
    while (!score.empty()) {
        //достаем минимальную вершину и удаляем ее, чтобы не 
        auto top = *score.begin();
        score.erase(score.begin());
        
        //идем по смежным вершинам, кладем их в скор, обновляем минимальные значения
        for (auto to : G[top.second]) {
            if (!used_two[to.first] && to.second < min_edge[to.first]) {
                score.erase(make_pair(min_edge[to.first], to.first));
                min_edge[to.first] = to.second;
                score.insert(make_pair(min_edge[to.first], to.first));
            }
        }
        //после того как рассмотрели все смежные с вершиной вершины, помечаем ее, чтобы потом в нее не походить
        used_two[top.second] = true;
    }

    int sum = 0;
     for (int i = 1; i < min_edge.size(); i++)
         sum = sum + min_edge[i];
    fout << sum;
}

int main() {
    int vertices, edges, flag = 0;
    fin >> vertices >> edges;

    int u, v, w;
    for (int i = 0; i < edges; i++) {
        fin >> u >> v >> w;
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }

    dfs(1);
    for (int i = 1; i <= vertices; i++) {
        if (!used_one[i]) {
            flag = -1;
        }
    }

    if (flag == -1)
        fout << flag;
    else {
        prim(vertices);
    }
}
