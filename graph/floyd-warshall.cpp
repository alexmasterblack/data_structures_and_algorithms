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
    
    //матрица смежности, если есть путь, то это расстояние от одного ребра до другого, если пути нет, то будет стоять максимальное число
    vector<vector<int>> G(vertices + 1, vector<int>(vertices + 1, max));

    int v, u, w;
    for (int i = 1; i <= edges; i++) {
        fin >> v >> u >> w;
        G[v][u] = w;
    }
    
    //по диагонали стоят нули
    for (int i = 1; i <= vertices; i++)
        G[i][i] = 0;
    
    //G_ijk - это длина кратчайшего пути из i вершины в j с промежуточными вершинами k (1...k)
    //есть два случая, либо мы не проходим через вершину k (он не входит в кратчайший путь), ну и наш кратчайший путь не менятся
    //либо мы проходим через вершину, тогда кратчайший путь разбит вершиной k на G_ik и G_kj
    for (int k = 1; k <= vertices; k++) {
        for (int i = 1; i <= vertices; i++) {
            for (int j = 1; j <= vertices; j++) {
                //для поиска кратчайшего пути выбираем минимум просто
                //не рассматриваем вершины, из которыйх нет пути
                if (G[i][j] > G[i][k] + G[k][j] && G[i][k] != max && G[k][j] != max) {
                    G[i][j] = G[i][k] + G[k][j];
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
