using System;

namespace laba3
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("Введите строку симвлов");

            string str = Console.ReadLine();

            HashElement[] hashTable = new HashElement[1];

            foreach (char ch in str)
                hashTable = AddToHashTable(hashTable, ch);

            PrintHashTable(hashTable);

            while (true)
            {
                Console.Write("Введите символ, который хотите найти: ");

                str = Console.ReadLine();
                
                if (str.Length > 1)
                {
                    Console.WriteLine("Ошибка: введите 1 символ\n");
                    continue;
                }

                if (HashTableContains(Convert.ToChar(str), hashTable))
                    Console.WriteLine("Данный символ ИМЕЕТСЯ в введенной строке\n");

                else
                    Console.WriteLine("Данного символа НЕТ в введенной строке\n");
            }
        }

        class HashElement
        {
            public char Symbol { get; set; }
            public int Amount { get; set; }

            public HashElement(char symbol, int amount = 1)
            {
                Symbol = symbol;
                Amount = amount;
            }
        }

        static int HashCode(char ch)
        {
            return (int)ch;
        }

        static int GetIndex(char ch, int length)
        {
            return HashCode(ch) % length;
        }

        static bool HashTableContains(char ch, HashElement[] hashTable)
        {
            int bucket = GetIndex(ch, hashTable.Length);

            if (hashTable[bucket] != null && hashTable[bucket].Symbol == ch)
                return true;

            return false;
        }

        static HashElement[] AddToHashTable(HashElement[] hashTable, char ch)
        {
            if (HashTableContains(ch, hashTable))
            {
                int bucket = GetIndex(ch, hashTable.Length);

                hashTable[bucket].Amount++;
            }

            else
            {
                if (hashTable[GetIndex(ch, hashTable.Length)] != null)
                    hashTable = IncreaseHashtable(hashTable);

                int bucketNumber = GetIndex(ch, hashTable.Length);

                if (hashTable[bucketNumber] != null)
                    hashTable = AddToHashTable(hashTable, ch);

                else
                    hashTable[bucketNumber] = new HashElement(ch);
            }
            return hashTable;
        }

        static HashElement[] IncreaseHashtable(HashElement[] hashTable)
        {
            HashElement[] newHashTable = new HashElement[hashTable.Length * 2];

            for (int i = 0; i < hashTable.Length; i++)
            {
                if (hashTable[i] == null)
                    continue;

                int bucket = GetIndex(hashTable[i].Symbol, newHashTable.Length);

                newHashTable[bucket] = hashTable[i];
            }

            return newHashTable;
        }

        static void PrintHashTable(HashElement[] hashTable)
        {
            foreach (HashElement hashElement in hashTable)
            {
                if (hashElement == null)
                    continue;

                Console.WriteLine($"Буква: {hashElement.Symbol}. Количество вхождений: {hashElement.Amount}");
            }

            Console.WriteLine();
        }
    }
}
