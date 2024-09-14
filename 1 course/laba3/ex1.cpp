#include <iostream>
#include <cstdlib>

using namespace std;

struct list
{                                                    // список
    int node;                                        // узел списка
    struct list *ptr = (list *)malloc(sizeof(list)); // указатель на следующий элемент
};

struct queue
{                             // очередь, реализованная через односвязный линейный список
    struct list *rear, *frnt; // rear - номер первого элемента в очереди(для ввода в массив) , frnt - номер последнего элемента в очередь(для вывода)
};

struct queue *init(queue *root, list *node)
{ // инициализация очереди
    list *temp = (list *)malloc(sizeof(list));
    if (!temp) // проверка
        cout << "Memory error!";

    root->rear = temp;
    root->frnt = temp;

    root->rear->ptr = NULL;
    root->frnt->ptr = NULL;

    node = temp;

    node->ptr = NULL;
    return root;
}

struct list *add(list *node, int x, int i)
{                                              // добавление элементов в очередь
    list *temp = (list *)malloc(sizeof(list)); // временная указатель для занесения в него данных
    if (!temp) // проверка
        cout << "Memory error!";
    list *p = (list *)malloc(sizeof(list));    // временный указатель для поиска конечного элемента списка
    if (!p) // проверка
        cout << "Memory error!";

    temp->node = x;
    temp->ptr = NULL;

    if (i == 0)
    {
        node = temp;
        return node;
    }
    else if (i == 1)
    {
        node->ptr = temp;
        return node;
    }
    else
    {
        for (p = node; p->ptr != NULL;)
            p = p->ptr;
        p->ptr = temp;
        return node;
    }
}

struct list *second_variable_delete(list *node, int &n)
{ // удаление каждого второго элемента очереди
    list* temp = (list*)malloc(sizeof(list)); // выделение памяти для занесение во временную память удаляемого узла
    if (!temp) // проверка
        cout << "Memory error!";
    temp = node;

    for (int i = 0; i < n; i++)
    { // перенос указателей с удаленных узлов на сохранившееся
        if (i % 2 == 1){
            temp->ptr = temp->ptr->ptr;
            temp = temp->ptr;
        }
    }

    n = (n + 1) / 2;
    return temp;
}

void inputting(list* node, int n){ // вывод элементов очереди
    for (int i = 0; i < n; i++){
        cout << node->node << " ";
        node = node->ptr;
    }
    cout << endl;
}

int main()
{
    int n;

    queue *root = (queue *)malloc(sizeof(queue)); // выделение памяти для корня
    if (!root) // проверка
        cout << "Memory error!";
    list *node = (list *)malloc(sizeof(list));    // выделение памяти для узла, в котором мы находимся в данный момент
    if (!node) // проверка
        cout << "Memory error!";

    cout << "Введите количество элементов очереди: ";
    cin >> n;

    if (n <= 0)
        return 0;

    root = init(root, node); // вызов функции инициализации очереди
    node = root->rear;

    for (int i = 0; i < n; i++)
    { // добавление элементов в очередь
        cout << "Введите " << i + 1 << " элемент очереди: ";
        int x;
        cin >> x;
        node = add(node, x, i); // вызов функции добавления элементов в очередь
    }

    root->rear = node; // присвоение корню оставшихся узлов

    cout << "Элементы очереди:";
    inputting(node, n); // вызов функции вывода элементов очереди

    root->rear = second_variable_delete(node, n); // вызов функции удаления каждого второго элемента очереди

    cout << "Элементы измененной очереди:";
    inputting(node, n); // вызов функции вывода элементов очереди

    free(root);
    free(node);
    return 0;
}
