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

public partial class Admin_Promotion_PrListInfo : AdminBasePage
{
	string PrID;
	public int TableID;
	string Con_OnlineTime;
	public int Con_OnlineTimes;
	public int TGCount = 0;
	public int TGIncome = 0;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "13" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			PrID = tmp;
		
		string sql = @"select * from Web_VTGLog as t where TG_UserID=@TG_UserID order by RegTime DESC
					   select count(UserID) as TGCount,isnull(sum(GetMoney),0) as GetMoney from Web_VTGLog where IsRegAward=1 and IsClearing=1 and TG_UserID=@TG_UserID ";

		DataSet ds = DbSession.Default.FromSql(sql)
			.AddInputParameter("@TG_UserID", DbType.Int32, PrID)
			.ToDataSet();
		if( ds.Tables.Count > 0 )
		{
			if (ds.Tables[0].Rows.Count > 0)
			{
				PrListinfos.DataSource = ds.Tables[0];
				PrListinfos.DataBind();
			}
			if (ds.Tables[1].Rows.Count > 0)
			{
				TGCount = (int)ds.Tables[1].Rows[0]["TGCount"];
				TGIncome = (int)ds.Tables[1].Rows[0]["GetMoney"];
			}
			
		}
		else
		{
			this.NoPrListinfos.Visible = true;
			//this.YesList.Visible = false;
		}
		ds.Clear();

	}


	public string GetUserPercent( string userId )
	{
		//获取用户总游戏时长
		double playTimeSum = Convert.ToDouble( new BLL.Member().GetPlayTimeSum( userId ).Trim() );
		if( playTimeSum <= 0 )
		{
			return "0%";
		}

		double Con_OnlineTime = 0.0;
		DataRow dr = BLL.Config.GetInfoOfPromotion();
		if( dr == null )
		{
			return "0%";
		}

		//被推广玩家成为有效推广所需要的在线游戏时间
		Con_OnlineTime = Convert.ToDouble( dr["Con_OnlineTime"] );
		Con_OnlineTime = Con_OnlineTime * 60 * 60;//转换成秒数


		if( playTimeSum >= Con_OnlineTime )
		{
			return "100%";
		}
		else
		{
			//return (playTimeSum / Con_OnlineTime).ToString("p");
			return ( playTimeSum / Con_OnlineTime ).ToString( "p" );
		}
	}

}
