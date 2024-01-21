using Microsoft.Extensions.Caching.Memory;
using NetCourse.Framework.Security;
using Ricebird.Authentication.Models;

namespace XmuAuthen.Services
{
    public class CredentialServiceByMemoryCache
    {
        internal CredentialServiceByMemoryCache(TimeSpan fre)
        {
            tokenStores = new MemoryCache(new MemoryCacheOptions());
        }

        private readonly MemoryCache tokenStores;


        #region 操作函数
        public (bool success, string msg, string credential) AddUser(IUserPrincipal user)
        {

            if (user.ID == Guid.Empty)
            {
                throw new ArgumentException($"不可以加入空用户");
            }

            AuthCredential authCredential = new AuthCredential(user, TimeSpan.FromMinutes(30));
            tokenStores.Set(authCredential.Credential, authCredential, TimeSpan.FromMinutes(30));

            return (true, "", authCredential.Credential);
        }

        public IUserPrincipal? GetUser(string token)
        {
            IUserPrincipal? user = (tokenStores.Get(token) as AuthCredential)?.UserIdentity;
            return user;
        }

        public void RemoveCredential(string token)
        {
            tokenStores.Remove(token);
        }
        #endregion
    }
}
