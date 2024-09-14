#include <iostream>
#include <cstdlib>

using namespace std;

struct list
{                                                    // список
    int node;                                        // узел списка
    int priority;                                    // приоритет узла
    struct list *ptr = (list *)malloc(sizeof(list)); // указатель на следующий элемент
};

struct queue
{                             // очередь, реализованная через односвязный линейный список
    struct list *rear, *frnt; // rear - номер первого элемента в очереди(для ввода в массив) , frnt - номер последнего элемента в очередь(для вывода)
};

struct queue *init(queue *root, list *node)
{ // инициализация очереди с приоритетом
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

struct list *add(list *node, int x, int i, int priority)
{                                              // добавление элементов в очередь
    list *temp = (list *)malloc(sizeof(list)); // временная указатель для занесения в него данных
    if (!temp)                                 // проверка
        cout << "Memory error!";
    list *temp_now = (list *)malloc(sizeof(list)); // временный указатель места, где мы сейчас находимся
    if (!temp_now)                                 // проверка
        cout << "Memory error!";

    temp->priority = priority;
    temp->node = x;
    temp->ptr = NULL;

    if (i == 0)
    {
        node = temp;
        return node;
    }
    else
    {
        temp_now = node;

        for (int j = 0; j <= i; j++)
        {
            if (temp_now->priority == temp->priority)
            { // установка элемента после элемента с таким же приоритетом
                if (temp_now->ptr != NULL && temp_now->ptr->priority != temp->priority)
                { // не в самый конец очереди
                    temp->ptr = temp_now->ptr;
                    temp_now->ptr = temp;
                    break;
                }
                else if (temp_now->ptr == NULL)
                { // в самый конец очереди
                    temp_now->ptr = temp;
                    break;
                }
            }
            else if (temp_now->priority < temp->priority && temp_now->ptr != NULL && temp_now->ptr->priority > temp->priority)
            { // установка элемента после элемента с более низким приоритетом
                temp->ptr = temp_now->ptr;
                temp_now->ptr = temp;
                break;
            }
            else
            {
                if (temp_now->priority < temp->priority && temp_now->ptr == NULL)
                { // установка элемента с максимальным приоритетом в конец очереди
                    temp_now->ptr = temp;
                    break;
                }
                else if (temp_now->priority > temp->priority)
                { // добавление элемента с самым низким приоритетом в начало очереди
                    temp->ptr = temp_now;
                    return temp;
                }
            }
            temp_now = temp_now->ptr;
        }
        return node;
    }
}

struct list *delete_elem(list *node)
{                                              // удаление узла очереди
    list *temp = (list *)malloc(sizeof(list)); // временная указатель для занесения в него данных
    if (!temp)                                 // проверка
        cout << "Memory error!";
    temp = node->ptr;
    free(node);
    return temp;
}

void inputting(list *node, int n)
{ // вывод элементов очереди
    for (int i = 0; i < n; i++)
    {
        cout << node->node << " ";
        node = node->ptr;
    }
    cout << endl;
}

int main()
{
    int n;

    queue *root = (queue *)malloc(sizeof(queue)); // выделение памяти для корня
    if (!root)                                    // проверка
        cout << "Memory error!";
    list *node = (list *)malloc(sizeof(list)); // выделение памяти для узла, в котором мы находимся в данный момент
    if (!node)                                 // проверка
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
        int x;        // элемент
        int priority; // приоритет
        cin >> x;
        cout << "Введите приоритет " << i + 1 << " элемента очереди: ";
        cin >> priority;
        node = add(node, x, i, priority); // вызов функции добавления элементов в очередь
    }

    root->rear = node; // присвоение корню оставшихся узлов

    cout << "Элементы очереди:";
    inputting(node, n); // вызов функции вывода элементов очереди

    for (; n > 1;)
    {                             // постепенное удаление узла очереди
        node = delete_elem(node); // вызов функции удаления узлов очереди
        cout << "Элементы измененной очереди:";
        n--;
        inputting(node, n); // вызов функции вывода элементов очереди
    }

    free(root);
    free(node);
    return 0;
}
