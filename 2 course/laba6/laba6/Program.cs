int n;

Console.Write("Введите число вершин ПОЛНОГО БИНАРНОГО ДЕРЕВА: ");

while (!Int32.TryParse(Console.ReadLine(), out n))
    Console.Write("Введите корректное число: ");

if (n == 0)
    return;

List<int> elems = new();
List<TreeNode> nodesList = new();

for (int i = 0; i < n; i++)
{
    Console.Write($"Введите значение для {i + 1}-ой вершины: ");

    int elem;
    while (!Int32.TryParse(Console.ReadLine(), out elem))
        Console.Write("Введите корректное число: ");

    elems.Add(elem);
}

Tree.Root = Tree.BuildTreeHelper(elems, 0, nodesList);
Tree.MaxSum = Tree.Root!.Element;

foreach (TreeNode node in nodesList)
    Tree.FindMaxSum(node, 0);

Console.WriteLine($"Максимальная сумма: {Tree.MaxSum}");

static class Tree
{
    static public TreeNode? Root {  get; set; }
    static public int MaxSum { get; set; }

    static public TreeNode? BuildTreeHelper(List<int> elems, int i, List<TreeNode> nodeList)
    {
        if (i >= elems.Count)
            return null;

        TreeNode node = new(elems[i]);
        nodeList.Add(node);

        node.Left = BuildTreeHelper(elems, 2 * i + 1, nodeList);
        node.Right = BuildTreeHelper(elems, 2 * i + 2, nodeList);

        return node;
    }

    static public void FindMaxSum(TreeNode node, int currentSum)
    {
        currentSum += node.Element;

        if (currentSum > Tree.MaxSum)
            Tree.MaxSum = currentSum;

        if (node.Left is not null)
            Tree.FindMaxSum(node.Left, currentSum);
        if (node.Right is not null)
            Tree.FindMaxSum(node.Right, currentSum);
    }
}

class TreeNode
{
    public int Element {  get; set; }
    public TreeNode? Left { get; set; }
    public TreeNode? Right { get; set; }

    public TreeNode(int element)
    {
        Element = element;
    }
}
