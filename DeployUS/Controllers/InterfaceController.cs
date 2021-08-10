
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using System;
using System.Net;
using System.Net.Http;
using System.Text;

namespace DeployUS.Controllers
{
    [Route("api")]
    [ApiController]
    public class InterfaceController : ControllerBase
    {
        const int nullId = -1;
        string serverAddr = Environment.GetEnvironmentVariable("CONNECTIONDB_ADDR");

        [HttpGet("{service}")]
        [HttpGet("{service}/{id}")]
        public Object Get(string service, int id = nullId)
        {
            using (var client = new HttpClient())
            {
                
                try
                {
                    if (id == nullId)
                    {
                        return client.GetAsync(serverAddr + service).Result.Content.ReadAsStringAsync().Result;
                    }
                    return client.GetAsync(serverAddr + service + "/" + id).Result.Content.ReadAsStringAsync().Result;
                }
                catch(AggregateException)
                {
                    return null;
                }
            }
        }

        [HttpDelete("{service}/{id}")]
        public HttpResponseMessage Delete(string service, int id)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return client.DeleteAsync(serverAddr + service + "/" + id).Result;
                }
                catch(AggregateException)
                {
                    return new HttpResponseMessage(HttpStatusCode.BadGateway);
                }
            }
        }

        [HttpPost("workers")]
        public HttpResponseMessage CreateWorker(Worker worker)
        {
            System.Console.WriteLine(worker.address);
            if(isIpValid(worker.address))
            {
                using (var client = new HttpClient())
                {
                    try
                    {
                        var toSend = new StringContent(JsonConvert.SerializeObject(worker), Encoding.UTF8, "application/json");
                        return client.PostAsync(serverAddr + "workers", toSend).Result;
                    }
                    catch(AggregateException)
                    {
                        return new HttpResponseMessage(HttpStatusCode.BadGateway);
                    }
                }
            }
            return new HttpResponseMessage(HttpStatusCode.BadRequest); ;
        }

        [HttpPost("scripts")]
        public HttpResponseMessage CreateScript(Script script)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    var toSend = new StringContent(JsonConvert.SerializeObject(script), Encoding.UTF8, "application/json");
                    return client.PostAsync(serverAddr + "scripts", toSend).Result;
                }
                catch(AggregateException)
                {
                    return new HttpResponseMessage(HttpStatusCode.BadGateway);
                }
            }
        }

        private bool isIpValid(string ip)
        {
            if(ip=="localhost")
            {
                return true;
            }
            var ipArray=ip.Split(".");
            if(ipArray.Length==4)
            {
                foreach(string val in ipArray)
                {
                    try
                    {
                        int result=Int32.Parse(val);
                        if(result < 0 || result > 255)
                        {
                            return false;
                        }
                    }
                    catch (FormatException)
                    { 
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
    }
}
