
using NetCourse.Framework.Database;

namespace Xmu.Stores.Models
{
    public class User : EntityBase, IUserPrincipal
    {
        #region 字段
        public string UserName { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;

        public string Avatar { get; set; } = string.Empty;
        #endregion
    }
}
