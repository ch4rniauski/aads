#include <iostream>
#include <cstdlib>

using namespace std;

struct list
{
    float element;
    struct list *ptr;
};

struct stack
{
    struct list *rear;
    int top;
};

void init(stack *stk)
{ // инициализация стека
    stk->rear = NULL;
    stk->top = 0;
}

struct stack *push(stack *stk)
{ // занесение значений в стек
    list *temp = (list *)malloc(sizeof(list));
    float element;
    cin >> element;
    temp->element = element;
    temp->ptr = stk->rear;
    stk->rear = temp;
    return stk;
}

float average_value(stack *stk, int n) // подсчет среднего значения элементов стека
{
    float averageValue = 0;

    list *temp = (list *)malloc(sizeof(list));
    temp = stk->rear;

    for (int i = 0; i < n; i++)
    {
        averageValue += temp->element;
        temp = temp->ptr;
    }

    return averageValue / n;
}

int number_element_larger_average(stack *stk, int n, float average)
{ // подсчет кол-ва элементов стека, значение которых выше среднего всех элементов стека
    int number = 0;

    list *temp = (list *)malloc(sizeof(list));
    temp = stk->rear;

    for (int i = 0; i < n; i++)
    {
        if (temp->element > average)
            number++;
        temp = temp->ptr;
    }

    return number;
}

int main()
{
    int n;

    cout << "Введите число элементов стека: ";
    cin >> n;

    stack *stk = (stack *)malloc(sizeof(stack)); // указатель на стек

    init(stk); // вызов ф-ции инициализации стека

    for (int i = 0; i < n; i++)
    {
        cout << "Введите " << i + 1 << " элемент стека: ";
        stk = push(stk); // вызов ф-ции занесения значений в стека
    }

    float average = average_value(stk, n); // вызов ф-ции подсчета среднего значения элементов стека

    cout << "Среднее значение элементов стека: " << average << endl;

    cout << "Количество элементов стека, значение которых выше среднего всех элементов стека: " << number_element_larger_average(stk, n, average) << endl; // вызов ф-ции подсчета кол-ва элементов стека, значение которых выше среднего всех элементов стека

    free(stk);
    return 0;
}
