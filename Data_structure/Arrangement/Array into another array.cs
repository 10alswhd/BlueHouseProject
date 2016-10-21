namespace nure
{
    class task
    {
        static void Main(string[] args)
        {
            int[] a = {1, 5, 2, 4, 0, 1, 3, 2, 0, 9, 10, 0, 12 } ,  b = new int[a.Length];            
            int lasteven = 0, lastodd = b.Length - 1;
           
            for (int i = 0; i < a.Length; i++)
            {
                if (a[i] % 2 == 0 && a[i] != 0)
                {
                    b[lasteven] = a[i];
                    lasteven++;
                }
                else if (a[i] != 0)
                {
                    b[lastodd] = a[i];
                    lastodd--;
                }
            }
            Console.WriteLine(string.Join(",", a));
            Console.WriteLine(string.Join(",", b));
        }
    }
