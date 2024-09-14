using System;

namespace laba1
{
    internal class Program
    {
        static void Main()
        {
            Console.Write("Введите n: ");
            string strTemp = Console.ReadLine();

            while (!IsInt(strTemp))
            {
                Console.Write("Введите n: ");
                strTemp = Console.ReadLine();
            }

            int[] minHeap = new int[Convert.ToInt32(strTemp)];

            for (int i = 0; i < minHeap.Length; i++)
                AddElementToHeap(ref minHeap, i);

            HeapFunc(ref minHeap);

            Node binaryHeap = new Node(minHeap[0]);

            if (minHeap.Length >= 2)
                binaryHeap.Left = ConvertArrayToList(binaryHeap.Left, minHeap, 0, 1);

            if (minHeap.Length >= 3)
                binaryHeap.Right = ConvertArrayToList(binaryHeap.Right, minHeap, 0, 2);

            PrintHeap(minHeap);

            Console.WriteLine($"\nМинимальный элемент: {minHeap[0]}");

            int[] newHeap = RemoveMin(minHeap);

            if (newHeap.Length >= 2)
                binaryHeap.Left = ConvertArrayToList(binaryHeap.Left, newHeap, 0, 1);

            if (newHeap.Length >= 3)
                binaryHeap.Right = ConvertArrayToList(binaryHeap.Right, newHeap, 0, 2);

            PrintHeap(newHeap);
        }

        class Node
        {
            public int Value { get; set; }
            public Node Left { get; set; }
            public Node Right { get; set; }

            public Node(int value)
            {
                Value = value;
                Left = null;
                Right = null;
            }
        }

        static bool IsInt(string str)
        {
            foreach (char ch in str)
            {
                if ((int)ch < 48 || (int)ch > 57)
                    return false;
            }

            return true;
        }

        static void AddElementToHeap(ref int[] heap, int i)
        {
            Console.Write($"Введите {i + 1} член кучи: ");
            string strTemp = Console.ReadLine();

            while (!IsInt(strTemp))
            {
                Console.Write($"Введите {i + 1} член кучи: ");
                strTemp = Console.ReadLine();
            }

            heap[i] = Convert.ToInt32(strTemp);
            int parent = (i - 1) / 2;

            while (i > 0 && heap[i] < heap[parent]) //
            {
                (heap[parent], heap[i]) = (heap[i], heap[parent]);

                i = parent;
                parent = (i - 1) / 2;
            }
        }

        static void Heapify(ref int[] heap, int i)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < heap.Length)
            {
                if (heap[i] > heap[left]) //
                {
                    (heap[left], heap[i]) = (heap[i], heap[left]);

                    Heapify(ref heap, left);
                }
            }

            if (right < heap.Length)
            {
                if (heap[i] > heap[right]) //
                {
                    (heap[right], heap[i]) = (heap[i], heap[right]);

                    Heapify(ref heap, right);
                }
            }
        }

        static void HeapFunc(ref int[] heap)
        {
            for (int i = (heap.Length / 2 + 1); i > -1; i--) 
                Heapify(ref heap, i);
        }

        static Node ConvertArrayToList(Node node,int[] heap, int position, byte rightOrLeft)
        {
            if (rightOrLeft == 1) // left
            {
                int left = 2 * position + 1;
                position = left;

                node = new Node(heap[left]);

                left = 2 * position + 1;
                int right = 2 * position + 2;

                if (left <= heap.Length - 1)
                    node.Left = ConvertArrayToList(node.Left, heap, position, 1);

                if (right <= heap.Length - 1)
                    node.Right = ConvertArrayToList(node.Right, heap, position, 2);

                return node;
            }

            else // right
            {
                int right = 2 * position + 2;
                position = right;

                node = new Node(heap[right]);

                right = 2 * position + 2;
                int left = 2 * position + 1;

                if (left <= heap.Length - 1)
                    node.Left = ConvertArrayToList(node.Left, heap, position, 1);

                if (right <= heap.Length - 1)
                    node.Right = ConvertArrayToList(node.Right, heap, position, 2);

                return node;
            }
        }

        static int[] RemoveMin(int[] heap)
        {
            int[] newHeap = new int[heap.Length - 1];

            for (int i = 0; i < newHeap.Length; i++)
                newHeap[i] = heap[i + 1];

            HeapFunc(ref newHeap);

            return newHeap;
        }

        static void PrintHeap(int[] heap)
        {
            int elementsInLine = 1;

            for (int i = 0; i < heap.Length; i++)
            {
                if (i + 1 == elementsInLine)
                {
                    elementsInLine = (i + 1) * 2;
                    Console.WriteLine();
                }

                Console.Write(heap[i] + " ");
            }

            Console.WriteLine();
        }
    }
}
