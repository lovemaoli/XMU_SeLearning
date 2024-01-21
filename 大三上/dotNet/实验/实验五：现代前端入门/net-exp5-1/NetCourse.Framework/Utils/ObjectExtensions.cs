using System.Dynamic;
using System.Reflection;

namespace Ricebird.Framework
{
    public static class ObjectExtensions
    {
        public static Dictionary<string, object> ObjectToDictionary(this object obj)
        {
            if (obj is ExpandoObject || obj is Dictionary<string, object>)
            {
                return (Dictionary<string, object>)obj;
            }

            Dictionary<string, object> dic = new Dictionary<string, object>();
            foreach (var propInfo in obj.GetType().GetProperties())
            {
                if (!dic.ContainsKey(propInfo.Name))
                {
                    try
                    {
                        object? value = propInfo.GetValue(obj);
                        if (value == null) continue;
                        dic[propInfo.Name] = value;
                    }
                    catch
                    {
                        continue;
                    }

                }
            }

            return dic;
        }

        private static PropertyInfo? ContainName(this Object obj, string name)
        {
            foreach (var prop in obj.GetType().GetProperties())
            {
                if (prop.Name == name)
                    return prop;
            }
            return null;
        }



        public static T? CreateInstance<T>(this Type t)
            where T : class
        {
            var finalType = typeof(T);
            if (finalType.IsAssignableFrom(t))
            {
                T? result = Activator.CreateInstance(t) as T;
                return result;
            }

            return null;
        }

        public static bool HasProperty(this object obj, string propertyName)
        {
            Type type = obj.GetType();
            PropertyInfo? property = type.GetProperty(propertyName);
            return property != null;
        }

        public static object? GetPropertyValue(this object obj, string propertyName)
        {
            Type type = obj.GetType();
            PropertyInfo? property = type.GetProperty(propertyName);
            if (property == null)
            {
                throw new ArgumentException(string.Format("找不到属性'{0}'.", propertyName), propertyName);
            }
            object? value = property.GetValue(obj, null);
            return value;
        }

        public static T? GetPropertyValue<T>(this object obj, string propertyName)
        {
            return obj.GetPropertyValue(propertyName, default(T));
        }

        public static T GetPropertyValue<T>(this object obj, string propertyName, T defaultValue)
        {
            Type type = obj.GetType();
            PropertyInfo? property = type.GetProperty(propertyName);
            if (property == null)
            {
                return defaultValue;
                // throw new ArgumentException(string.Format("Property '{0}' not found.", propertyName), propertyName);
            }
            object? value = property.GetValue(obj, null);
            return (value is T t) ? t : defaultValue;
        }

        public static void SetPropertyValue(this object obj, string propertyName, object value)
        {
            Type type = obj.GetType();
            PropertyInfo? property = type.GetProperty(propertyName);
            if (property == null)
            {
                throw new ArgumentException(string.Format("找不到属性'{0}'", propertyName), propertyName);
            }
            if (!property.CanWrite)
            {
                throw new ArgumentException(string.Format("属性 '{0}' 不可写.", propertyName), propertyName);
            }
            property.SetValue(obj, value, null);
        }

        public static T? GetAttribute<T>(this object obj) where T : Attribute
        {
            return obj.GetAttribute<T>(true);
        }

        public static T? GetAttribute<T>(this object obj, bool includeInherited) where T : Attribute
        {
            Type type = (obj as Type) ?? obj.GetType();
            object[] customAttributes = type.GetCustomAttributes(typeof(T), includeInherited);
            T? result;
            if (customAttributes.Length > 0)
            {
                result = (customAttributes[0] as T);
            }
            else
            {
                result = default(T);
            }
            return result;
        }
    }
}
