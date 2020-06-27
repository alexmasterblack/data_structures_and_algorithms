#include <fstream>
#include <utility>
#include <vector>
#include <set>

#define max 100001

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<vector<pair<int, int>>> G(100001);

void dijkstra(int v, int vertices) {
    //здесь будут храниться результаты
    vector<int> distance(vertices + 1, max);
    //кратчайший путь для исходной вершины равен 0, остальные максимальному числу
    distance[v] = 0;
    //здесь множество вершин, для которых уже найден лучший путь
    set<pair<int, int>> score;
    //добавляем в множество первую вершину
    score.insert(make_pair(0, v));
    while (!score.empty()) {
        //достаем минимальную вершину
        auto top = *score.begin();
        //удаляем ее, чтобы в следующий раз не взять ее за минимальную
        score.erase(score.begin());
        for (auto to : G[top.second]) {
            //рассматриваем смежные вершины
            //если мы нашли путь, который кротче предыдущего, то удаляем предыдущее значение
            //обновляем результат и вставляем новое
            if (distance[to.first] > distance[top.second] + to.second) {
                score.erase(make_pair(distance[to.first], to.first));
                distance[to.first] = distance[top.second] + to.second;
                score.insert(make_pair(distance[to.first], to.first));
            }
        }
    }

    for (int i = 1; i < distance.size(); i++) {
        if (distance[i] == max)
            distance[i] = -1;
    }
    for (int i = 1; i < distance.size(); i++)
        fout << distance[i] << ' ';


}

int main() {
    //число вершин, ребер, исходная вершина
    int vertices, edges, sourse_vertex;
    fin >> vertices >> edges >> sourse_vertex;

    //смежная вершина и вес

    int u, v, w;
    for (int i = 1; i <= edges; i++) {
        fin >> u >> v >> w;
        //вес, длина
        G[u].push_back(make_pair(v, w));
    }

    dijkstra(sourse_vertex, vertices);

}
