using System.Text.Json;
using Xmu.Stores.Models;

namespace Xmu.Stores.Services
{
    public class UserStore
    {
        private const string path = "./users.txt";
        public List<User> AllUsers { get; set; } = new List<User>();

        public UserStore()
        {
            LoadUsers();
        }

        public void LoadUsers()
        {
            try
            {
                string json = File.ReadAllText(path);
                AllUsers = JsonSerializer.Deserialize<List<User>>(json) ?? new List<User>();
            }
            catch
            {

            }
        }

        public List<IUserPrincipal> GetUsers(int page, int pageSize, out int totalRows)
        {
            totalRows = AllUsers.Count;
            return AllUsers.Skip((page - 1) * pageSize).Take(pageSize).Select(e => e as IUserPrincipal).ToList();
        }

        /// <summary>
        /// 添加用户
        /// </summary>
        /// <param name="name">用户名</param>
        /// <param name="pwd">密码</param>
        /// <returns>是否成功，失败的消息，添加成功返回用户对象</returns>
        public (bool success, string msg, IUserPrincipal? user) AddUser(string name, string pwd)
        {
            if (AllUsers.Any(e => e.UserName == name))
            {
                return (false, $"已经存在用户名为{name}的用户", null);
            }

            if (string.IsNullOrEmpty(name))
            {
                return (false, "必须输入用户名", null);
            }

            var user = new User
            {
                ID = Guid.NewGuid(),
                UserName = name,
                Password = pwd,
            };

            AllUsers.Add(user);
            SaveToFile();

            return (true, string.Empty, user);
        }

        /// <summary>
        /// 获取用户
        /// </summary>
        /// <param name="userName">用户名</param>
        /// <param name="pwd">密码</param>
        /// <returns>找到用户返回对象，否则返回null</returns>
        public IUserPrincipal? GetUser(string userName, string pwd) => AllUsers.FirstOrDefault(e => e.UserName == userName && e.Password == pwd);

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="userName">用户名</param>
        /// <returns>删除成功则返回被删除的用户</returns>
        public IUserPrincipal? RemoveUser(string userName)
        {
            var user = AllUsers.FirstOrDefault(e => e.UserName == userName);
            if (user == null)
            {
                return null;
            }

            AllUsers.Remove(user);
            SaveToFile();
            return user;
        }

        private void SaveToFile()
        {
            string json = JsonSerializer.Serialize(AllUsers);
            File.WriteAllText(path, json);
        }
    }
}
