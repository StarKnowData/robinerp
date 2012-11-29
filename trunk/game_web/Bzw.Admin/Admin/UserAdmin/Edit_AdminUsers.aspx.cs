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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Edit_AdminUsers : AdminBasePage
{
	string AdminPwds, AdminNames;
	protected void Page_Load( object sender, EventArgs e )
	{
		this.ltUserName.Text = AdminInfo["UserName"].ToString(); // Session["AdminName"].ToString();
	}

	protected void EditAdminUsers( object sender, EventArgs e )
	{
		AdminNames = this.ltUserName.Text.ToString();
		AdminPwds = CommonManager.String.EncryptMD5SystemDefaultMethod( AdminPwd.Text.Trim(), true, true ); //Limit.shortmd5(AdminPwd.Text).ToString();
		if( AdminNames == "" )
		{
			Alert( "温馨提示:\\n\\n请输入您的用户名！", null );
			return;
		}
		if( AdminPwds == "" )
		{
			Alert( "温馨提示:\\n\\n请输入您的原始密码！", null );
			return;
		}

		string sql = "select count(*) from [web_manage_admin] where Username='" + AdminNames + "' and PassWord='" + AdminPwds + "'";
		int SqlState = DbSession.Default.FromSql( sql ).ToScalar<int>(); //(int)sqlconn.sqlExecScalar( sql );
		if( SqlState > 0 )
		{
			string sqlAdminPwd1, sqlAdminPwd2;
			sqlAdminPwd1 = CommonManager.String.EncryptMD5SystemDefaultMethod( AdminPwd1.Text.Trim(), true, true );
			sqlAdminPwd2 = CommonManager.String.EncryptMD5SystemDefaultMethod( AdminPwd2.Text.Trim(), true, true );
			if( sqlAdminPwd1 == "" )
			{
				Alert( "温馨提示:\\n\\n请输入您的新密码！", null );
				return;
			}
			if( sqlAdminPwd2 == "" )
			{
				Alert( "温馨提示:\\n\\n请输确认您的密码！", null );
				return;
			}
			if( sqlAdminPwd1 != sqlAdminPwd2 )
			{
				Alert( "温馨提示:\\n\\n请重新输入您要修改的密码！", null );
				return;
			}

			/*
			Hashtable ind = new Hashtable();
			ind.Add( "PassWord", sqlAdminPwd1 );
			SqlState = sqlconn.sqlExecute( ind, "[web_manage_admin]", "UserName='" + AdminNames + "'", 2 );
			if( SqlState > 0 )
				Limit.outMsgBox( "温馨提示:\\n\\n密码修改成功！", "../Serverinfo.asp", true );
			else
				Limit.outMsgBox( "温馨提示:\\n\\n系统异常错误，请稍候重试！", true );*/

			sql = "update web_manage_admin set PassWord=@PassWord where UserName=@UserName";

			DbSession.Default.FromSql( sql )
				.AddInputParameter( "@PassWord", DbType.String, sqlAdminPwd1 )
				.AddInputParameter( "@UserName", DbType.String, AdminNames )
				.Execute();

			Alert( "温馨提示:\\n\\n密码修改成功！", "../Serverinfo.aspx" );
		}
		else
			Alert( "温馨提示:\\n\\n您输入的原始密码不正确，请重新输入！", null );
	}
}
