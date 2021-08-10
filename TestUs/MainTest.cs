using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;

namespace TestUs
{
    [TestClass]
    public class MainTest
    {
        [TestMethod]
        public void TestMethod()
        {
            var mock = new Mock<Script>();
            Assert.AreEqual(1+1, 2);
        }
    }
}
