using Microsoft.EntityFrameworkCore;
using NetCourse.Framework.Database;

namespace Microsoft.Extensions.DependencyInjection
{
    public static class IServiceCollectionExtensions
    {
        public static void AddSqliteDatabase(this IServiceCollection collection, string dbPath, string migrationAssemblyName)
        {
            collection.AddDbContext<NetContext>(opt =>
            {
                opt.UseSqlite($"Data Source={dbPath}", b =>
                {
                    b.MigrationsAssembly(migrationAssemblyName);
                });
            });
        }
    }
}
