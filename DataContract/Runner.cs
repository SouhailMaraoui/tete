using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

public class Runner
{
    public Script script { get; set; }
    public Worker worker { get; set; }

    public Runner(Worker w, Script s)
    {
        worker=w;
        script=s;
    }
}
