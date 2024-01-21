using System.Text;

namespace System
{
    public static class UtilExtensions
    {
        private static readonly Random r = new(DateTime.Now.Millisecond);
        public static string GenerateKey(this string sourceArray, int keyLength)
        {
            StringBuilder result = new();
            int aryLength = sourceArray.Length;
            for (int i = 0; i < keyLength; i++)
            {
                result.Append(sourceArray[r.Next(aryLength)]);
            }

            return result.ToString();
        }

        public static IDictionary<TKey, TValue> MergeKey<TKey, TValue>(this IDictionary<TKey, TValue> dic, TKey key, TValue? value)
            where TKey : notnull
        {
            if (value == null)
            {
                return dic;
            }

            if (dic.ContainsKey(key))
            {
                dic[key] = value;
            }
            else
            {
                dic.Add(key, value);
            }

            return dic;
        }
    }
}
