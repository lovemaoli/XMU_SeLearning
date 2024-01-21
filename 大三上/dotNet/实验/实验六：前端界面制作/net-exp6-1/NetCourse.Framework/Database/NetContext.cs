using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Microsoft.Extensions.Logging;
using System.ComponentModel.DataAnnotations.Schema;
using System.Reflection;

namespace NetCourse.Framework.Database
{
    public class NetContext : DbContext, IDependency
    {
        public NetContext(DbContextOptions<NetContext> options, IServiceProvider sP, HostEnv hostEnv) : base(options)
        {
            ServiceProvider = sP;
            HostEnv = hostEnv;
        }

        protected IServiceProvider ServiceProvider { get; set; }

        protected HostEnv HostEnv
        {
            get; set;
        }

        #region 注册函数
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            var entityTypes = HostEnv.AllEntities;

            RegisterEntities(modelBuilder, entityTypes);
            RegisterConvention(modelBuilder);

            foreach (var relationship in modelBuilder.Model.GetEntityTypes().SelectMany(e => e.GetForeignKeys()))
            {
                relationship.DeleteBehavior = DeleteBehavior.Cascade;
            }

            foreach (var type in entityTypes)
            {
                EntityBase? rep = type.CreateInstance<EntityBase>();
                if (rep != null)
                {
                    rep.OnModelCreating(modelBuilder);
                }
            }

            base.OnModelCreating(modelBuilder);
        }

        private readonly HashSet<string> existsName = new HashSet<string>();
        private void RegisterConvention(ModelBuilder modelBuilder)
        {
            foreach (var entity in modelBuilder.Model.GetEntityTypes())
            {
                var tableAttr = entity.GetType().GetCustomAttribute<TableAttribute>();
                string tableName = tableAttr == null ? entity.ClrType.Name : tableAttr.Name;
                if (existsName.Contains(tableName))
                {
                    throw new InvalidOperationException($"不能添加两个名称相同的表：{tableName}");
                }

                modelBuilder.Entity(entity.Name).ToTable(tableName);
            }
        }

        private void RegisterEntities(ModelBuilder modelBuilder, IEnumerable<Type> entityTypes)
        {
            List<Type> hasForeignKey = new List<Type>();
            foreach (var type in entityTypes)
            {
                try
                {
                    modelBuilder
                        .Entity(type);
                }
                catch
                {
                    hasForeignKey.Add(type);
                }
            }

            foreach (var type in hasForeignKey)
            {
                modelBuilder.Entity(type);
            }
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            base.OnConfiguring(optionsBuilder);
        }
        #endregion
    }
}
