
using NetCourse.Framework.Security;
using Ricebird.Authentication.Services;

namespace Ricebird.Authentication.Midwares
{
    public class AuthenticationMidware
    {
        protected readonly RequestDelegate _next;

        public AuthenticationMidware(RequestDelegate next)
        {
            _next = next;
        }


        public async Task Invoke(HttpContext context)
        {
            RicebirdAuthenticationService authService = context.RequestServices.GetRequiredService<RicebirdAuthenticationService>();

            string accessToken = context.Request.Headers[nameof(accessToken)].ToString() ?? "";
            IUserPrincipal currentUser = authService.GetUserPrincipal(accessToken);
            context.Features.Set<IUserPrincipal>(currentUser);

            await _next(context);
        }
    }
}
