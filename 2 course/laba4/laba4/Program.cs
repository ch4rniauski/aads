byte verticeAmount;

while (true)
{
    Console.Write("Введите количество вершин ориентированного графа: ");

    if (byte.TryParse(Console.ReadLine(), out verticeAmount))
        break;

    Console.WriteLine("Ошибка");
}

List<GraphVertice> graph = new();

for (int i = 0; i < verticeAmount; i++)
{
    Console.Write($"Введите номера вершин, исходящих из {i+1} вершины (через пробел): ");

    string[]? elements = Console.ReadLine()!.Split(' ');

    GraphVertice vertice = new();
        
    if (elements[0] != "")
    {
        vertice.AdjacentVertices = new int[elements.Length];
        for (int j = 0; j < elements.Length; j++)
        {
            if (Int32.TryParse(elements[j], out int result))
                vertice.AdjacentVertices[j] = result - 1;
        }
    }
    graph.Add(vertice);
}

for (int i = 0; i < verticeAmount; i++)
{
    Console.Write($"Введите символ для {i + 1} вершины: ");

    if (Char.TryParse(Console.ReadLine(), out char result))
        graph[i].Element = result;
    else
    {
        Console.WriteLine("Ошибка");
        i--;
        continue;
    }
}

Console.WriteLine($"Лексикографически первый путь на графе: {FindLexicographicallyFirstPath(graph)}");

static string FindLexicographicallyFirstPath(List<GraphVertice> graph)
{
    List<string> paths = new();

    for (int i = 0; i < graph.Count; i++)
        DeepSearch(i, "", new List<int>(), ref paths, graph);

    Console.WriteLine("Все возможные пути, исходя из введенных данных:");
    for (int i = 0; i < paths.Count; i++)
        Console.WriteLine($"\t{paths[i]}");

    paths.Sort();

    return paths.Count > 0 ? paths[0] : "Нет доступных путей на графе.";
}

static void DeepSearch(int currentVertice, string currentPath, List<int> visitedVertices, ref List<string> paths, List<GraphVertice> graph)
{
    visitedVertices.Add(currentVertice);

    currentPath += graph[currentVertice].Element;

    if (graph[currentVertice].AdjacentVertices != null)
    {
        foreach (int adjacentVertice in graph[currentVertice].AdjacentVertices!)
        {
            if (!visitedVertices.Contains(adjacentVertice))
            {
                List<int> newVisitedVertices = new List<int>(visitedVertices);
                DeepSearch(adjacentVertice, currentPath, newVisitedVertices, ref paths, graph);
            }
        }
    }
    else
        paths.Add(currentPath);
}

class GraphVertice
{
    public char Element {  get; set; }
    public int[]? AdjacentVertices { get; set; } = null;
}
