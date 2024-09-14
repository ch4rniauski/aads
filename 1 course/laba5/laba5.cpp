#include <iostream>
#include <cstdlib>

using namespace std;

struct Tree
{ // дерево
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

struct Tree *node_search(Tree *tree, int element, int &repeat_counter)
{ // поиск узла, после которого нужно вставить следующий элемент
    if (element > tree->elem && tree->right != NULL)
    { // переход на правый узел
        tree = tree->right;
        tree = node_search(tree, element, repeat_counter);
    }
    else if (element < tree->elem && tree->left != NULL)
    { // переход на левый узел
        tree = tree->left;
        tree = node_search(tree, element, repeat_counter);
    }
    else
    {
        if (element == tree->elem)
        {
            repeat_counter++;
            return tree;
        }
    }
    return tree;
}

bool is_clear(Tree *tree)
{ // проверка пустоты бинарного дерева
    if (tree == NULL)
    {
        return 1;
    }
    return 0;
}

struct Tree *append(Tree *tree, int element, int &i)
{ // добавление элемента
    if (is_clear(tree))
    {
        tree = init(tree);
        tree->elem = element;
        return tree;
    }

    else
    {
        Tree *temp = (Tree *)malloc(sizeof(Tree)); // временный указатель для узла
        if (!temp)
            cout << "Memory error!";

        temp->right = NULL;
        temp->left = NULL;

        Tree *temp2 = (Tree *)malloc(sizeof(Tree)); // временный указатель для копирования всего дерева
        if (!temp2)
            cout << "Memory error!";
        temp2 = tree;

        int repeat_counter = 0; // счетчик для проверки: есть ли одинаковые элементы или нет

        tree = node_search(tree, element, repeat_counter);

        if (element > tree->elem && repeat_counter == 0)
        {
            tree->right = temp;
            tree->right->elem = element;
            return temp2;
        }

        else if (element < tree->elem && repeat_counter == 0)
        {
            tree->left = temp;
            tree->left->elem = element;
            return temp2;
        }
        else
        {
            if (repeat_counter != 0)
            {
                cout << "В бинарном дереве не могут повторяться элементы. Введите другой элемент" << endl;
                i--;
                return temp2;
            }
        }
    }
    return tree;
}

void output(Tree *tree)
{ // вывод элементов при помощи рекурсивного прямого обхода
    if (tree != NULL)
    {
        output(tree->left);
        cout << tree->elem << " ";
        output(tree->right);
    }
}

struct Tree *min_search(Tree *temp)
{ // поиск минимального элемента до тех пор, пока правый узел не будет равен NULL
    if (temp->right == NULL)
        return temp;
    else
        temp = min_search(temp->right);
    return temp;
}

struct Tree *del_node(Tree *tree, int key)
{ // удаление введенного элемента
    if (tree == NULL)
    {
        cout << "Дерево пустое" << endl;
        return tree;
    }
    else if (key > tree->elem)
        tree->right = del_node(tree->right, key);
    else
    {
        if (key < tree->elem)
            tree->left = del_node(tree->left, key);
        else
        {
            Tree *temp = (Tree *)malloc(sizeof(Tree));
            temp = tree;
            if (temp->right == NULL)
                tree = temp->left;
            else if (temp->left == NULL)
                tree = temp->right;
            else
            {
                temp = min_search(temp->left);
                tree = del_node(tree, temp->elem);
                tree->elem = temp->elem;
            }
        }
    }
    return tree;
}

void del(Tree *tree)
{ // удаление всего дерева
    if (tree != NULL)
    {
        del(tree->left);
        del(tree->right);
        free(tree);
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

    for (int i = 0; i < n; i++)
    {
        cout << "Введите новый элемент дерева: ";
        int element;
        cin >> element;
        tree = append(tree, element, i);
    }

    output(tree);
    cout << endl;

    while (1)
    {
        cout << "Хотите ли вы удалить какой-нибудь элемент из дерева?" << endl;
        cout << "1 = ДА" << endl;
        cout << "2 = НЕТ" << endl;
        int answer;
        cin >> answer;
        if (answer == 2)
        {
            return 0;
        }
        else if (answer == 1)
        {
            int key;
            cout << "Введите элемент, который хотите удалить: ";
            cin >> key;
            tree = del_node(tree, key);
        }
        else
        {
            cout << "Неизвестный ответ." << endl;
            continue;
        }

        output(tree);

        cout << endl;
        if (is_clear(tree))
        {
            cout << "Ваше дерево пустое." << endl;
            break;
        }
    }

    del(tree);
    return 0;
}
