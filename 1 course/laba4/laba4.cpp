#include <iostream>
#include <cstdlib>

using namespace std;

struct Tree
{
    struct Tree *right;
    struct Tree *left;
    int elem;
};

struct Tree *init(Tree *tree)
{ // инициализация дерева
    tree = (Tree *)malloc(sizeof(Tree));
    if (!tree)
        cout << "Memory error!";

    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

struct Tree *node_search(Tree *tree, int element)
{ // поиск узла, после которого нужно вставить следующий элемент
    if (element > tree->elem && tree->right != NULL)
    { // переход на правый узел
        tree = tree->right;
        tree = node_search(tree, element);
    }
    else if (element < tree->elem && tree->left != NULL)
    { // переход на левый узел
        tree = tree->left;
        tree = node_search(tree, element);
    }
    return tree;
}

void append(Tree *tree, int element, int i)
{ // добавление элемента
    if (i == 0)
        tree->elem = element;

    else
    {
        Tree *temp = (Tree *)malloc(sizeof(Tree));
        if (!temp)
            cout << "Memory error!";

        temp->right = NULL;
        temp->left = NULL;

        tree = node_search(tree, element);

        if (element > tree->elem)
        {
            tree->right = temp;
            tree->right->elem = element;
        }

        else
        {
            tree->left = temp;
            tree->left->elem = element;
        }
    }
}

void output(Tree *tree)
{
    if (tree != NULL)
    {
        output(tree->left);
        cout << tree->elem << " ";
        output(tree->right);
    }
}

int main()
{
    int n;
    cout << "Введите количество элементов, которое хотите поместить в дерево: ";
    cin >> n;

    if (n <= 0)
        return 0;

    Tree *tree = NULL;
    tree = init(tree);

    for (int i = 0; i < n; i++)
    {
        cout << "Введите новый элемент дерева: ";
        int element;
        cin >> element;
        append(tree, element, i);
    }

    output(tree);
    free(tree);
    return 0;
}
