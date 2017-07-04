using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabPW8_9
{
    class Program
    {
        static void Main(string[] args)
        {
            float a = float.Parse(Console.ReadLine());
            float b = float.Parse(Console.ReadLine());
            float c = float.Parse(Console.ReadLine());
            var d = b * b - 4 * a * c;
            var x1 = (-b + Math.Sqrt(d)) / (2 * a);
            var x2 = (-b - Math.Sqrt(d)) / (2 * a);
            Console.WriteLine(" x1 ={0}, x2={1}", x1, x2);
            Console.ReadKey();
        }
    }
}
