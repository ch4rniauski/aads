#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
    int key;
    struct Node *right = NULL;
    struct Node *left = NULL;
    int height = 0;
};

struct Node *height_from_beginning(Node *tree, int &i)
{ // обновление высоты узлов c самого начала
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
        cout << "Memory error!";
    i++;
    tree->height = i;
    for (;;)
    {
        if (tree->right != NULL)
        {
            i = tree->height - 1;
            temp = height_from_beginning(tree->right, i);
            tree->height = tree->right->height + 1;
            ;
        }
        break;
    }
    for (;;)
    {
        if (tree->left != NULL)
        {
            i = tree->height - 2;
            temp = height_from_beginning(tree->left, i);
            tree->height = tree->left->height + 1;
        }
        break;
    }
    // i++;
    // tree->height = i;
    return tree;
}

struct Node *update_height(Node *tree)
{ // обновление высоты узлов
    if (tree->right->height > tree->left->height)
    {
        tree->height = tree->right->height + 1;
        return tree;
    }
    else
    {
        tree->height = tree->left->height + 1;
        return tree;
    }
}

struct Node *change_height(Node *tree)
{                    // изменение высот узлов дерева
    int counter = 0; // счетчик для проверки: изменялась лм высота узла

    if (tree->right != NULL)
    {
        tree->height++;
        counter++;
        tree = change_height(tree->right);
    }

    if (tree->left != NULL)
    {
        if (tree->right == NULL)
        {
            counter++;
            tree->height++;
        }
        tree = change_height(tree->left);
    }

    return tree;
}

int BF(Node *tree)
{ // коэффициент балансировки
    if (tree->right != NULL && tree->left != NULL)
        return (tree->right->height - tree->left->height);
    else if (tree->right == NULL && tree->left != NULL)
        return -(tree->left->height);
    else
        return tree->right->height;
}

struct Node *init(Node *tree)
{ // инициализация дерева
    tree = (Node *)malloc(sizeof(Node));
    if (!tree)
        cout << "Memory error!";

    tree->left = NULL;
    tree->right = NULL;
    tree->height = 0;

    return tree;
}

struct Node *RightRotation(Node *tree)
{ // правый поворот
    Node *temp = (Node *)malloc(sizeof(Node));
    temp = tree->left;
    tree->left = temp->right;
    temp->right = tree;
    return temp;
}

struct Node *LeftRotation(Node *tree)
{ // левый поворот
    Node *temp = (Node *)malloc(sizeof(Node));
    temp = tree->right;
    tree->right = temp->left;
    temp->left = tree;
    return temp;
}

struct Node *Balance(Node *tree)
{ // балансировка дерева
    if (BF(tree) == 2 && tree->right != NULL && tree->right->left != NULL && tree->right->right != NULL && tree->right->left->height > tree->right->right->height)
    {
        tree = RightRotation(tree);
        return LeftRotation(tree);
    }

    else if (BF(tree) == -2 && tree->left != NULL && tree->left->right != NULL && tree->left->left != NULL && tree->left->right->height > tree->left->left->height)
    {
        tree = LeftRotation(tree);
        return RightRotation(tree);
    }

    if (BF(tree) == 2 && tree->right->left != NULL && tree->right->right != NULL && tree->right->left->height <= tree->right->right->height)
        return LeftRotation(tree);
    else if (BF(tree) == 2 && tree->left->right != NULL && tree->left->left != NULL && tree->left->right->height <= tree->left->left->height)
        return RightRotation(tree);

    /*if (BF(tree) == 2)
    {
        if (BF(tree->right) < 0)
            tree->right = RightRotation(tree->right);
        return LeftRotation(tree);
    }

    if (BF(tree) == -2)
    {
        if (BF(tree->left) > 0)
            tree->left = LeftRotation(tree->left);
        return RightRotation(tree);
    }*/

    /*Node *temp = (Node *)malloc(sizeof(Node));

    if ((tree->right != NULL && tree->right->right != NULL) or (tree->right != NULL && tree->right->left != NULL))
    {
        tree->right->height--;
        temp = Balance(tree->right);
        temp->right->height++;
    }
    else if ((tree->left != NULL && tree->left->right != NULL) or (tree->left != NULL && tree->left->left != NULL))
    {
        tree->left->height--;
        temp = Balance(tree->left);
        tree->left->height++;
    }

    if (tree->right != NULL && tree->right->height == 1 && tree->left == NULL)
        return LeftRotation(tree);
    if (tree->left != NULL && tree->left->height == 1 && tree->right == NULL)
        return RightRotation(tree);*/
    return tree;
}

bool is_clear(Node *tree)
{ // проверка пустоты бинарного дерева
    if (tree == NULL)
    {
        return 1;
    }
    return 0;
}

struct Node *node_search(Node *tree, int key, int &repeat_counter)
{ // поиск узла, после которого нужно вставить следующий элемент
    if (key > tree->key && tree->right != NULL)
    { // переход на правый узел
        tree = tree->right;
        tree = node_search(tree, key, repeat_counter);
    }
    else if (key < tree->key && tree->left != NULL)
    { // переход на левый узел
        tree = tree->left;
        tree = node_search(tree, key, repeat_counter);
    }
    else
    {
        if (key == tree->key)
        {
            repeat_counter++;
            return tree;
        }
    }
    return tree;
}

struct Node *append(Node *tree, int key, int &i)
{ // добавление элемента
    if (is_clear(tree))
    {
        tree = init(tree);
        tree->key = key;
        return tree;
    }

    else
    {
        Node *temp = (Node *)malloc(sizeof(Node)); // временный указатель для пустого узла
        if (!temp)
            cout << "Memory error!";

        temp->right = NULL;
        temp->left = NULL;
        temp->height = 0;

        Node *temp2 = (Node *)malloc(sizeof(Node)); // временный указатель
        if (!temp2)
            cout << "Memory error!";

        int repeat_counter = 0; // счетчик для проверки: есть ли одинаковые элементы или нет

        temp2 = node_search(tree, key, repeat_counter);

        if (key > tree->key && repeat_counter == 0)
        {
            temp2->right = temp;
            temp2->right->key = key;
            int i = -1;
            tree = height_from_beginning(tree, i);
            // temp = change_height(tree);
            temp = Balance(tree);
            i = -1;
            tree = height_from_beginning(tree, i);
            return temp;
        }

        else if (key < tree->key && repeat_counter == 0)
        {
            temp2->left = temp;
            temp2->left->key = key;
            temp = change_height(tree);
            temp = Balance(tree);
            int i = -1;
            tree = height_from_beginning(tree, i);
            return tree;
        }
        else
        {
            if (repeat_counter != 0)
            {
                cout << "В бинарном дереве не могут повторяться элементы. Введите другой элемент" << endl;
                i--;
                return tree;
            }
        }
    }
    return tree;
}

void output(Node *tree)
{ // вывод элементов при помощи рекурсивного прямого обхода
    if (tree != NULL)
    {
        output(tree->left);
        cout << tree->key << " ";
        output(tree->right);
    }
}

void del(Node *tree)
{ // удаление всего дерева
    if (tree != NULL)
    {
        del(tree->left);
        del(tree->right);
        free(tree);
    }
}

struct Node *min_search(Node *temp)
{ // поиск минимального элемента до тех пор, пока правый узел не будет равен NULL
    if (temp->right == NULL)
        return temp;
    else
        temp = min_search(temp->right);
    return temp;
}

struct Node *del_node(Node *tree, int key)
{ // удаление введенного элемента
    if (tree == NULL)
    {
        cout << "Дерево пустое" << endl;
        return tree;
    }
    else if (key > tree->key)
        tree->right = del_node(tree->right, key);
    else
    {
        if (key < tree->key)
            tree->left = del_node(tree->left, key);
        else
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp = tree;
            if (temp->right == NULL)
                tree = temp->left;
            else if (temp->left == NULL)
                tree = temp->right;
            else
            {
                temp = min_search(temp->left);
                tree = del_node(tree, temp->key);
                tree->key = temp->key;
            }
        }
    }
    return tree;
}

int main()
{
    Node *tree = NULL;

    int n;

    cout << "Введите количество элементов, которое хотите добавить в АВЛ-дерево: ";
    cin >> n;

    if (n <= 0)
        return 0;

    for (int i = 0; i < n; i++)
    { // ввод элементов
        int key;
        cout << "Введите новый элемент: ";
        cin >> key;
        tree = append(tree, key, i);
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
            return 0;

        else if (answer == 1)
        {
            int key;
            cout << "Введите элемент, который хотите удалить: ";
            cin >> key;
            tree = del_node(tree, key);
            tree = Balance(tree);
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
