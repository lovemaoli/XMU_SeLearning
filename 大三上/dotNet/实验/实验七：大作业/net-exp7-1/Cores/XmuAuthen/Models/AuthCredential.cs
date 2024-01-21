using NetCourse.Framework.Security;

namespace Ricebird.Authentication.Models
{
    internal class AuthCredential
    {
        internal AuthCredential(IUserPrincipal user, TimeSpan expiredIn)
        {
            UserIdentity = user;
            ExpiredIn = expiredIn;
        }

        public IUserPrincipal UserIdentity { get; set; }

        public string Credential { get; set; } = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".GenerateKey(8);

        public TimeSpan ExpiredIn { get; set; }

        internal DateTime LastAccess { get; set; } = DateTime.Now;

        internal bool CheckExpired(DateTime now)
        {
            return (now - LastAccess) >= ExpiredIn;
        }
    }
}
