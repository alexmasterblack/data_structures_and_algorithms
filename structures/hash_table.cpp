#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>

#define lenght 4001

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class HashTable {
    list<int> *table;
public:
    HashTable() {
        table = new list<int>[lenght];
    }

    int hash_function(int data) {
        int result = data;
        for (int i = 1; i < data; i++) {
            result = result + pow(data % 10, i);
            data /= 10;
        }
        return abs(result % lenght);
    }

    void push(int data) {
        int key = hash_function(data);

        auto i = find(table[key].begin(), table[key].end(), data);
        if (i == table[key].end()) {
            table[key].push_back(data);
        }
    }

    void pop(int data) {
        int key = hash_function(data);

        list<int>::iterator i;
        for (i = table[key].begin(); i != table[key].end(); i++) {
            if (*i == data)
                break;
        }

        if (i != table[key].end())
            table[key].erase(i);
    }

    void print() {
        vector<int> result;
        for (int i = 0; i < lenght; i++) {
            for (auto element : table[i])
                result.push_back(element);
        }
        sort(result.begin(), result.end());
        for (int i : result) {
            fout << i << ' ';
        }
    }
};

int main() {
    HashTable table;

    int sup;
    while (fin >> sup) {
        if (sup > 0)
            table.push(sup);
        if (sup < 0)
            table.pop(-sup);
        if (sup == 0)
            break;
    }

    table.print();
}
