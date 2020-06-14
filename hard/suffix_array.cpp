#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

vector<pair<pair<int, int>, int>> pairs;

void suffix_array(int classes[], string word) {
    //рассматриваем подстроки длины 2^k
    int step = 2;
    for (int i = step / 2; i < word.size(); i *= 2) {
        pairs.clear();
        for (int j = 0; j < word.size(); j++) {
            //первая подстока, вторая подстрока и их индекс
            pairs.emplace_back(make_pair(classes[j], classes[(j + i) % word.size()]), j);
        }

        //сортируем
        sort(pairs.begin(), pairs.end());

        //создаем новый класс
        int index = 0;
        for (int j = 0; j < pairs.size(); j++, index += 1) {
            //так как пары отсортированы, то по индексу пары первая подстрока в классе равна 0
            if (j == 0)
                classes[pairs[j].second] = 0;
            else {
                //пары могут повторяться (а так как они отсортированы, то можно проверять соседние),
                //то отменяем прошлое увеличение индекса и присваиваем предыдущий индекс
                if (pairs[j].first.first == pairs[j - 1].first.first &&
                    pairs[j].first.second == pairs[j - 1].first.second)
                    index -= 1;
                classes[pairs[j].second] = index;
            }
        }
    }
}

void counting_sort(string word) {
    int classes[word.size()];
    int support[123]{0};

    //сортировка подсчетом, нулевая итерация
    //под индексом, равным аски коду буквы, получаем количество этой буквы в слове
    for (char i : word) {
        support[i] += 1;
    }

    //отсортированные индексы для массива класссов
    int support_index[123]{0};
    int index = 0;
    for (int i = 0; i < 123; i++) {
        if (support[i] != 0) {
            support_index[i] = index;
            index += 1;
        }
    }

    //по букве записываю индекс в массив классов
    for (int i = 0; i < word.size(); i++) {
        classes[i] = support_index[word[i]];
    }

    //остальные итерации
    return suffix_array(classes, word);
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string word;
    fin >> word;

    counting_sort(word);
    //строка в инпуте будет лежать по индексу ноль, так как она будет первой
    //но так как пары в лексикографическом порядке, то не обязательно она там будет первая
    vector<int> finally;
    int index = 0;
    for (int i = 0; i < pairs.size(); i++) {
        //нужно учесть, что подстроки могут быть идентичными, поэтому для правильного вывода надо учесть повторы
        if (i > 0 && pairs[i].first.first == pairs[i - 1].first.first &&
            pairs[i].first.second == pairs[i - 1].first.second)
            index += 1;
        else {
            finally.push_back(pairs[i].second);
            index = 0;
        }

    }

    //нахожу нулевой суффик и выводу индекс
    if (!finally.empty()) {
        for (int i = 0; i < finally.size(); i++) {
            if (finally[i] == 0)
                fout << i;
        }
    } else {
        fout << 0;
    }
}
