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
using BCST.Common;
using Bzw.Entities;
using System.Text.RegularExpressions;
using Utility;

public partial class Admin_Games_GameBattleRooms : AdminBasePage
{	

	protected void Page_Load( object sender, EventArgs e )
	{		
		AdminPopedom.IsHoldModel( "06" );
		
		string action = CommonManager.Web.Request("action","");
		if( !string.IsNullOrEmpty( action ) )
		{
			//处理页面指令
			switch( action )
			{
				case "del":
					//删除
					Del();
					break;
				default:
					break;
			}
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "TBattleRoomInfo" )
			.AddInputParameter( "@Wheres", DbType.String, "" )
			.AddInputParameter( "@KeyName", DbType.String, "BattleRoomID" )
			.AddInputParameter( "@OrderBy", DbType.String, "BattleRoomID" )
			.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				lbNonData.Visible = false;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
			}
			else
			{
				rptDataList.Visible = false;
				lbNonData.Visible = true;
			}
		}
	}

	/// <summary>
	/// 删除的方法
	/// </summary>
	private void Del()
	{
		string id = CommonManager.Web.Request("params","");
		if( string.IsNullOrEmpty( id ) || !CommonManager.String.IsInteger( id ) )
			return;
		DbSession.Default.Delete<TBattleRoomInfo>( TBattleRoomInfo._.BattleRoomID == id );
        DbSession.Default.FromSql("update TGameRoomInfo set BattleRoomID=0 where BattleRoomID=" + id).Execute();
        DbSession.Default.FromSql("delete from TBattleMatchTable where roomid=(select top 1 roomid from TGameRoomInfo where BattleRoomId="+id+")").Execute();
		//AdminLog.Default.Add( Session["AdminName"].ToString(), "删除一个混战场信息，ID号：" + id );
		string adminName = AdminInfo["UserName"].ToString();
		string descript = "删除一个混战场信息，ID号：" + id+";删除混战记录排行。";
		string system = Common.GetOS;
		new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
		string url = Regex.Replace( Request.Url.AbsoluteUri, "[?&]{1}action=del&params=[\\d+|,]+&?", "" );
		CommonManager.Web.ResponseEnd( url, true );
	}
}
