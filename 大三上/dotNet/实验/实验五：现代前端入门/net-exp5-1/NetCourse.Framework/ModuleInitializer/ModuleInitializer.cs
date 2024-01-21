using NetCourse.Framework.Database;
using System.Reflection;

namespace NetCourse.Framework.ModuleInitializer
{
    internal class ModuleInitializer
    {
        private IServiceCollection Collection
        {
            get; set;
        }

        private HostEnv HostEnv { get; init; }

        internal ModuleInitializer(IServiceCollection collection, HostEnv env)
        {
            Collection = collection;
            HostEnv = env;
        }

        /// <summary>
        /// 初始化程序集
        /// </summary>
        internal void InitializeAssembly()
        {
            List<Type> registerTypes = new List<Type>();
            foreach (var assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                registerTypes.AddRange(assembly.DefinedTypes.Select(e => e.AsType()));
            }

            // 开始初始化程序集
            List<Type> singleton = new List<Type>();
            List<Type> transient = new List<Type>();
            List<Type> scoped = new List<Type>();
            // 扫描一次所有程序集，直接分类
            int i = 0;
            foreach (var type in registerTypes)
            {
                if (typeof(IDependency).IsAssignableFrom(type))
                {
                    if (typeof(EntityBase).IsAssignableFrom(type) && type.IsClass && !type.IsAbstract)
                    {
                        HostEnv.AllEntities.Add(type);
                    }

                    transient.Add(type);
                }
                else if (typeof(ISingletonDependency).IsAssignableFrom(type))
                {
                    singleton.Add(type);
                }
                else if (typeof(IScopedDependency).IsAssignableFrom(type))
                {
                    scoped.Add(type);
                }
                i++;
            }
            // 程序集扫描完毕后，开始注册
            RegisterType(transient, Collection.AddTransient);
            RegisterType(scoped, Collection.AddScoped);
            RegisterType(singleton, Collection.AddSingleton);
        }

        internal static void RegisterType(List<Type> types, Func<Type, Type, IServiceCollection> registerAction)
        {
            foreach (var t in types)
            {
                if (t.IsClass && !t.IsAbstract && !t.IsGenericType)
                {
                    registerAction(t, t);
                    // 类型必须是可以实例化的，则开始将它注册到它的所有母类上
                    for (Type? baseType = t.BaseType; baseType != typeof(object); baseType = baseType.BaseType)
                    {
                        if (baseType == null)
                        {
                            break;
                        }

                        registerAction(baseType, t);
                    }

                    var interfaces = t.GetInterfaces();
                    foreach (var inter in interfaces)
                    {
                        registerAction(inter, t);
                    }
                }
            }
        } // RegisterType
    } // class
} // namespace
