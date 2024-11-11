Console.Write("Введите строку: ");

string? str = Console.ReadLine();

if (str is null || str == "")
    return;

str = str.ToLower();

List<char> symbols = new();
List<int> repetitions = new();

foreach (char c in str)
{
    if (symbols.Contains(c))
        repetitions[symbols.IndexOf(c)]++;
    else
    {
        symbols.Add(c);
        repetitions.Add(1);
    }
}

for (int i = 0; i < symbols.Count; i++)
{
    Node node = new()
    {
        Element = symbols[i],
        Repetitions = repetitions[i]
    };

    Huffman.Tree.Add(node);
}

Huffman.SortList();

while (Huffman.Tree.Count > 1)
{
    Huffman.CreateNode();
    Huffman.SortList();
}

List<string[]> charCodes = new();

for (int i = 0; i < symbols.Count; i++)
{
    string code = string.Empty;
    Node tempNode = Huffman.Tree[0];

    while (true)
    {
        if (tempNode.Left != null && tempNode.Left.IsChecked == false)
        {
            tempNode = tempNode.Left;
            code += "0";
        }
        else if (tempNode.Right != null && tempNode.Right.IsChecked == false)
        {
            tempNode = tempNode.Right;
            code += "1";
        }
        else if (tempNode.Element != null)
        {
            charCodes.Add([$"{tempNode.Element}", $"{code}"]);
            tempNode.IsChecked = true;
            break;
        }
        else
        {
            tempNode.IsChecked = true;
            i--;
            break;
        }
    }
}

Console.WriteLine();
for (int i = 0; i < charCodes.Count; i++)
    Console.WriteLine($"{charCodes[i][0]} = {charCodes[i][1]}");
Console.WriteLine();

foreach (char c in str)
{
    for (int i = 0; ; i++)
    {
        if (charCodes[i].Contains(Convert.ToString(c)))
        {
            Console.Write($"{charCodes[i][1]} ");
            break;
        }
    }
}
Console.WriteLine();

static class Huffman
{
    public static List<Node> Tree = new();

    public static void CreateNode()
    {
        Node node1 = Tree[0];
        Node node2 = Tree[1];

        Node newNode = new()
        {
            Repetitions = node1.Repetitions + node2.Repetitions,
            Right = node1,
            Left = node2,
        };

        Tree[0] = newNode;
        Tree.Remove(node2);
    }

    public static void SortList()
    {
        for (int i = 0; i < Tree.Count - 1; i++)
        {
            for (int j = 0; j < Tree.Count - (i + 1); j++)
            {
                if (Tree[j].Repetitions > Tree[j + 1].Repetitions)
                    (Tree[j], Tree[j + 1]) = (Tree[j + 1], Tree[j]);
            }
        }
    }
}

class Node
{
    public char? Element { get; set; } = null;
    public int Repetitions { get; set; }
    public Node? Right { get; set; } = null;
    public Node? Left { get; set; } = null;
    public bool IsChecked { get; set; } = false;
}
