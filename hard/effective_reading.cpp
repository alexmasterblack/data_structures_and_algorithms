#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef pair<pair<long long, long long>, long long> left_right_pages;

vector<left_right_pages> books;
long long last_day = 0;
int number_of_books;

class heap {
    vector<left_right_pages> heap_list;
    long long size_heap = 0;

    void heap_up(long long index) {
        if (index == 0)
            return;
        long long parent = (index - 1) / 2;
        if (heap_list[parent].first.second > heap_list[index].first.second) {
            swap(heap_list[parent], heap_list[index]);
            heap_up(parent);
        }
    }

    void heap_down(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int sup_element = index;

        if (left < size_heap && heap_list[left].first.second < heap_list[sup_element].first.second)
            sup_element = left;
        if (right < size_heap && heap_list[right].first.second < heap_list[sup_element].first.second)
            sup_element = right;
        if (heap_list[sup_element].first.second < heap_list[index].first.second) {
            swap(heap_list[index], heap_list[sup_element]);
            heap_down(sup_element);
        }
    }

public:

    void add_to_heap(left_right_pages element) {
        heap_list.push_back(element);
        size_heap++;
        heap_up(size_heap - 1);
    }

    void pop_min() {
        swap(heap_list[0], heap_list[size_heap - 1]);
        size_heap--;
        heap_list.pop_back();
        heap_down(0);
    }

    void clear() {
        heap_list.clear();
        size_heap = 0;
    }

    long long get_size() {
        return size_heap;
    }

    left_right_pages top() {
        return heap_list[0];
    }

    void reading(long long page) {
        //если размер кучи равен нулю, то либо мы еще не добавили ничего, либо уже нечего читать
        if (size_heap == 0)
            return;
        else {
            //если страниц больше, то просто отнимаем, если меньше то вынимаем книгу
            //отнимает от числа листов столько, сколько было в книге и считаем рекурсивно дальше
            if (heap_list[0].second > page) {
                heap_list[0].second = heap_list[0].second - page;
            } else if (heap_list[0].second <= page) {
                page = page - heap_list[0].second;
                pop_min();
                reading(page);
            }
        }
    }

};

heap heap;

bool comp(left_right_pages one, left_right_pages two) {
    return one.first.first < two.first.first;
}

bool checking(long long best_number) {
    heap.clear();
    //начинаю добавлять книги, ести встречаю промежуток времени
    //равный левой границе книге, то добавляю ее в кучу
    long long current_book = 0;
    for (long long time = 1; time < last_day + 1; time++) {
        //если правая граница будет больше момента времени, то мы не можем прочитать книги
        if (heap.get_size() > 0 && heap.top().first.second <= time)
            return false;

        //в один день может быть несколько книг, так что добавляю их
        while (time == books[current_book].first.first) {
            heap.add_to_heap(books[current_book]);
            current_book += 1;
        }

        //читаем
        heap.reading(best_number);
    }
    //если куча пустая, то мы смогли прочитать все книги и все ок
    if (heap.get_size() == 0)
        return true;
}

long long binary_search(long long left, long long right, long long middle_pages) {
    //нам нужно найти такое минимальное количество страниц, что Петя сможет прочитать все книги
    while (left <= right) {
        if (checking(middle_pages)) {
            right = middle_pages - 1;
        } else {
            left = middle_pages + 1;
        }
        middle_pages = (left + right + 1) / 2;
    }
    return middle_pages;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> number_of_books;
    //добавляю информацию о книгах, считаю последний день и сумму всех страниц
    //это будет правая граница для бинарного поиска
    int sup_one, sup_two, sup_three;
    long long right_border = 0, left_border = 1;
    for (int i = 0; i < number_of_books; i++) {
        fin >> sup_one >> sup_two >> sup_three;
        books.emplace_back(make_pair(sup_one, sup_two), sup_three);
        if (sup_two > last_day)
            last_day = sup_two;
        //так как нам может понадобиться прочитать все книги в один день
        right_border = right_border + sup_three;
    }

    //сортируем по левой границе
    sort(books.begin(), books.end(), comp);

    fout << binary_search(left_border, right_border, (left_border + right_border + 1) / 2);
}
