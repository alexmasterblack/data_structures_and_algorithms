#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> G(100001);
vector<int> up(100001);
vector<int> time_in(100001);
vector<int> points(100001);
bool used[100001];

int time = 0;
//для того, чтобы понять, что вершина есть точка сочления
//необходимо понять, что у других вершин ее поддерева есть пути к вершинам другого поддерева

void point_search(int v = 1, char flag = '1') {
    int number_of_children = 0;
    //время, с которым мы заходим в вершину time_in
    //up минимальное время вхождения в вершину
    up[v] = time_in[v] = time++;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        int to = G[v][i];
        if (used[to])
            //спрашиваем для вершины ее время входа
            //если такая вершина уже посещалась, то обновляем значение
            //либо предыдущее, которое уже лежит, либо новое
            up[v] = min(up[v], time_in[to]);
        if (!used[to]) {
            point_search(to, '0');
            //прошлись по всему поддереву и нашли минимальное время входа
            up[v] = min(up[v], up[to]);
            //если минимальное время в поддереве больше времени самой вершины, то эта вершина точка сочленения
            if (flag == '0' && up[to] >= time_in[v]) {
                points[v] = v;
            }
            number_of_children += 1;
        }
    }
    //если больше, чем один вызов, то стартовая вершина и есть точка сочленения
    if (flag == '1' && number_of_children > 1) {
        points[v] = v;
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

    point_search();

    int lenght = 0;
    for (int point : points) {
        if (point != 0)
            lenght += 1;
    }

    fout << lenght;

    for (int point : points) {
        if (point != 0)
            fout << ' ' << point;
    }
}
