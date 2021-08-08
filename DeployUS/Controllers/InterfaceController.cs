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
    [Route("api")]
    [ApiController]
    public class InterfaceController : ControllerBase
    {
        const int nullId = -1;
        const string serverAddr = "http://localhost:5000/";

        [HttpGet("{service}")]
        [HttpGet("{service}/{id}")]
        public object Get(string service, int id = nullId)
        {
            using (var client = new HttpClient())
            {
                if (id == nullId)
                {
                    return client.GetAsync(serverAddr + service).Result.Content.ReadAsStringAsync().Result;
                }
                return client.GetAsync(serverAddr + service + "/" + id).Result.Content.ReadAsStringAsync().Result;
            }
        }

        [HttpDelete("{service}/{id}")]
        public string Delete(string service, int id)
        {
            using (var client = new HttpClient())
            {
                return client.DeleteAsync(serverAddr + service + "/" + id).Result.StatusCode.ToString();
            }
        }

        [HttpPost("workers")]
        public HttpResponseMessage CreateWorker(Worker worker)
        {
            using (var client = new HttpClient())
            {
                var toSend = new StringContent(JsonConvert.SerializeObject(worker), Encoding.UTF8, "application/json");
                return client.PostAsync(serverAddr + "workers", toSend).Result;
            }
        }

        [HttpPost("scripts")]
        public HttpResponseMessage CreateScript(Script script)
        {
            using (var client = new HttpClient())
            {
                var toSend = new StringContent(JsonConvert.SerializeObject(script), Encoding.UTF8, "application/json");
                return client.PostAsync(serverAddr + "scripts", toSend).Result;
            }
        }
    }
}
