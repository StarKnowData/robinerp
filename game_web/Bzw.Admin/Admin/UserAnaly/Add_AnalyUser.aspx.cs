using System;
using System.Data;

using Bzw.Data;
using BCST.Common;

public partial class Admin_UserAnaly_Add_AnalyUser : AdminBasePage
{
	public int AdminId = 0;//显示编号

	protected void Page_Load( object sender, EventArgs e )
	{
	 
		DelUser();
		if( !Page.IsPostBack )
		{
			List_AnalyUser();
		}
	}

	private void DelUser()
	{
		string action = Utility.Common.GetStringOfUrl( "action" );
		string param = Utility.Common.GetStringOfUrl("params");
		if( action == "del" && CommonManager.String.IsInteger( param ) )
		{
			int result = Utility.SqlHelper.Delete( "Web_DataAnaly_Users", "UserID", param );
			if( result > 0 )
			{
				//new BLL.AdminLog().Add( UiCommon.AdminLoginInfo.UserName, "删除ID号为" + param + "运营系统用户" );
				Utility.Common.OutMsgBox( "删除成功", "Add_AnalyUser.aspx" );
			}
			else
			{
				Utility.Common.OutMsgBox( "删除失败", "Add_AnalyUser.aspx");
			}
		}
	}

	//运营系统用户列表
	protected void List_AnalyUser()
	{
		DataTable sd = new DataTable();
		string sql = "select * from dbo.Web_DataAnaly_Users";
		DataTable dt = DbSession.Default.FromSql(sql).ToDataTable();
		if( dt.Rows.Count > 0 )
		{
			List_AdminUsers.DataSource = dt;
			List_AdminUsers.DataBind();
		}
	}

	// 添加管理员
	protected void Add_AdminUsers( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
		{
			return;
		}
		string SqlAdminName = Utility.Common.FilterString( AdminName.Text.Trim() );
		if( SqlAdminName.Trim().Length == 0 )
			Utility.Common.OutMsgBox( "温馨提示:\\n\\n请输入用户名！","");
		string SqlAdminPwd =Utility.Common.FilterString(AdminPwd.Text);
		if( SqlAdminPwd.Trim().Length == 0 )
			Utility.Common.OutMsgBox( "温馨提示:\\n\\n请输入密码！","");

		//SqlAdmin_Support = this.Admin_Support.Text.ToString();
		
		string sql = "select count(*) from Web_DataAnaly_Users where Username='" + SqlAdminName + "'";
		int SqlState = Convert.ToInt32( Utility.SqlHelper.ExecuteScalar( CommandType.Text, sql, null ) );
		if( SqlState > 0 )
		{
			Utility.Common.OutMsgBox( "温馨提示:\\n\\n用户名已存在，请更换其他用户名！","");
		}
		else
		{
			sql = "insert into Web_DataAnaly_Users (Username,Password,AddTime) values(@Username,@pass,getdate())";
			//int iAdminIdentity = Convert.ToInt32( Utility.SqlHelper.ExecuteScalar( CommandType.Text, sql, null ) );
			int result = DbSession.Default.FromSql( sql ).AddInputParameter( "@Username", DbType.String, SqlAdminName )
													 .AddInputParameter( "@pass", DbType.String, CommonManager.String.EncryptMD5SystemDefaultMethod( SqlAdminPwd, false, true ) ).Execute();
			if( result > 0 )
			{
				Utility.Common.OutMsgBox( "温馨提示:\\n\\n添加成功！", "Add_AnalyUser.aspx" );
			}
			else
			{
				Utility.Common.OutMsgBox( "温馨提示:\\n\\n添加失败！", "Add_AnalyUser.aspx" );
			}
		}
	}


	public string ControlDelLink( object adminID, object userGroup )
	{
		string delLink = "<a href=\"Del_AdminUser.aspx?id=" + adminID.ToString() + "\" onclick='{if(confirm(\"确定要删除吗?\")){return true;}return false;}'>删除</a>";
		if( Convert.ToInt32( userGroup ) == 2 )
		{
			delLink = "&nbsp;";
		}
		return delLink;
	}




}

