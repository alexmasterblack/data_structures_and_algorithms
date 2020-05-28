#include <fstream>
#include <string>
#include <vector>
#include <numeric>
 
#define len 10
 
using namespace std;
 
int n;
vector<string> keys;
vector<bool> used;
vector<int> support;
vector<int> result;
 
int search_sum(vector<int> &sup_elements) {
    return accumulate(sup_elements.begin(), sup_elements.end(), 0);
}
 
void permutation(int level = 0) {
    if (level == n) {
        if (search_sum(support) < search_sum(result))
            result.assign(support.begin(), support.end());
        return;
    } else {
        for (int i = 0; i < keys[level].size(); i++) {
            int now = keys[level][i] - 97;
            if (!used[now]) {
                used[now] = true;
                support[level] = i;
                if (search_sum(support) < search_sum(result))
                    permutation(level + 1);
                used[now] = false;
            }
 
        }
        support[level] = len;
        permutation(level + 1);
        support[level] = 0;
    }
}
 
 
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
 
    fin >> n;
 
    used.resize(len);
    support.resize(len);
 
    string sup;
    for (int i = 0; i < n; i++) {
        fin >> sup;
        keys.push_back(sup);
        result.push_back(len);
    }
 
    permutation();
 
    for (int i = 0; i < n; i++) {
        if (result[i] != len) {
            fout << keys[i].insert(result[i], "&");
        } else fout << keys[i];
        fout << endl;
    }
 
}
