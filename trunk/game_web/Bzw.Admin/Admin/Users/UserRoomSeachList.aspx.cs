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
public partial class Admin_Users_UserRoomSeachList : AdminBasePage
{
	public string seachids;
	public string usernames;
	string sqladd = "";
	string sqlsql;
	public string UserID, MatchTable, RoomName;
	 
	public int TableID;
    public  Int64 sum;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		seachids = CommonManager.Web.Request( "ids", "" );	   //ID
		usernames = CommonManager.Web.Request( "users", "" ); //昵称
		string sqluu = CommonManager.Web.Request( "uu", "" ); //用户注册名
		string sqlrr = CommonManager.Web.Request( "rr", "" ); //游戏名称
		string sqld1 = CommonManager.Web.Request( "d1", "" ); //开始时间
		string sqld2 = CommonManager.Web.Request( "d2", "" ); //结束时间
		string sqlnn = CommonManager.Web.Request( "nn", "" ); //显示记录条数

		/*if( !CommonManager.String.IsInteger( sqlnn ) || int.Parse( sqlnn ) < 0 )
			sqlnn = "10";
		*/
		string sqlss = CommonManager.Web.Request( "ss", "" ); //排列方式
		string sqls1 = CommonManager.Web.Request( "s1", "" ); //选定值1 降序 否则 0 升序
		if( string.IsNullOrEmpty( sqls1 ) )
			sqls1 = "0";


		//判断时间
	
		if( !CommonManager.String.IsInteger( sqld1 ) || !CommonManager.String.IsInteger( sqld2 ) )
		{
			CommonManager.Web.RegJs(this, "alert('[结束时间]必须为数字！');history.back();", false);
			return;
		}
		//比较时间
		if( Convert.ToInt32( sqld1 ) > Convert.ToInt32( sqld2 ) )
		{
			CommonManager.Web.RegJs(this, "alert('[结束时间]前面输入的数必须小于或等于后面输入的数！');history.back();", false);
			return;
		}
		else
			sqladd = sqladd + " and (datediff(hour,LogonDate,getdate())>=" + sqld1 + " and datediff(hour,LogonDate,getdate())<=" + sqld2 + ")";
		//判断用户名
		if( sqluu.ToString() != "" )
		{
			DataTable sdtwo = new DataTable();
			string two = "select UserID from TUsers where userName='" + sqluu + "'";
			sdtwo = DbSession.Default.FromSql(two).ToDataTable();
			if (sdtwo.Rows.Count > 0)
			{
				UserID = sdtwo.Rows[0]["UserID"].ToString();
			}
			else
			{
				CommonManager.Web.RegJs(this, "alert('没有此用户名！');history.back();", false);
				return;
			}
			sdtwo.Clear();
			sqladd = "and UserName='" + sqluu + "'";			
		}



		//查询房间
		//if( sqlrr.ToString() != "0" )
		//{
		//    DataTable sd1 = new DataTable();
		//    string sql1 = "select RoomName from TGameRoomInfo where RoomID='" + sqlrr + "'";
		//    //Response.Write(sql1);
		//    //Response.End();
		//    sd1 = sqlconn.sqlReader( sql1 );
		//    if( sd1.Rows.Count > 0 )
		//    {
		//        //MatchTable = sd1.Rows[0]["MatchTable"].ToString();
		//        //Response.Write(MatchTable);
		//        //Response.End();
		//        // Response.Write(MatchTable + ":" + sqlrr + ":" + sqladd);
		//        RoomName = sd1.Rows[0]["RoomName"].ToString();
		//    }
		//    else
		//        Limit.outMsgBox( "温馨提示：\\n\\n 没有找到房间的信息！", true );
		//}

		sqladd = " and RoomID='" + sqlrr + "' " + sqladd;
		sqlsql = sqladd;
		string orderby = "";
		if( sqlss.ToString() == "0" )
			orderby = "Point";
		else if( sqlss.ToString() == "1" )
			orderby = "Money ";
		else if( sqlss.ToString() == "2" )
			orderby = "TaxCom ";
		else if( sqlss.ToString() == "3" )
			orderby = "Win ";
		else if( sqlss.ToString() == "4" )
			orderby = "Lost ";
		else if( sqlss.ToString() == "5" )
			orderby = "Mid ";
		else if( sqlss.ToString() == "6" )
			orderby = "PlayTimeCount ";
		else if( sqlss.ToString() == "7" )
			orderby = "OnLineTimeCount ";
		else if( sqlss.ToString() == "8" )
			orderby = "LogonDate ";
		else
			orderby = "Point ";

		//Response.Write(sqladd);
		//Response.End();
		//判断升序或降序
		if( sqls1.ToString() == "1" )
			orderby = orderby + " DESC";

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_VMatchTable" )
		   .AddInputParameter( "@Wheres", DbType.String, sqlsql )
		   .AddInputParameter( "@KeyName", DbType.String, "ID" )
		   .AddInputParameter( "@OrderBy", DbType.String, orderby )
		   .ToDataSet();
    
		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
            sum = Convert.ToInt64(DbSession.Default.FromSql("select SUM(Convert(bigint,TaxCom)) from Web_VMatchTable where 1=1 " + sqlsql).ToScalar());
 			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			RoomSeachList.DataSource = ds.Tables[1];
			RoomSeachList.DataBind();
			RoomSeachList.Visible = true;
			NoUserRoom.Visible = false;
		}
		else
		{
            sum = 0;
			NoUserRoom.Visible = true;
			RoomSeachList.Visible = false;
		}

		/*
		//if (sqlnn != 0) sql = "select top " + sqlnn + " * from " + MatchTable + " " + sqladd + " ";
		DataTable sd = new DataTable();
		// string para = "id=" + seachids + "&=rr" + sqlrr + "&=d1" + sqld1 + "&=d2" + sqld2 + "&=ss" + sqlss + "&nn=" + sqlnn;
		//&d1=" + sqld1 + "&d2=" + sqld2 + "&nn=" + sqlnn + "&ss=" + sqlss + "&s1=" + sqls1 + "
		string para = " ids=" + seachids + "&users=" + usernames + "&uu=" + sqluu + "&rr=" + sqlrr + "";
		string[] sql = new string[2];
		sql[0] = "select TMatchTable.*,TUsers.UserName from  TMatchTable,TUsers  " + sqladd + "";
		//Response.Write(sql[0]);
		//Response.End();
		sql[1] = "select  count(*) from  TMatchTable,TUsers " + sqlsql + "";
		string url = "UserRoomSeachList.aspx";
		PageLink page_set = new PageLink( url, 20, 10, para, sql );
		page_set.paraLinkType = paraLinkShow.middling.ToString();
		sd = page_set.get_table();
		if( sd.Rows.Count > 0 )
		{
			Repeater Vlist = (Repeater)Page.FindControl( "RoomSeachList" );
			Vlist.DataSource = sd;
			Vlist.DataBind();
			this.pageList.Text = page_set.pageList();
		}
		else
			this.NoUserRoom.Visible = true;*/
	}
}
