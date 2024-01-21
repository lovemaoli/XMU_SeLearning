using NetCourse.Framework;
using NetCourse.Framework.ModuleInitializer;
using System.Reflection;

namespace Microsoft.Extensions.DependencyInjection
{
    public static class DependencyExtension
    {
        public static void LoadAssembly(this IServiceCollection collection, string assemblyName)
        {
            Assembly.Load(assemblyName);
        }

        public static HostEnv ScanAllDependency(this IServiceCollection collection)
        {
            HostEnv env = new HostEnv();
            collection.AddSingleton(env);

            ModuleInitializer initializer = new ModuleInitializer(collection, env);
            initializer.InitializeAssembly();

            return env;
        }
    }
}
