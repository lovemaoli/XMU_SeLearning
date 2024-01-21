using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using NetCourse.Framework.Security;
using Ricebird.Authentication.Services;

namespace XmuAuthen.Controllers
{
    [Route("~/api/auth/{action}")]
    public class AuthenController : Controller
    {
        private readonly RicebirdAuthenticationService authService;
        public AuthenController(RicebirdAuthenticationService authenticationService)
        {
            authService = authenticationService;
        }

        public record LoginForm(string loginToken, string password);
        // 演示地址：/api/login?loginToken=test&password=pwd
        [Route("~/api/login")]
        public ActionResult Login(LoginForm form)
        {
            var (success, msg, token) = authService.GetCredential(form.loginToken, form.password);

            return Ok(new
            {
                success,
                msg,
                token
            });
        }

        // http://localhost:5286/api/auth/ValidateLoginState?accessToken=
        public ActionResult ValidateLoginState()
        {
            //string accessToken = Request.Query[nameof(accessToken)].ToString() ?? "";
            //IUserPrincipal currentUser = authService.GetUserPrincipal(accessToken);
            IUserPrincipal currentUser = HttpContext.Features.Get<IUserPrincipal>()!;
            if (currentUser.ID == Guid.Empty)
            {
                return Ok(new
                {
                    success = false,
                    msg = "登录凭证已经失效，需要重新登录。"
                });
            }
            else
            {
                return Ok(new
                {
                    success = true,
                    msg = "登录凭证生效中，已自动登录。",
                    currentUser,
                });
            }
        }

        //public override void OnActionExecuting(ActionExecutingContext context)
        //{
        //    string accessToken = context.HttpContext.Request.Query[nameof(accessToken)].ToString() ?? "";
        //    IUserPrincipal currentUser = authService.GetUserPrincipal(accessToken);
        //    HttpContext.Features.Set<IUserPrincipal>(currentUser);
        //}
    }
}
