using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace WorkUs.Controllers
{
    [Route("exec")]
    [ApiController]
    public class Controller : ControllerBase
    {

        [HttpPost]
        public string Run(Script script)
        {
            var scriptText = script.script.Replace("\"", "\\\"");

            ProcessStartInfo startInfo = new ProcessStartInfo() { 
                FileName = "/bin/bash",
                Arguments = $"-c echo \"{scriptText}\" > docker-compose.yml && docker-compose up",
                UseShellExecute = false,
                RedirectStandardOutput = true,
                CreateNoWindow = true
            }; 
            Process proc = new Process() { StartInfo = startInfo, };
            proc.Start();

            string ret="";
            while (!proc.StandardOutput.EndOfStream)
            {
                string line = proc.StandardOutput.ReadLine();
                ret+=line;
            }
            return ret;
        }
    }
}
