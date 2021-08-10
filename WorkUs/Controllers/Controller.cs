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
using System.IO;

namespace WorkUs.Controllers
{
    [Route("exec")]
    [ApiController]
    public class Controller : ControllerBase
    {

        [HttpPost]
        public Object Run(Script script)
        {
            System.Console.WriteLine("RUNNING ==================");
            System.Console.WriteLine(script.script);
            System.Console.WriteLine("END ======================\n");
            var scriptText = script.script.Replace("\"", "\\\"");

            var folderName=script.name+"_"+script.id.ToString();

            System.IO.Directory.CreateDirectory(folderName);
            System.IO.File.WriteAllText(folderName+"/docker-compose.yml", scriptText);

            var cmd=$"docker-compose up -f {folderName}/docker-compose.yml --force-recreate --remove-orphans -d"; 

            ProcessStartInfo startInfo = new ProcessStartInfo() { 
                FileName = "/bin/bash",
                Arguments = $"-c \"{cmd}\"",
                RedirectStandardError = true,
                UseShellExecute = false,
            }; 

            Process proc = new Process() { StartInfo = startInfo, };
            proc.Start();

            while(!proc.WaitForExit(5000));

            StreamReader reader = proc.StandardError;
            var ret=new Dictionary<string, string>();
            ret.Add("ExitCode",proc.ExitCode.ToString());
            ret.Add("Message",reader.ReadLine());

            return ret;
        }
    }
}
