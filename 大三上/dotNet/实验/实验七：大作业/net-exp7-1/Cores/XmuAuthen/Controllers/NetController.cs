using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using NetCourse.Framework.Security;
using Ricebird.Authentication.Services;

namespace XmuAuthen.Controllers
{
    public abstract class NetController : Controller
    {
        public override void OnActionExecuting(ActionExecutingContext context)
        {
            RicebirdAuthenticationService authService = context.HttpContext.RequestServices.GetRequiredService<RicebirdAuthenticationService>();
            string accessToken = context.HttpContext.Request.Query[nameof(accessToken)].ToString() ?? "";
            IUserPrincipal currentUser = authService.GetUserPrincipal(accessToken);
            HttpContext.Features.Set<IUserPrincipal>(currentUser);
        }

        protected IUserPrincipal? CurrentUser => HttpContext.Features.Get<IUserPrincipal>();
    }
}
