#include <fstream>
#include <vector>
#include <math.h>

#define len 3010
#define modul 1000000007

using namespace std;

long long numerator[len]{0};

void factorization(int number, long long support[]) {
    for (int i = 2; i <= number; i++) {
        int sup_element = i;
        for (int j = 2; j <= sqrt(sup_element); j++) {
            while (sup_element % j == 0) {
                support[j]++;
                sup_element /= j;
            }
        }
        support[sup_element]++;
    }
}

void calculation(long long number) {
    long long support[len]{0};
    factorization(number, support);
    for (int i = 0; i < len; i++) {
        numerator[i] = numerator[i] - support[i];
    }
}

long long end(vector<long long> finally) {
    long long composition = 1;
    for (auto element : finally) {
        composition = composition * element % modul;
    }
    return composition;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int first_x, first_y, first_z, last_x, last_y, last_z;
    fin >> first_x >> first_y >> first_z >> last_x >> last_y >> last_z;

    factorization(abs(last_x - first_x) + abs(last_y - first_y) + abs(last_z - first_z), numerator);

    calculation(abs(last_x - first_x));
    calculation(abs(last_y - first_y));
    calculation(abs(last_z - first_z));

    vector<long long> finally;
    for (int i = 0; i < len; i++) {
        if (numerator[i] != 0) {
            long long power = pow(i, numerator[i]);
            finally.push_back(power % modul);
        }
    }

    fout << end(finally) % modul;
}
