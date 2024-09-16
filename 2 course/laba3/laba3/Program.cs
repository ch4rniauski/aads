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

            Dictionary<char, int>[] hashTable = new Dictionary<char, int>[1];
        }

        static int HashCode(char ch)
        {
            return (int)ch * 49 / 100;
        }

        static bool HashTableContains(char ch, Dictionary<char, int>[] hashTable)
        {
            int bucket = HashCode(ch) % hashTable.Length;

            if (hashTable[bucket][ch] == ch)
                return true;

            return false;
        }

        static Dictionary<char, int>[] AddToHashTable(Dictionary<char, int>[] hashTable, char ch)
        {
            if (HashTableContains(ch, hashTable))
            {
                int bucket = HashCode(ch) % hashTable.Length;

                hashTable[bucket][ch]++;
            }

            else
            {
                if (hashTable[HashCode(ch) % hashTable.Length] != null)
                {
                    Dictionary<char, int>[] tempHashTable = new Dictionary<char, int>[hashTable.Length * 2];

                    for (int i = 0; i < hashTable.Length; i++)
                    {
                        int bucket = HashCode(ch) % tempHashTable.Length;

                        tempHashTable[bucket] = hashTable[i];

                        hashTable = tempHashTable;
                    }
                }

                int bucketNumber = HashCode(ch) % hashTable.Length;

                hashTable[bucketNumber] = new Dictionary<char, int>();
                hashTable[bucketNumber][ch] = 1;
            }
            return hashTable;
        }
    }
}
