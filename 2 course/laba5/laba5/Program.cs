int n;

while(true)
{
    Console.Write("Введите количество элементов для массива: ");

    if (Int32.TryParse(Console.ReadLine(), out n))
        break;
}
Console.WriteLine();

int[] array = new int[n];
int[] arrayForBubbleSort = new int[n];
int[] arrayForShellSort = new int[n];

Random random = new Random();

for (int i = 0; i < n; i++)
{
    array[i] = random.Next(1, 1000);
    arrayForBubbleSort[i] = array[i];
    arrayForShellSort[i] = array[i];
}

PrintArray(array, n, "Изначальный массив: ");

BubbleSort(arrayForBubbleSort, n);
PrintArray(arrayForBubbleSort, n, "Сортировка пузырьком: ");

ShellSort(arrayForShellSort, n);
PrintArray(arrayForShellSort, n, "Сортировка Шелла: ");

static void BubbleSort(int[] array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - (i + 1); j++)
        {
            if (array[j] > array[j + 1])
                (array[j], array[j + 1]) = (array[j+ 1], array[j]);
        }
    }
}

static void ShellSort(int[] array, int n)
{
    int step = n / 2;

    while (step >= 1)
    {
        for (int i = 0; i + step < n; i += step)
        {
            if (array[i] > array[i + step])
            {
                (array[i], array[i + step]) = (array[i + step], array[i]);

                for (int j = i; j - step >= 0; j -= step)
                {
                    if (array[j - step] >= array[j])
                        (array[j], array[j - step]) = (array[j - step], array[j]);
                }
            }
        }

        step /= 2;
    }
}

static void PrintArray(int[] array, int n, string title)
{
    Console.Write(title);

    foreach (int elem in array)
        Console.Write($"{elem} ");

    Console.WriteLine();
    Console.WriteLine();
}
