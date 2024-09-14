using System;
using System.Collections.Generic;

namespace laba2
{
    internal class Program
    {
        static void Main()
        {
            SortedSet<int> set = new SortedSet<int>();
            
            while (true)
            {
                AddElementWithCommand(ref set);
            }
        }

        static void AddElementWithCommand(ref SortedSet<int> set)
        {
            string str = Console.ReadLine();
            str = str.ToLower();

            if ((str.Contains("push") && !str.Contains("delete")) || (!str.Contains("push") && str.Contains("delete")))
            {
                string tempStr = RemoveSpaces(str);

                if (tempStr == "push" || tempStr == "delete")
                    Console.WriteLine("Нужно ввести какое-нибудь значение");

                else
                {
                    if (tempStr.Contains("push"))
                    {
                        if (AddElementToSet(ref set, tempStr))
                            PrintSet(set);
                    }

                    else
                    {
                        if (RemoveElementFromSet(ref set, tempStr))
                            PrintSet(set);
                    }
                }
            }

            else
                Console.WriteLine("Неизвестная команда");
        }

        static bool AddElementToSet(ref SortedSet<int> set, string str)
        {
            string numberStr = "";
            byte minusCounter = 0;

            for (int i = 4; i < str.Length; i++)
            {
                if (((int)str[i] < 48 || (int)str[i] > 57) && str[i] != '-')
                {
                    Console.WriteLine("Введите целое число");
                    return false;
                }
                
                if (str[i] == '-')
                {
                    minusCounter++;

                    if (minusCounter == 2)
                    {
                        Console.WriteLine("Неизвестное число");
                        return false;
                    }
                }

                numberStr += str[i];
            }

            set.Add(Convert.ToInt32(numberStr));

            return true;
        }

        static bool RemoveElementFromSet(ref SortedSet<int> set, string str)
        {
            string numberStr = "";
            byte minusCounter = 0;

            for (int i = 6; i < str.Length; i++)
            {
                if (((int)str[i] < 48 || (int)str[i] > 57) && str[i] != '-')
                {
                    Console.WriteLine("Введите целое число");
                    return false;
                }

                if (str[i] == '-')
                {
                    minusCounter++;

                    if (minusCounter == 2)
                    {
                        Console.WriteLine("Неизвестное число");
                        return false;
                    }
                }

                numberStr += str[i];
            }

            set.Remove(Convert.ToInt32(numberStr));

            return true;
        }

        static string RemoveSpaces(string str)
        {
            if (str.Contains(" "))
            {
                for (int i = 0; i < str.Length; i++)
                {
                    if (str[i] == ' ')
                    {
                        str = str.Remove(i, 1);
                        i--;
                    }
                }
            }

            return str;
        }

        static void PrintSet(SortedSet<int> set)
        {
            foreach (int elem in set)
                Console.Write(elem + " ");

            Console.WriteLine();
        }
    }
}
