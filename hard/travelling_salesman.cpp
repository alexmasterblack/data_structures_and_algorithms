#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>

#define maximum 2147483647

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int number_of_planet;
    fin >> number_of_planet;

    int **matrix = new int *[number_of_planet];
    for (int i = 0; i < number_of_planet; i++)
        matrix[i] = new int[number_of_planet];

    int sup;
    for (int i = 0; i < number_of_planet; i++) {
        for (int j = 0; j < number_of_planet; j++) {
            fin >> sup;
            matrix[i][j] = sup;
        }
    }

    int dp[1 << number_of_planet][number_of_planet];

    for (int i = 0; i < (1 << number_of_planet); i++) {
        for (int j = 0; j < number_of_planet; j++) {
            dp[i][j] = maximum;
        }
    }

    for (int i = 0; i < number_of_planet; i++) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 0; mask < (1 << (number_of_planet)); mask++) {
        for (int i = 0; i < number_of_planet; i++) {
            if (dp[mask][i] == maximum)
                continue;
            for (int j = 0; j < number_of_planet; j++) {
                if ((mask & (1 << j)) == 0 && matrix[i][j] != -1)
                    dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + matrix[i][j]);
            }
        }
    }

    int minimum = maximum;
    for (int i = 0; i < number_of_planet; i++) {
        if (dp[(1 << number_of_planet) - 1][i] < minimum)
            minimum = dp[(1 << number_of_planet) - 1][i];
    }

    fout << minimum;
}
