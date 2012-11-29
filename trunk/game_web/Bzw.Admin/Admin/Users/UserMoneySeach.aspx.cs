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

public partial class Admin_Users_UserList_Seach_UserMoneySeach : AdminBasePage
{
	public string seachids;
	public string usernames, usernamess;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		seachids = CommonManager.Web.Request( "id", "" ); 
		if( seachids.ToString() != "" )
		{
			DataTable sd = new DataTable();
			string sql = "select userid,nickname,username from Tusers where userid='" + seachids + "'";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); 
			if( sd.Rows.Count > 0 )
			{
				usernames = sd.Rows[0]["nickname"].ToString();
				usernamess = sd.Rows[0]["username"].ToString();
			}

			sd.Clear();
		}
		else
		{
			usernames = "玩家用户";
			usernamess = "";
			this.YesMoney.Visible = false;
		}
		DataTable sdt = new DataTable();
		string sqlt = "SELECT [RoomID], [RoomName] FROM [TGameRoomInfo] order by roomid desc";
		sdt = DbSession.Default.FromSql( sqlt ).ToDataTable(); 
		if( sdt.Rows.Count > 0 )
		{
			this.rr.DataBind();
			for( int i = 0; i < sdt.Rows.Count; i++ )
			{
				this.rr.Items.Add( new ListItem( sdt.Rows[i]["RoomName"].ToString(), sdt.Rows[i]["RoomID"].ToString() ) );
			}
		}
		sdt.Clear();
	}


	protected void SearchPage( object sender, EventArgs e )
	{
		string sqlids = CommonManager.Web.RequestForm( "ids", "" );  //ID
		string sqlusers = CommonManager.Web.RequestForm( "us", "" ); //昵称
		string sqltt = CommonManager.Web.RequestForm( "tt", "" );  //房间类型
		string sqlrr = this.rr.Text.ToString();
		string sqluu = CommonManager.Web.RequestForm( "uu", "" );  //用户注册名
//		if( sqluu.ToString() == "" )
	//	{			
	//		CommonManager.Web.RegJs( this, "alert('用户名不能为空！');location.href=location.href;", false );
	//		return;
	//	}
	 	string sqld1 = CommonManager.Web.RequestForm( "d1", "" );  //开始时间
		string sqld2 = CommonManager.Web.RequestForm( "d2", "" );  //结束时间

		Response.Redirect( "UserMoneySeachList.aspx?ids=" + sqlids + "&users=" + sqlusers + "&tt=" + sqltt + "&rr=" + sqlrr + "&uu=" + sqluu + "&d1=" + sqld1 + "&d2=" + sqld2 );
	}
}
