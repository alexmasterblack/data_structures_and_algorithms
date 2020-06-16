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
    
    //матрица смежности
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
    
    //массив дп, где у нас маски по типо 1000...0100.., то есть степени двойки, заполняем нулями
    //это маски с отдельными планетами, по условию задачи мы можем выбрать любую
    //поэтому заполняем нулями, а остальные максимальным числом
    int dp[1 << number_of_planet][number_of_planet];

    for (int i = 0; i < (1 << number_of_planet); i++) {
        for (int j = 0; j < number_of_planet; j++) {
            dp[i][j] = maximum;
        }
    }

    for (int i = 0; i < number_of_planet; i++) {
        dp[1 << i][i] = 0;
    }
    //на каждой планете мы ставим ноль, как я понимаю, когда мы перейдем из маски 011 в 100, то в качестве минимума у нас был бы ноль
    //иначе он бы выбрал в качестве минимума перемещение от i-ой вершины в j-ую, ну и это бы считалось, что он возвращается обратно по вершинам
    
    //dp[mask][i] - минимальный пусть, пройденный комивояжером, если бы он посетил подмножество планет mask
    //и находился на планете i (текущая планета)
    //i-ый город входит в маску, то есть i-ый бит в маске равен 1
    //рассматриваем маски
    for (int mask = 0; mask < (1 << (number_of_planet)); mask++) {
        //рассматриваем текущую планету
        for (int i = 0; i < number_of_planet; i++) {
            //такое состояние недопустимо, поэтому пропускаем
            if (dp[mask][i] == maximum)
                continue;
            //j - номер планеты, в которую комивояжер прилетит из планеты i
            for (int j = 0; j < number_of_planet; j++) {
                //проверяем, что эта планеты не входит в маску, то есть j - ый бит должен быть равен нулю
                //если matrix[i][j] равен -1, то это диагональ матрицы смежности, комивояжер не может попасть из текущей вершины в эту же
                if ((mask & (1 << j)) == 0 && matrix[i][j] != -1)
                    //меняем состояние, выбираем наименьшее значение из новой маски или из значения старой + расстояние от вершины i до j 
                    dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + matrix[i][j]);
                //в общем здесь мы выбираем наименьший путь от вершины i до j
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
