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
            return (int)ch * 49 / 100;
        }

        static bool HashTableContains(char ch, HashElement[] hashTable)
        {
            int bucket = HashCode(ch) % hashTable.Length;

            if (hashTable[bucket] != null && hashTable[bucket].Symbol == ch)
                return true;

            return false;
        }

        static HashElement[] AddToHashTable(HashElement[] hashTable, char ch)
        {
            if (HashTableContains(ch, hashTable))
            {
                int bucket = HashCode(ch) % hashTable.Length;

                hashTable[bucket].Amount++;
            }

            else
            {
                if (hashTable[HashCode(ch) % hashTable.Length] != null)
                    hashTable = IncreaseHashtable(hashTable);

                int bucketNumber = HashCode(ch) % hashTable.Length;

                hashTable[bucketNumber] = new HashElement(ch);
            }
            return hashTable;
        }

        static HashElement[] IncreaseHashtable(HashElement[] hashTable)
        {
            HashElement[] newHashTable = new HashElement[hashTable.Length * 2];

            for (int i = 0; i < hashTable.Length; i++)
            {
                int bucket = HashCode(hashTable[i].Symbol) % newHashTable.Length;

                newHashTable[bucket] = hashTable[i];
            }

            return newHashTable;
        }
    }
}
