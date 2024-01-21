using NetCourse.Framework;
using NetCourse.Framework.Security;
using XmuAuthen.Services;

namespace Ricebird.Authentication.Services
{
    public class RicebirdAuthenticationService : ISingletonDependency
    {
        private readonly CredentialServiceByMemoryCache credentialService;
        private readonly IServiceProvider serviceProvider;

        public RicebirdAuthenticationService(IServiceProvider provider)
        {
            credentialService = new CredentialServiceByMemoryCache(TimeSpan.FromMinutes(1));
            AnonymousIdentity = new AnonymousUser();
            serviceProvider = provider;
        }

        public IUserPrincipal AnonymousIdentity
        {
            get;
            init;
        }

        public (bool success, string msg, string credential) GetCredential(string token, string password)
        {
            if (string.IsNullOrEmpty(password))
            {
                return (false, "必须输入密码", "");
            }
            IUserStore repo = serviceProvider.GetRequiredService<IUserStore>();
            IUserPrincipal? user = repo.GetUser(token, password);
            
            if (user == null)
            {
                return (false, "用户名或密码错误", "");
            }
            if (user is not null) // --
            {
                return GetCredential(user);
            }

            return (false, "用户名密码错误", "");
        }

        public (bool success, string msg, string credential) GetCredential(IUserPrincipal user)
        {
            var result = credentialService.AddUser(user);
            return result;
        }

        public IUserPrincipal GetUserPrincipal(string credential)
        {
            var user = credentialService.GetUser(credential);
            return user ?? AnonymousIdentity;
        }

        public void Logout(string credential)
        {
            credentialService.RemoveCredential(credential);
        }

        #region 内部类
        private class AnonymousUser : IUserPrincipal
        {
            public Guid ID
            {
                get; set;
            }
            public string UserName
            {
                get; set;
            } = string.Empty;
            public string Password
            {
                get; set;
            } = string.Empty;
        }
        #endregion
    }
}
