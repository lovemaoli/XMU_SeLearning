using Microsoft.EntityFrameworkCore;
using Xmu.Stores.Models;

namespace UserStores.Services
{
    public class UserStoreDb : IUserStore
    {
        private IServiceProvider provider;
        public UserStoreDb(IServiceProvider sP, UserRepository repo)
        {
            provider = sP;
            AllUsers = repo.Users;
        }

        public DbSet<User> AllUsers { get; set; }

        public (bool success, string msg, IUserPrincipal? user) AddUser(string name, string pwd)
        {
            User u = new User()
            {
                 UserName = name,
                 Password = pwd,                  
            };
            using var scope = provider.CreateScope();
            var repo = scope.ServiceProvider.GetRequiredService<UserRepository>();
            repo.Users.Add(u);
            repo.DbContext.SaveChanges();

            return (true, "", u);
        }

        public User? GetUser(string userName)
        {
            using var scope = provider.CreateScope();
            var repo = scope.ServiceProvider.GetRequiredService<UserRepository>();
            var query = from u in repo.Users
                        where u.UserName == userName
                        select u;
            return query.FirstOrDefault();
        }

        // 下面的函数与上面的函数等效
        //public User? GetUser(string userName)
        //{
        //    using var scope = provider.CreateScope();
        //    var repo = scope.ServiceProvider.GetRequiredService<UserRepository>();
        //    return repo.Users.FirstOrDefault(e => e.UserName == userName);
        //}

        public IUserPrincipal? GetUser(string userName, string pwd)
        {
            throw new NotImplementedException();
        }
    }
}
