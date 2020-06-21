#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class AvlTree {
    struct node {
        int value;
        node *left;
        node *right;
        int height;
    };

    node *root;

    int height(node *top) {
        if (top == NULL)
            return 0;
        else
            return top->height;
    }

    int balance(node *top) {
        if (top == NULL)
            return 0;
        else
            return height(top->right) - height(top->left);
    }

    node *right_rotation(node *top) {
        node *new_top = top->left;
        top->left = new_top->right;
        new_top->right = top;
        top->height = max(height(top->left), height(top->right)) + 1;
        new_top->height = max(height(new_top->left), height(new_top->right)) + 1;
        return new_top;
    }

    node *left_rotation(node *top) {
        node *new_top = top->right;
        top->right = new_top->left;
        new_top->left = top;
        top->height = max(height(top->left), height(top->right)) + 1;
        new_top->height = max(height(new_top->left), height(new_top->right)) + 1;
        return new_top;
    }

    node *balance_check(node *top) {
        top->height = max(height(top->left), height(top->right)) + 1;
        if (balance(top) == -2) {
            if (balance(top->left) == -1)
                return right_rotation(top);
            else if (balance(top->left) == 1) {
                top->left = left_rotation(top->left);
                return right_rotation(top);
            }
        }
        if (balance(top) == 2) {
            if (balance(top->right) == 1)
                return left_rotation(top);
            else if (balance(top->right) == -1) {
                top->right = right_rotation(top->right);
                return left_rotation(top);
            }
        }
        return top;
    }

    node *minumum(node *top) {
        if (top == NULL)
            return 0;
        if (top->left != NULL)
            return minumum(top->left);
        else return top;
    }

    node *push(int key, node *top) {
        if (top == NULL) {
            top = new node;
            top->value = key;
            top->left = NULL;
            top->right = NULL;
        } else if (key < top->value) {
            top->left = push(key, top->left);
        } else if (key > top->value) {
            top->right = push(key, top->right);
        }
        return balance_check(top);
    }

    node *pop(int key, node *top) {
        if (top == NULL) {
            return top;
        }

        node * temp = top;

        if (key < top->value) {
            top->left = pop(key, top->left);
        } else if (key > top->value) {
            top->right = pop(key, top->right);
        } else if (top->left != NULL && top->right != NULL) {
            top->value = minumum(top->right)->value;
            top->right = pop(minumum(top->right)->value, top->right);
        } else {
            if (top->left != NULL) {
                top = top->left;
                free(temp);
            } else if (top->right != NULL) {
                top = top->right;
                free(temp);
            } else {
                free(temp);
                return NULL;
            }
        }
        return balance_check(top);
    }

    int lenght(node *top, int left_size = 0, int right_size = 0) {
        if (top == NULL) {
            return 0;
        } else {
            if (top->left != NULL)
                left_size = lenght(top->left);
            if (top->right != NULL)
                right_size = lenght(top->right);
            return left_size + right_size + 1;
        }
    }


public:
    AvlTree() {
        root = NULL;
    }

    void push(int key) {
        root = push(key, root);
    }

    void pop(int key) {
        root = pop(key, root);
    }

    int lenght() {
        return lenght(root);
    }

    int min() {
        return minumum(root)->value;
    }
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    AvlTree tree;

    int sup;
    while (fin >> sup) {
        if (sup > 0)
            tree.push(sup);
        if (sup < 0)
            tree.pop(-sup);
        if (sup == 0)
            break;
    }

    int size = tree.lenght();
    for (int i = 0; i < size; i++) {
        sup = tree.min();
        fout << sup << ' ';
        tree.pop(sup);
    }
}
