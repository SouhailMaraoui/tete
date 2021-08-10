using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

public class Worker
{
    public int id { get; set; }
    public string name { get; set; }
    public string address { get; set; }

    public Worker(string n, string a)
    {
        name=n;
        address=a;
    }

}