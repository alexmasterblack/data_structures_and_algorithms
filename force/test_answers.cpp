#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<char> str;
vector<vector<char>> result;
vector<int> count_tr;
vector<string> answers;

void place_repeat(char *a, int n, int k, int h = 0) {
    if (h == k) {
        for (int i = 0; i < answers.size(); i++) {
            int count = 0;
            for (int j = 0; j < k; j++) {
                if (answers[i][j] == str[j])
                    count++;
            }
            if (count != count_tr[i])
                return;
            if (i == answers.size() - 1 && count == count_tr[i])
                result.push_back(str);
        }
    } else {
        for (int i = 0; i < n; i++) {
            str.push_back(a[i]);
            place_repeat(a, n, k, h + 1);
            str.pop_back();
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    char a[3] = "+-";

    int shush, num_quest;
    fin >> shush >> num_quest;

    int sup_count;
    string sup_answer;
    for (int i = 0; i < shush; i++) {
        fin >> sup_answer;
        fin >> sup_count;
        answers.push_back(sup_answer);
        count_tr.push_back(sup_count);
    }

    place_repeat(a, 2, num_quest);

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < num_quest; j++) {
            fout << result[i][j];
        }
        fout << endl;
    }
}
