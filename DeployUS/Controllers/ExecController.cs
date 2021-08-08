using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace DeployUS.Controllers
{
    [Route("exec")]
    [ApiController]
    public class InterfaceController : ControllerBase
    {

        [HttpPost]
        public string Run(Worker worker, Script script)
        {
            using (var client = new HttpClient())
            {
                var toSend = new StringContent(JsonConvert.SerializeObject(script), Encoding.UTF8, "application/json");
                return client.PostAsync(worker.address + "exec", toSend).Result;
            }
        }
    }
}
