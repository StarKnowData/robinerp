using System;
using System.Data;
using Bzw.Data;
using BCST.Common;

public partial class Admin_UserAnaly_Edit_Users : AdminBasePage
{
	public int param
	{
		get
		{
			return Utility.Common.GetIntOfUrl("id");
		}
	}
	protected void Page_Load( object sender, EventArgs e )
	{
		if( !IsPostBack )
		{
			//UiCommon.AdminLoginInfo.GetAdminSession();
			getUserInfo();
		}
	}

	private void getUserInfo()
	{
		if(param<=0)
		{
			Response.Redirect( Utility.Common.UrlValue );
		}
		string sql = "select * from dbo.Web_DataAnaly_Users where UserID=@UserID";
		DataTable dt = DbSession.Default.FromSql( sql ).AddInputParameter( "@UserID", DbType.Int32, param ).ToDataTable();
		if( dt.Rows.Count > 0 )
		{
			txtUserName.Text = dt.Rows[0]["UserName"].ToString();
		}
	}


	protected void EditAdminUsers( object sender, EventArgs e )
	{
		string pass = Utility.Common.FilterString( txtPass.Text );
		string userName = Utility.Common.FilterString( txtUserName.Text.Trim() );
		if( pass != txtPass2.Text )
		{
		//	CommonManager.Web.RegJs( this.Page, "alert('两次输入的密码不一样！');location.href=location.href;", true );
		}
		int result = BLL.DataAnalyUser.Default.UpdateAnalyUserPassword( param.ToString(),pass );
		if( result > 0 )
		{
			lblMsg.Text = "修改成功！";
		}
		else
		{
			lblMsg.Text = "修改失败！";
		}
	}
}
