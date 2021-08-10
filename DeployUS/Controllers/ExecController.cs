using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
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
        public Object Run(Runner runner)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    var toSend = new StringContent(JsonConvert.SerializeObject(runner.script), Encoding.UTF8, "application/json");

                    var response = client.PostAsync("http://"+runner.worker.address + ":5003/exec", toSend).Result;
                    var contents = response.Content.ReadAsStringAsync().Result;

                    return contents;
                }
                catch(AggregateException)
                {
                    return new HttpResponseMessage(HttpStatusCode.BadGateway); ;
                }
            }
        }
    }
}
