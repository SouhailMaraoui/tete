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
    public class ExecController : ControllerBase
    {

        [HttpPost]
        public HttpResponseMessage Run(Runner runner)
        {

            using (var client = new HttpClient())
            {
                var toSend = new StringContent(JsonConvert.SerializeObject(runner.script), Encoding.UTF8, "application/json");
                return client.PostAsync(runner.worker.address + "exec", toSend).Result;
            }
        }
    }
}
