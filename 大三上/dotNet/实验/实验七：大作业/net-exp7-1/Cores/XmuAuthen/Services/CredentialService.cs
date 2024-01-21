
using NetCourse.Framework.Security;
using Ricebird.Authentication.Models;

namespace Ricebird.Authentication.Services
{
    internal class CredentialService
    {
        internal CredentialService(TimeSpan frequency)
        {
            this.frequency = frequency;
        }

        private readonly TimeSpan frequency;
        private readonly Dictionary<string, AuthCredential> tokenStores = new Dictionary<string, AuthCredential>();
        private Dictionary<Guid, int> tokenCountByUserId = new Dictionary<Guid, int>();
        private readonly object locker = new object();
        private DateTime lastExpirationScan = DateTime.Now;

        private void ScanExpiredTokenIfNeed()
        {
            DateTime now = DateTime.Now;
            if (now - lastExpirationScan >= frequency)
            {
                lastExpirationScan = now;
                Task.Run(() =>
                {
                    lock (locker)
                    {
                        List<string> tokenNeedRemove = new List<string>();
                        Dictionary<Guid, int> countByUserId = new Dictionary<Guid, int>();
                        foreach (var entry in tokenStores)
                        {
                            var token = entry.Value;
                            if (token.CheckExpired(now))
                            {
                                tokenNeedRemove.Add(entry.Key);
                            }
                            else
                            {
                                if (countByUserId.TryGetValue(token.UserIdentity.ID, out int v))
                                {
                                    v++;
                                }
                                else
                                {
                                    countByUserId.Add(token.UserIdentity.ID, 1);
                                }
                            }
                        } // foreach

                        foreach (var item in tokenNeedRemove)
                        {
                            tokenStores.Remove(item);
                        }

                        tokenCountByUserId = countByUserId;
                    }
                });
            } // if
        } // void ScanExpiredTokenIfNeed()

        #region 操作函数
        public int TotalToken => tokenStores.Count;
        public int TotalUser => tokenCountByUserId.Count;
        public object GetJson()
        {
            return (new
            {
                success = true,
                msg = "",
                TotalToken,
                TotalUser,
                tokenStores,
                tokenCountByUserId
            });
        }

        public (bool success, string msg, string credential) AddUser(IUserPrincipal user)
        {

            if (user.ID == Guid.Empty)
            {
                throw new ArgumentException($"不可以加入空用户");
            }

            AuthCredential authCredential = new AuthCredential(user, TimeSpan.FromMinutes(30));
            AddOrUpdateToken(authCredential);

            return (true, "", authCredential.Credential);
        }

        public IUserPrincipal? GetUser(string token)
        {
            IUserPrincipal? user = null;
            lock (locker)
            {
                if (tokenStores.TryGetValue(token, out var authCredential) && !authCredential.CheckExpired(DateTime.Now))
                {
                    authCredential.LastAccess = DateTime.Now;
                    user = authCredential.UserIdentity;
                }
            }

            ScanExpiredTokenIfNeed();
            return user;
        }

        public void RemoveCredential(string token)
        {
            lock (locker)
            {
                if (tokenStores.TryGetValue(token, out var authCredential))
                {
                    tokenCountByUserId[authCredential.UserIdentity.ID]--;
                    if (tokenCountByUserId[authCredential.UserIdentity.ID] <= 0)
                    {
                        tokenCountByUserId.Remove(authCredential.UserIdentity.ID);
                    }

                    tokenStores.Remove(token);
                }
            }

            ScanExpiredTokenIfNeed();
        }

        private void AddOrUpdateToken(AuthCredential token)
        {
            lock (locker)
            {
                tokenStores.MergeKey(token.Credential, token);
                Guid userId = token.UserIdentity.ID;
                if (!tokenCountByUserId.TryAdd(userId, 1))
                {
                    tokenCountByUserId[userId]++;
                }
            }

            ScanExpiredTokenIfNeed();
        }

        public int CountTokensByUser(Guid userId)
        {
            if (tokenCountByUserId.TryGetValue(userId, out int value))
            {
                return value;
            }

            return 0;
        }
        #endregion
    }
}
