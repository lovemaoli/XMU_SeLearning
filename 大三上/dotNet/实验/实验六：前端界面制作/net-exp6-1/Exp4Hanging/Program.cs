using Ricebird.Authentication.Midwares;

var builder = WebApplication.CreateBuilder(args);

builder.Services.LoadAssembly("UserStores"); // 必加，建议所有新的项目都在这里加一遍
builder.Services.LoadAssembly("XmuAuthen"); // 必加，建议所有新的项目都在这里加一遍
builder.Services.ScanAllDependency(); // 必加
builder.Services.AddMvc();
builder.Services.AddSqliteDatabase(@".\myDb.db", "UserAuthen"); //这里的UserAuthen是默认项目的名字，根据实际情况修改

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
}
app.UseStaticFiles();

app.UseMiddleware<AuthenticationMidware>();
app.UseRouting();
app.MapControllers();

app.Run();
