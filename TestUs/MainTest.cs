using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;
using System;
using Moq;
using DeployUS.Controllers;
using Newtonsoft.Json;
using System.Net.Http;

namespace TestUs
{
    [TestClass]
    public class MainTest
    {
        Worker validWorker=new Worker("validWorker","178.128.238.88");
        Worker invalidWorker1=new Worker("invalidWorker","10.44.44.450");
        Worker invalidWorker2=new Worker("invalidWorker","ipaddr");

        Script validScript=new Script("validScript","version: '3'\nservices: \n  page:\n    image: httpd\n    ports:\n      - 4242:80");
        Script invalidScript=new Script("invalidScript","invalid yaml");

        int nonexistentId=99999;

        private string getConnectionDbAddr()
        {
            string env=Environment.GetEnvironmentVariable("CONNECTIONDB_ADDR");
            if(String.IsNullOrEmpty(env)) 
            {
                return "http://68.183.192.81:5000/";
            }
            return env;
        }

        [TestMethod]
        public void addWorkers()
        {
            var mock = new Mock<InterfaceController>();
            mock.Object.serverAddr=getConnectionDbAddr();

            Assert.IsTrue(mock.Object.CreateWorker(validWorker).ToString().Contains("StatusCode: 201"));
            Assert.IsTrue(mock.Object.CreateWorker(invalidWorker1).ToString().Contains("StatusCode: 400"));
            Assert.IsTrue(mock.Object.CreateWorker(invalidWorker2).ToString().Contains("StatusCode: 400"));

            Worker[] workers= JsonConvert.DeserializeObject<Worker[]>(mock.Object.Get("workers").ToString());

            Assert.IsTrue(Array.Exists(workers, worker=> worker.name==validWorker.name && worker.address==validWorker.address));
            Assert.IsFalse(Array.Exists(workers, worker=> worker.name==invalidWorker1.name && worker.address==invalidWorker1.address));
            Assert.IsFalse(Array.Exists(workers, worker=> worker.name==invalidWorker2.name && worker.address==invalidWorker2.address));
        }


        /*For DeployUs we also add invalid scripts to the database since it's was harder to do a check on that level, and I left it for 
        WorkUs to determine wether or not the script is valid and either execute or return an error with diffrent exit codes*/
        [TestMethod]
        public void addScripts()
        {
            var mock = new Mock<InterfaceController>();
            mock.Object.serverAddr=getConnectionDbAddr();

            Assert.IsTrue(mock.Object.CreateScript(validScript).ToString().Contains("StatusCode: 201"));
            Assert.IsTrue(mock.Object.CreateScript(invalidScript).ToString().Contains("StatusCode: 201"));

            Script[] scripts= JsonConvert.DeserializeObject<Script[]>(mock.Object.Get("scripts").ToString());

            Assert.IsTrue(Array.Exists(scripts, script=> script.name==validScript.name && script.script==validScript.script));
            Assert.IsTrue(Array.Exists(scripts, script=> script.name==invalidScript.name && script.script==invalidScript.script));
        }

        [TestMethod]
        public void testUnexistentWorker()
        {
            var mock = new Mock<InterfaceController>();
            mock.Object.serverAddr=getConnectionDbAddr();
            var httpResponse=mock.Object.Get("workers",nonexistentId);

            Assert.IsTrue(httpResponse.ToString().Contains("\"status\":404"));
        }
        [TestMethod]
        public void testUnexistentScript()
        {
            var mock = new Mock<InterfaceController>();
            mock.Object.serverAddr=getConnectionDbAddr();
            var httpResponse=mock.Object.Get("scripts",nonexistentId);

            Assert.IsTrue(httpResponse.ToString().Contains("\"status\":404"));
    
        }
        [TestMethod]
        public void runValidScriptValidWorker()
        {
            var mock = new Mock<ExecController>();
            Runner valid=new Runner(validWorker,validScript);
            Assert.IsTrue(mock.Object.Run(valid).ToString().Contains("\"ExitCode\":\"0\""));
            
        }
        [TestMethod]
        public void runInvalidScriptValidWorker()
        {
            var mock = new Mock<ExecController>();
            Runner invalid=new Runner(validWorker,invalidScript);
            Assert.IsTrue(mock.Object.Run(invalid).ToString().Contains("\"ExitCode\":\"1\""));
        }
        [TestMethod]
        public void runValidScriptInvalidWorker()
        {
            var mock = new Mock<ExecController>();
            Runner invalid=new Runner(invalidWorker1,validScript);
            Assert.IsTrue(mock.Object.Run(invalid).ToString().Contains("StatusCode: 502"));
        }
        [TestMethod]
        public void runInvalidScriptInvalidWorker()
        {
            var mock = new Mock<ExecController>();
            Runner invalid=new Runner(invalidWorker1,invalidScript);
            Assert.IsTrue(mock.Object.Run(invalid).ToString().Contains("StatusCode: 502"));
        }
    }
}