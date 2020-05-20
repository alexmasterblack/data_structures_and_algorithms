#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string sub_a, str_b;
int sub_b;
string result = "NO";

void gen(string a_str, int size, string b, string c, int level = 0) {
    if (level == size) {
        if (a_str[0] != '0') {
            str_b = to_string(stoi(c) - stoi(a_str));
            sort(str_b.begin(), str_b.end());
            sort(b.begin(), b.end());
            if (str_b == b) {
                result = "YES";
                sub_a = a_str;
                sub_b = stoi(c) - stoi(a_str);
                return;
            }
        }
    } else {
        for (int i = level; i < size; i++) {
            swap(a_str[level], a_str[i]);
            gen(a_str, size, b, c, level + 1);
            swap(a_str[level], a_str[i]);
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string a, b, c;
    fin >> a >> b >> c;

    gen(a, a.length(), b, c);

    fout << result;
    if (result == "YES") {
        fout << endl << sub_a << ' ' << sub_b;
    }
}
