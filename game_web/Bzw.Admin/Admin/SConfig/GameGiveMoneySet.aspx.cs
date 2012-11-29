using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

namespace Bzw.Web.Admin.SConfig
{
	public partial class GameGiveMoneySet : AdminBasePage
	{
		public string ConfigID, StartPresent, EndPresent, CoinNum, TimeLength;

		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel( "12" );
			if( !IsPostBack )
			{
				DataTable sd = new DataTable();
				string sql = "select top 1 * from Web_Config where id=1";
				sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
				if( sd.Rows.Count > 0 )
				{
					ConfigID = sd.Rows[0]["ID"].ToString();
					StartPresent = sd.Rows[0]["StartPresent"].ToString();
					EndPresent = sd.Rows[0]["EndPresent"].ToString();
					CoinNum = sd.Rows[0]["CoinNum"].ToString();
					TimeLength = sd.Rows[0]["TimeLength"].ToString();
				}
				sd.Clear();
			}
		}

		protected void EditPric( object sender, EventArgs e )
		{
			string SqlStartPresent = System.Web.HttpContext.Current.Request.Form["txtBeginDate"];
			string SqlEndPresent = System.Web.HttpContext.Current.Request.Form["txtEndDate"];
			string SqlCoinNum = System.Web.HttpContext.Current.Request.Form["CoinNum"];
			string SqlTimeLength = System.Web.HttpContext.Current.Request.Form["TimeLength"];
			string sql = @"UPDATE [Web_Config] SET 
						[StartPresent] = @StartPresent,[EndPresent] = @EndPresent,[CoinNum] = @CoinNum,[TimeLength] = @TimeLength
						WHERE ID=@ID";
			DbSession.Default.FromSql( sql )
				.AddInputParameter( "StartPresent", DbType.String, SqlStartPresent )
				.AddInputParameter( "@EndPresent", DbType.String, SqlEndPresent )
				.AddInputParameter( "@CoinNum", DbType.String, SqlCoinNum )
				.AddInputParameter( "@TimeLength", DbType.String, SqlTimeLength )
				.AddInputParameter( "@ID", DbType.String, "1" )
				.Execute();
			Alert( "温馨提示：\\n\\n在线送金币设置成功！", "GameGiveMoneySet.aspx" );

		}
	}
}
