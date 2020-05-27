#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
int n;
string word;
vector<string> cubes;
vector<int> support;
vector<int> result;
 
bool used[12];
 
void permutation(int level = 0) {
    if (level == word.size()) {
        result.assign(support.begin(), support.end());
        return;
    } else {
        for (int i = 0; i < n; i++) {
            if (!used[i] && result.empty() && cubes[i].find(word[level]) != string::npos) {
                used[i] = true;
                support[level] = i + 1;
                permutation(level + 1);
                used[i] = false;
            }
        }
    }
}
 
 
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
 
    fin >> n;
    fin >> word;
    support.resize(word.size());
 
    string sup;
    for (int i = 1; i < n + 1; i++) {
        fin >> sup;
        cubes.push_back(sup);
    }
 
    permutation();
 
    if (result.empty())
        fout << 0;
    else
        for (int element : result)
            fout << element << ' ';
}
