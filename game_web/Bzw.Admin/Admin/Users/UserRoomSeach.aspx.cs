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

public partial class Admin_Users_UserList_Seach_UserRoomSeach : AdminBasePage
{
	public string seachids;
	public string usernames, usernamess;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		seachids = CommonManager.Web.Request( "id", "" ); //Limit.editCharacter(Limit.getFormValue("id"));
		if( seachids.ToString() != "" )
		{
			DataTable sd = new DataTable();
			string sql = "select userid,nickname,username from Tusers where userid='" + seachids + "'";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
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
			this.YesRoomSeach.Visible = false;
		}
		DataTable sdt = new DataTable();
		string sqlt = "SELECT [RoomID], [RoomName] FROM [TGameRoomInfo] where BattleRoomID=0  order by roomid desc";
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
		string sqlids = CommonManager.Web.RequestForm( "ids", "" ); //Limit.editCharacter(Limit.getFormValue("ids")); //ID
		string sqlusers = CommonManager.Web.RequestForm( "us", "" ); //Limit.editCharacter(Limit.getFormValue("us"));//昵称
		//string sqltt = Limit.editCharacter(Limit.getFormValue("tt")); //房间类型
		string sqluu = CommonManager.Web.RequestForm( "uu", "" ); //Limit.editCharacter(Limit.getFormValue("uu")); //用户注册名
	//	if( sqluu.ToString() == "" )
	//	{
			//Limit.outMsgBox( "温馨提示：\\n\\n玩家用户名不能为空！", true );
	//		CommonManager.Web.RegJs( this, "alert('用户名不能为空！');location.href=location.href;", false );
	//		return;
	//	}
		string sqlrr = this.rr.Text.ToString(); //游戏名称
		string sqld1 = CommonManager.Web.RequestForm( "d1", "" ); //Limit.editCharacter(Limit.getFormValue("d1")); //开始时间
		string sqld2 = CommonManager.Web.RequestForm( "d2", "" ); //Limit.editCharacter(Limit.getFormValue("d2")); //结束时间
		string sqlnn = CommonManager.Web.RequestForm( "nn", "" ); //Limit.editCharacter(Limit.getFormValue("nn"));//显示记录条数
		string sqlss = CommonManager.Web.RequestForm( "ss", "" ); //Limit.editCharacter(Limit.getFormValue("ss"));//排列方式
		string sqls1 = CommonManager.Web.RequestForm( "s1", "" ); //Limit.editCharacter(Limit.getFormValue("s1")); //选定值1 降序 否则 0 升序
		// Response.Write(sqlnn);
		// Response.End();
		Response.Redirect( "UserRoomSeachList.aspx?ids=" + sqlids + "&users=" + sqlusers + "&nn=" + sqlnn + "&rr=" + sqlrr + "&uu=" + sqluu + "&d1=" + sqld1 + "&d2=" + sqld2 + "&ss=" + sqlss + "&s1=" + sqls1 );
	}
}
