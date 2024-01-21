using Xmu.Stores.Services;

namespace NetCourse.UnitTest
{
    [TestClass]
    public class UserStoreTest
    {
        [TestMethod("ÃÌº””√ªß≤‚ ‘")]
        public void AddUserTest1()
        {
            UserStore store = new UserStore();

            var (success, msg, u) = store.AddUser("test", "test");

            string excepted = "";

            Assert.AreEqual(excepted, msg);
        }
    }
}