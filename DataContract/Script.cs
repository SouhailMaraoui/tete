using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

public class Script
{
    public int id { get; set; }
    public string name { get; set; }
    public string script { get; set; }

    public Script(string n, string s)
    {
        name=n;
        script=s;
    }
}
