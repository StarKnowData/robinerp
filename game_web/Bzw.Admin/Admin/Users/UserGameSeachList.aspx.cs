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
using System.Text;
using BCST.Common;
public partial class Admin_Users_UserGameSeachList : AdminBasePage
{
	public string seachids;
	public string usernames;
	string sqladd = "";
	public int listids = 0;
	string UserID;

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		seachids = CommonManager.Web.Request( "ids", "" );//Limit.editCharacter( Limit.getFormValue( "ids" ) ); //ID

		usernames = CommonManager.Web.Request( "users", "" );//Limit.editCharacter( Limit.getFormValue( "users" ) );//昵称

		string sqltt = CommonManager.Web.Request( "tt", "" );//Limit.editCharacter( Limit.getFormValue( "tt" ) ); //房间类型
		if( sqltt == "" )
			sqltt = "0";
		string sqlrr = CommonManager.Web.Request( "rr", "" );//Limit.editCharacter( Limit.getFormValue( "rr" ) );//游戏类别
		if( sqlrr == "" )
			sqlrr = "0";
		string sqluu = CommonManager.Web.Request( "uu", "" );//Limit.editCharacter( Limit.getFormValue( "uu" ) ); //用户注册名
		string sqld1 = CommonManager.Web.Request( "d1", "" );//Limit.editCharacter( Limit.getFormValue( "d1" ) ); //开始时间
		if( sqld1 == "" )
			sqld1 = "0";
		string sqld2 = CommonManager.Web.Request( "d2", "" );//Limit.editCharacter( Limit.getFormValue( "d2" ) ); //结束时间
		if( sqld2 == "" )
			sqld2 = "24";

		if( sqltt != "0" )
		{
			sqladd = sqladd + " and (RoomID in (select RoomID from TGameRoomInfo where GameTypeID=" + sqltt + "))";
		}

		//房间判断
		if( sqlrr != "0" )
			sqladd = sqladd + " and RoomID='" + sqlrr + "'";

		//判断时间
		//if( !Limit.IsNumeric( sqld1 ) )
		//    Limit.outMsgBox( "温馨提示：\\n\\n 时间格式不正确！", true );
		//if( !Limit.IsNumeric( sqld2 ) )
		//    Limit.outMsgBox( "温馨提示：\\n\\n 时间格式不正确！", true );
		if( !CommonManager.String.IsInteger( sqld1 ) || !CommonManager.String.IsInteger( sqld2 ) )
		{
			CommonManager.Web.RegJs(this, "alert('[结束时间]必须为数字！');history.back();", false);
			return;
		}
		//比较时间
		if( Convert.ToInt32( sqld1 ) > Convert.ToInt32( sqld2 ) )
		{
			//Limit.outMsgBox( "温馨提示：\\n\\n 前面输入的数必须小于或等于后面输入的数！", true );
			CommonManager.Web.RegJs(this, "alert('[结束时间]前面输入的数必须小于或等于后面输入的数！');history.back();", false);
			return;
		}
		else
			sqladd = sqladd + " and (datediff(hour,EndTime,getdate())>=" + sqld1 + " and datediff(hour,EndTime,getdate())<=" + sqld2 + ")";



		//判断用户名
		if( sqluu.ToString() != "" )
		{
			DataTable sdtwo = new DataTable();
			string two = "select UserID from TUsers where userName='" + sqluu + "'";
			sdtwo = DbSession.Default.FromSql( two ).ToDataTable(); //sqlconn.sqlReader( two );
			if( sdtwo.Rows.Count > 0 )
			{
				UserID = sdtwo.Rows[0]["UserID"].ToString();
			}
			else
			{
				//Limit.outMsgBox( "温馨提示：\\n\\n没有此用户名！", true );
				CommonManager.Web.RegJs( this, "alert('没有此用户名！');history.back();", false );
				return;
			}
			sdtwo.Clear();
			sqladd = sqladd + " and UserID=" + UserID;

		}
		//添加一个始终为真的条件来连接SQL
        //Response.Write("查询条件"+sqladd);
     //   Response.End();

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "ID,RoomName,DeskIndex,GameTime,EndTime,Tax,UserID,ChangePoint,SrcMoney,ChangeMoney,ChangeTax,SrcPoint" )
			.AddInputParameter( "@TableName", DbType.String, "Web_VChangeRecord" )
			.AddInputParameter( "@Wheres", DbType.String, sqladd )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "EndTime desc" )
			.ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			GameSeachList.Visible = true;
			GameSeachList.DataSource = ds.Tables[1];
			GameSeachList.DataBind();
			NoUserGame.Visible = false;
		}
		else
		{
			this.NoUserGame.Visible = true;
			GameSeachList.Visible = false;
		}

	}

	protected void GameSeachList_ItemDataBound( object sender, RepeaterItemEventArgs e )
	{
		if( e.Item.ItemType == ListItemType.AlternatingItem || e.Item.ItemType == ListItemType.Item )
		{
			DataRowView view = (DataRowView)e.Item.DataItem;
			int id = (int)view["ID"];

//            string sql = @"select ID,TUsers.UserName,RoomName,DeskIndex,SrcPoint,SrcMoney,ChangePoint,ChangeMoney,ChangeTax from Web_VChangeRecord
//							inner join TUsers
//							on Web_VChangeRecord.UserID=TUsers.UserID
//							where ID=@RecordIndex ";
			string sql = @"select ID,UserID,UserName,RoomName,DeskIndex,SrcPoint,SrcMoney,ChangePoint,ChangeMoney,ChangeTax from Web_VChangeRecord where ID=@RecordIndex ";
			DataTable dt = DbSession.Default.FromSql( sql )
				.AddInputParameter( "@RecordIndex", DbType.Int32, id )
				.ToDataTable();
			if( dt.Rows.Count > 0 )
			{
				StringBuilder sb = new StringBuilder();
				string tmp = "<a href='UserGameSeachList_xg.aspx?id={0}' title='房间名：{2}&#13;桌号：{3}&#13;结束时总分：{4}&#13;结束时金币：{5}&#13;改变分数：{6}&#13;改变金币：{7}&#13;税：{8}'>{1}</a>&nbsp;&nbsp;&nbsp;&nbsp;";

				foreach( DataRow row in dt.Rows )
				{
					sb.AppendFormat(
						tmp,
						row["ID"].ToString(),
						row["UserName"].ToString(),
						row["RoomName"].ToString(),
						row["DeskIndex"].ToString(),
						row["SrcPoint"].ToString(),
						row["SrcMoney"].ToString(),
						row["ChangePoint"].ToString(),
						row["ChangeMoney"].ToString(),
						row["ChangeTax"].ToString()
						);
				}

				Literal ltinfo = (Literal)e.Item.FindControl( "ltRelateUser" );
				ltinfo.Text = sb.ToString();
			}
		}
	}

	protected string GetName(object uid)
	{
		if( uid == null )
			return "";
		return DbSession.Default.FromSql( "select UserName from TUsers where UserID=" + uid.ToString() ).ToScalar().ToString();
	}
}
