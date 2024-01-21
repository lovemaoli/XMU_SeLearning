using Microsoft.EntityFrameworkCore;
using NetCourse.Framework.Database;

namespace Xmu.Stores.Models
{
    public class UserRepository : IScopedDependency
    {
        public UserRepository(NetContext dbContext)
        {
            DbContext = dbContext;
        }

        public NetContext DbContext { get; set; }

        public DbSet<User> Users => DbContext.Set<User>();
    }
}
