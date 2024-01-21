
namespace NetCourse.Framework.Security
{
    public interface IUserStore : IScopedDependency
    {
        IUserPrincipal? GetUser(string userName, string pwd);
        (bool success, string msg, IUserPrincipal? user) AddUser(string name, string pwd);
    }
}
