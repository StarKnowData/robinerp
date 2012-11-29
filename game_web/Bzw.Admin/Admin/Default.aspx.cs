using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Utility;
using BCST.Common;
using BCST.Cache;
using Bzw.Data;
using UiCommon;

public partial class Admin_Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void AddAdminLogin(object sender, EventArgs e)
    {
		if( !CommonManager.Web.CheckPostSource() )
			return;
		if( !IsValid )
			return;
       
		if( string.IsNullOrEmpty( txtUserName.Text.Trim() ) )
		{
			CommonManager.Web.RegJs(this,"alert('请输入用户名！');",false);
			return;
		}
		if( string.IsNullOrEmpty( txtPassword.Text.Trim() ) )
		{
			CommonManager.Web.RegJs( this, "alert('请输入密码！');", false );
			return;
		}
		if( string.IsNullOrEmpty( txtCode.Text.Trim() ) )
		{
			CommonManager.Web.RegJs( this, "alert('请输入验证码！');", false );
			return;
		}
		if( txtCode.Text.Trim().ToLower() != UiCommon.ValidCode.CurrentCode )
		{
			CommonManager.Web.RegJs( this, "alert('验证码输入错误！');", false );
			return;
		}
		BCSTCache.Default.Delete<SessionCache>( UiCommon.ValidCode.KeyName );

		DataTable dt = DbSession.Default.FromSql( "select * from web_manage_admin where UserName=@UserName and Password=@Password" )
						.AddInputParameter( "@UserName", DbType.String, txtUserName.Text.Trim() )
						.AddInputParameter( "@Password", DbType.String, CommonManager.String.EncryptMD5SystemDefaultMethod( txtPassword.Text.Trim(), true, true ) )
						.ToDataTable();

		if( dt.Rows.Count != 1 )
		{
			string descript = "登录失败！登录名：" + txtUserName.Text.Trim() + "，登录密码：" + txtPassword.Text.Trim();
			new BLL.Member().InsertAdminModifyLog( txtUserName.Text.Trim(), Common.RequestIP, Common.GetOS, descript, 0 );
			CommonManager.Web.RegJs( this, "alert('用户名或密码错误！');", false );
			return;
		}
        
		BCSTCache.Default.Save<SessionCache>( StringConfig.AdminCacheName, dt.Rows[0],30 );
		BCSTCache.Default.Save<CookiesCache>( StringConfig.AdminCacheName, dt.Rows[0]["ID"].ToString(), 30 );
         
		string descript2 = "登录成功，进入管理页面！";
		new BLL.Member().InsertAdminModifyLog( txtUserName.Text.Trim(), Common.RequestIP, Common.GetOS, descript2, 1 );
       
		CommonManager.Web.ResponseEnd("AdminIn.aspx",true);
        
		#region old code
		//this.AdminNames = Limit.editCharacter(this.AdminName.Text.Trim());
		//if (this.AdminNames.Trim().Length == 0)
		//{
		//    this.Limit.outMsgBox(@"温馨提示：\n\n 用户名不能为空！", "Default.aspx", true);
		//}
		//this.AdminPass = this.AdminPwd.Text;
		//if (this.AdminPass.Trim().Length == 0)
		//{
		//    this.Limit.outMsgBox(@"温馨提示:\n\n 密码不能为空！", true);
		//}
		//this.AdminCode = this.GetCode.Text;
		//if (this.AdminCode.Trim().Length == 0)
		//{
		//    this.Limit.outMsgBox(@"温馨提示:\n\n 验证码不能为空！", "Default.aspx", true);
		//}
		//if (this.ms.GetSessionInfo("CodeImageV") != this.AdminCode)
		//{
		//    this.Limit.outMsgBox(@"温馨提示：\n\n 验证码输入错误，请重新输入！", "Default.aspx", true);
		//}
		//else
		//{
		//    string adminName = this.AdminNames;           
		//    string system = Common.GetOS;

		//    DataTable table = new DataTable();
		//    string strSQL = "select UserName ,Password,UserGroup from [web_manage_admin] where UserName='" + this.AdminNames + "' and Password='" + this.Limit.shortmd5(this.AdminPass) + "'";
		//    table = this.sqlconn.sqlReader(strSQL);
		//    if (table.Rows.Count > 0)
		//    {
		//        this.Session["AdminName"] = this.AdminNames;
		//        this.Session["AdminLogin"] = "yes";
		//        this.Session.Timeout = 120;
		//        this.Session["AdminSupport"] = table.Rows[0]["UserGroup"];
		//        //写入日志
		//        string descript = "登录成功，进入管理页面！";
		//        new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);
		//        base.Response.Redirect("Adminin.aspx");
                
		//    }
		//    else
		//    {
		//        string descript = "登录失败！登录名：" + this.AdminNames + "，登录密码：" + this.AdminPass;
		//        new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 0);
		//        this.Limit.outMsgBox(@"温馨提示：\n\n 用户名或密码错误", "Default.aspx", true);
		//    }
		//}
		#endregion
	}

}
