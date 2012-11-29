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

public partial class Admin_Users_UserMoneySeachList : AdminBasePage
{
	public string seachids;
	public string usernames;
	string sqladd, UserID;
	public int tableids;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		seachids = CommonManager.Web.Request("ids", "");  //ID
		usernames = CommonManager.Web.Request("users", ""); //昵称

		string sqltt = CommonManager.Web.Request("tt", ""); //房间类型
		if( sqltt == "" )
			sqltt = "0";
		string sqlrr = CommonManager.Web.Request("rr", ""); //游戏类别
		if( sqlrr == "" )
			sqlrr = "0";
		string sqluu = CommonManager.Web.Request( "uu", "" );  //用户注册名
		string sqld1 = CommonManager.Web.Request("d1", "");  //开始时间
		if( sqld1 == "" )
			sqld1 = "0";		
		string sqld2 = CommonManager.Web.Request("d2", ""); //结束时间
		if( sqld2 == "" )
			sqld2 = "24";


		if( sqltt != "0" )
		{
			sqladd = sqladd + " and (RoomID in (select RoomID from TGameRoomInfo where GameTypeID=" + sqltt + "))";
		}

		//房间判断
		if( sqlrr != "0" )
		{
			sqladd = sqladd + " and RoomID='" + sqlrr + "'";
		}

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
			sqladd = sqladd + " and (datediff(hour,TimeEx,getdate())>=" + sqld1 + " and datediff(hour,TimeEx,getdate())<=" + sqld2 + ")";

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
			sqladd = sqladd + " and UserName='" + sqluu + "'";

		}
		//添加一个始终为真的条件来连接SQL
		//sqladd = " and TMoneyChangeRecord.UserID=TUsers.UserID and TMoneyChangeRecord.RoomID<>0 " + sqladd;

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_VMoneyChangeRecord" )
		   .AddInputParameter( "@Wheres", DbType.String, sqladd )
		   .AddInputParameter( "@KeyName", DbType.String, "UserID" )
		   .AddInputParameter( "@OrderBy", DbType.String, "TimeEx desc" )
		   .ToDataSet();
		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			MoneySeachList.DataSource = ds.Tables[1];
			MoneySeachList.DataBind();
			MoneySeachList.Visible = true;
			NoUserGame.Visible = false;
		}
		else
		{
			NoUserGame.Visible = true;
			MoneySeachList.Visible = false;
		}		
	}
}
