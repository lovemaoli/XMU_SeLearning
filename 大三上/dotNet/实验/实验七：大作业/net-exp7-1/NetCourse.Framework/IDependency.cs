global using Microsoft.Extensions.DependencyInjection;
global using Ricebird.Framework;

namespace NetCourse.Framework
{
    public interface IDependency // 每次GetRequiredService时，都生成一个新的
    {
    }

    public interface IScopedDependency // 每个Scope.GetRequiredService时，都生成一个新的
    {

    }

    public interface ISingletonDependency // 单例，全程序只有一个
    {

    }
}