using System;
using System.Collections.Generic;

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

            Console.WriteLine("1");
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
    }
}
