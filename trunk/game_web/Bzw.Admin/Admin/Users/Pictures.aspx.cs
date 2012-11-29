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
using Bzw.Data;
using Bzw.Entities;
using System.IO;
using System.Collections.Generic;
using BCST.Common;

public partial class Admin_Users_Pictures : AdminBasePage
{
	public string UserListTitle;

    protected void Page_Load(object sender, EventArgs e)
    {
		AdminPopedom.IsHoldModel( "04" ); 

		if( !IsPostBack )
		{
			BindDrop();
		}

		string action = CommonManager.Web.Request( "action", "" ); //Limit.getFormValue( "action" );
		string rid = CommonManager.Web.Request( "id", "" );//Limit.getFormValue( "id" );

		if( string.IsNullOrEmpty( action ) || string.IsNullOrEmpty( rid ) || !CommonManager.String.IsInteger(rid) )
		{
			BindData();
			return;
		}

		if( action == "enable" )
		{
			SetModel( rid, true );
		}
		else if( action == "disable" )
		{
			SetModel( rid, false );
		}
		else if( action == "del" )
		{
			Del( rid );
		}
	}

	/// <summary>
	/// 绑定下拉列表
	/// </summary>
	private void BindDrop()
	{
		//绑定会员列表
		//DataTable ul = DbSession.Default.From<TUsers>().Select(TUsers._.UserID,TUsers._.UserName).OrderBy( TUsers._.UserID.Desc ).ToDataTable();
		//if( ul.Rows.Count > 0 )
		//{
		//    CommonManager.Web.BindListControl( ul, dropMemberList, TUsers._.UserName.Name, TUsers._.UserID.Name, new ListItem( "==请选择会员==", "none" ) );
		//}
		//绑定状态
		dropEnable.Items.Add( new ListItem( "==请选择状态==", "none" ) );
		string[] el = Enum.GetNames( typeof( Library.EnableState ) );
		if( el.Length > 0 )
		{
			foreach( string es in el )
			{
				dropEnable.Items.Add( new ListItem( es, es ) );
			}
		}
	}

	/// <summary>
	/// 删除
	/// </summary>
	/// <param name="rid"></param>
	private void Del( string rid )
	{
		//sqlConnection sqlconn = new sqlConnection();
		//sqlconn.sql_Exec( "delete * from Web_UserAlbum where id=" + rid );
		Web_UserAlbum model = DbSession.Default.Get<Web_UserAlbum>( Web_UserAlbum._.ID == rid );
		if( model == null )
			Response.Redirect( Request.Url.AbsolutePath, true );
		if( File.Exists( Server.MapPath( model.PicPath ) ) )
		{
			File.Delete( Server.MapPath( model.PicPath ) );
		}
		DbSession.Default.Delete<Web_UserAlbum>( Web_UserAlbum._.ID == rid );
		Response.Redirect( Request.Url.AbsolutePath, true );
	}

	/// <summary>
	/// 设置对象有效无效
	/// </summary>
	/// <param name="rid"></param>
	/// <param name="p"></param>
	private void SetModel( string rid, bool p )
	{
		string sql = "update Web_UserAlbum set Enable='{0}' where id=" + rid;
		//sqlConnection sqlconn = new sqlConnection();
		if( p )
		{
			//sqlconn.sql_Exec( string.Format( sql, Library.EnableState.通过.ToString() ) );
			DbSession.Default.FromSql( string.Format( sql, Library.EnableState.通过.ToString() ) ).Execute();
		}
		else
		{
			//sqlconn.sql_Exec( string.Format( sql, Library.EnableState.屏蔽.ToString() ) );
			DbSession.Default.FromSql( string.Format( sql, Library.EnableState.屏蔽.ToString() ) ).Execute();
		}

		Response.Redirect( Request.Url.AbsolutePath, true );
	}

	/// <summary>
	/// 绑定数据
	/// </summary>
	protected void BindData()
	{
		#region oooooooooooold Code
		//DataTable sd = new DataTable();
		//string[] sql = new string[2];
		//string topSQL = " top 30 ";
		//sql[0] = "select " + topSQL + "  *  from VUsersAlbum where Enable='" + Library.EnableState.未处理 + "'";
		//sql[1] = "select " + topSQL + " count(*) from VUsersAlbum   where  Enable='" + Library.EnableState.未处理 + "'";

		//string url = "UserAlbum.aspx";

		//PageLink page_set = new PageLink( url, 30, 10, "", sql );
		//page_set.paraLinkType = paraLinkShow.middling.ToString();
		//sd = page_set.get_table();
		//if( sd.Rows.Count > 0 )
		//{

		//    rptDataList.DataSource = sd;
		//    rptDataList.DataBind();
		//    this.pageList.Text = page_set.pageList();
		//}
		//else
		//    this.NoUserList.Visible = true;
		//sd.Clear(); 
		#endregion

		DbSession.Default.CacheOn();

		string where = "";
		string es = CommonManager.Web.RequestUrlDecode( "es", "" );
		string userid = CommonManager.Web.RequestUrlDecode( "userid", "" );//Limit.getFormValue( "userid" );
		if( !string.IsNullOrEmpty( es ) )
		{
			where = "and Enable='" + es + "'";
			//Response.Write( where );
			//Response.End();
		}
		if( !string.IsNullOrEmpty( userid ) )
		{
			where += string.IsNullOrEmpty( where ) ? "and UserName='" + Server.UrlDecode( userid ) + "'" : "and UserName='" + Server.UrlDecode( userid ) + "'";

			//Response.Write( where );
			//Response.End();
		}
		DataSet dt = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "VUsersAlbum" )
			.AddInputParameter( "@Wheres", DbType.String, " " + where )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "InputTime desc" )
			.ToDataSet();

			//.AddInputParameter( "@QueryStr", DbType.String, "select * from VUsersAlbum" + where )
			//.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			//.AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
			//.AddInputParameter( "@FdShow", DbType.String, "*" )
			//.AddInputParameter( "@FdOrder", DbType.String, "InputTime desc" )
			//.ToDataTable();

		if( /*dt.Rows.Count <= 0*/ dt.Tables.Count > 0 && dt.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)dt.Tables[0].Rows[0][0];//DbSession.Default.Count<VUsersAlbum>( new WhereClip( where.Replace( "where", "" ) ) );
			anpPageIndex.CurrentPageIndex = PageIndex;

			UserList.DataSource = dt.Tables[1];
			UserList.DataBind();
			UserList.Visible = true;
			NoUserList.Visible = false;
		}
		else
		{
			UserList.Visible = false;
			this.NoUserList.Visible = true;
		}
	}
}
