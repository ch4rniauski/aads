#include <iostream>
#include <cstdlib>

using namespace std;

struct list
{
    int number;
    struct list *next;
    struct list *prev;
};

struct list *init(int element)
{                                              // инициализация двусвязного циклического списка
    list *root = (list *)malloc(sizeof(list)); // выделение памяти для указателя на корень
    root->next = root;
    root->prev = root;
    root->number = element;
    return root;
}

struct list *add(list *root, list *node, int element)
{                                              // добавление узлов
    list *temp = (list *)malloc(sizeof(list)); // выделение памяти для нового узла

    temp->number = element; // ввод значения нового элемента
    temp->next = root;      // после последнего узла идет корень, т.к. цикличный список
    temp->prev = node;      // перед новым узлом идет предыдущий узел

    root->prev = temp;       // предыдущий элемент корня = последнему введенному
    temp->prev->next = temp; // указатель предыдущего элемента на следующий указывает на текущий элемент
    return temp;
}

struct list *shift(int answer, list *root)
{ // сдвиг элементов списка по кольцу
    if (answer > 0)
    { // сдвиг вправо
        for (int i = 0; i < answer; i++)
            root = root->prev;
    }
    else
    { // сдвиг влево
        for (int i = 0; i > answer; i--)
            root = root->next;
    }
    return root;
}

void outputting(list *root)
{                      // вывод элементов списка
    list *temp = root; // временный указатель на элемент
    while (temp->next != root)
    {
        cout << temp->number << " ";
        temp = temp->next;
    }
    cout << temp->number;
    cout << endl;
}

int main()
{
    cout << "Введите значение элемента в диапазоне от -50 до +50. Чтобы прекратить запись элементов, введите число, выходящее за эти рамки." << endl;
    cout << ">";

    int element;

    list *node; // указатель на узел
    list *root; // указатель на корень

    cin >> element;
    if (element < -50 || element > 50) // проверка
        return 0;
    else
        node = init(element); // вызов функции инициализации двусвязного циклического списка
    root = node;

    for (;;)
    { // добавление элементов в двусвязный циклический список
        cout << "Введите значение элемента в диапазоне от -50 до +50. Чтобы прекратить запись элементов, введите число, выходящее за эти рамки." << endl;
        cout << ">";
        cin >> element;
        if (element < -50 || element > 50) // проверка
            break;
        else
            node = add(root, node, element); // вызов функции добавления элемента в двусвязный циклический список
    }

    for (int answer = 0;;)
    { // смещение по кольцу элементов двусвязного циклического списка
        cout << "Введите, на сколько элементов Вы хотите сдвинуть список по кольцу(положительное число = сдвиг вправо, отрицательное = влево, 0 = прервать работу): ";
        cin >> answer;
        if (answer == 0)
            break;

        else
            root = shift(answer, root); // вызов функции сдвига элементов списка по кольцу
        outputting(root);               // вызов функции сдвига элементов списка
    }

    free(root);
    return 0;
}
