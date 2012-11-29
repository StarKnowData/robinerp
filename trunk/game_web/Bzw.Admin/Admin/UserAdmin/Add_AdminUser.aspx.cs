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
using System.Text;

using Utility;
using Bzw.Data;
using BCST.Common;

public partial class Admin_Add_AdminUser : AdminBasePage
{
	public string GetSession;//管理员等级编号（2为高级管理员，1为中级管理员，0为普通管理员）
	public int AdminId = 0;//显示编号
	protected void Page_Load( object sender, EventArgs e )
	{
		//系统内置的超级管理员，无需指定模块编号
		AdminPopedom.IsHoldModel( string.Empty );

		if( !Page.IsPostBack )
		{
			BindModelList();

			List_AdminUser();

		}

	}

	//管理员信息列表
	protected void List_AdminUser()
	{
		DataTable sd = new DataTable();
		string sql = "select id,UserName,Password,UserGroup,LastLoginTime from [web_manage_admin] where UserGroup<>2  Order by id desc";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();//sqlconn.sqlReader(sql);
		if( sd.Rows.Count > 0 )
		{
			this.List_AdminUsers.DataSource = sd;
			this.List_AdminUsers.DataBind();
		}

		sd.Clear();
	}

	//绑定模块列表
	public void BindModelList()
	{
		DataTable dt = DbSession.Default.FromSql( "select ModelNo,ModelName from Web_Manage_Model" ).ToDataTable(); //sqlconn.sqlReader("select ModelNo,ModelName from Web_Manage_Model");
		if( dt.Rows.Count > 0 )
		{
			for( int i = 0; i < dt.Rows.Count; i++ )
			{
				this.chkListModels.Items.Add( new ListItem( dt.Rows[i]["ModelName"].ToString(), dt.Rows[i]["ModelNo"].ToString() ) );
			}
		}
	}

	// 添加管理员
	protected void Add_AdminUsers( object sender, EventArgs e )
	{
		string SqlAdminName, SqlAdminPwd;
		SqlAdminName = CommonManager.Web.RequestForm("AdminName", "");//Limit.editCharacter( this.AdminName.Text );
		if( SqlAdminName.ToString().Trim() == "" )
		{
			Alert( "温馨提示:\\n\\n请输入您的用户名！", null);
			return;
		}
		SqlAdminPwd = CommonManager.Web.RequestForm("AdminPwd", "");//Limit.shortmd5( AdminPwd.Text );
		if( SqlAdminPwd.ToString().Trim() == "" )
		{
			Alert( "温馨提示:\\n\\n请输入您的密码！", null );
			return;
		}
		//SqlAdmin_Support = this.Admin_Support.Text.ToString();

		string sql = "select count(*) from [web_manage_admin] where Username='" + SqlAdminName + "'";
		int SqlState = DbSession.Default.FromSql( sql ).ToScalar<int>(); //(int)sqlconn.sqlExecScalar( sql );
		if( SqlState > 0 )
		{
			Alert( "温馨提示:\\n\\n用户名已存在，请更换其他用户名！", null );
		}
		else
		{
			sql = "insert into [web_manage_admin] (Username,Password,LastLoginTime) values('" + SqlAdminName + "','" + CommonManager.String.EncryptMD5SystemDefaultMethod(SqlAdminPwd, true, true) + "','" + DateTime.Now + "')  select @@Identity";
			int iAdminIdentity = DbSession.Default.FromSql( sql ).ToScalar<int>(); 
			//add popedom info
			StringBuilder sbPopedom = new StringBuilder();
			foreach( ListItem li in chkListModels.Items )
			{
				if( li.Selected )
				{
					sbPopedom.Append( "  insert into Web_Manage_Popedom (AdminID,ModelNo) values (" + iAdminIdentity + ",'" + li.Value + "');" );
				}
			}
			if( sbPopedom.ToString().Trim().Length > 0 )
			{
				
				DbSession.Default.FromSql( sbPopedom.ToString() ).Execute();
			}

			string adminName = AdminInfo["UserName"].ToString();
			string descript = "添加管理员帐号！新增帐号：" + SqlAdminName;
			string system = Common.GetOS;
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示:\\n\\n添加管理员成功！", "Add_AdminUser.aspx");
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
