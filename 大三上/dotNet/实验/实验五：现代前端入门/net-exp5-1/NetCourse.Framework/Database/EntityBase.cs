using Microsoft.EntityFrameworkCore;

namespace NetCourse.Framework.Database
{
    public class EntityBase : IDependency
    {
        public Guid ID { get; set; } = Guid.NewGuid();

        public virtual void OnModelCreating(ModelBuilder builder)
        {

        }
    }
}
