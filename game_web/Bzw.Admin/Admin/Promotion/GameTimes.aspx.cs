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

public partial class Admin_Promotion_GameTimes : AdminBasePage
{
	int Con_ValiDay;
	string RegisterTM;
	string Userid;
	string GameTime;
	string tid;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "13" );

		DataTable sd = new DataTable();
		string tmp = CommonManager.Web.Request( "tid", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			tid = tmp; //Limit.editCharacter(Limit.getFormValue("tid"));

		tmp = CommonManager.Web.Request( "Userid", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			Userid = tmp;
		//Limit.editCharacter( Limit.getFormValue( "Userid" ) );

		#region 获取天数
		string sql3 = "select Con_ValidDay from Web_config where id=1";
		sd = DbSession.Default.FromSql( sql3 ).ToDataTable(); // sqlconn.sqlReader(sql3);
		if( sd.Rows.Count > 0 )
		{
			Con_ValiDay = Convert.ToInt32( sd.Rows[0]["Con_ValidDay"] );
		}
		else
		{
			Alert( "系统提示：\\n\\n请勿非法操作！", "GameTimes.aspx" );
		}
		#endregion

		#region 获取注册时间
		string sql1 = "select RegisterTM from Web_Users where Userid='" + Userid + "'";
		sd = DbSession.Default.FromSql( sql1 ).ToDataTable(); //sqlconn.sqlReader(sql1);
		if( sd.Rows.Count > 0 )
		{
			RegisterTM = Convert.ToDateTime( sd.Rows[0]["RegisterTM"] ).ToString( "yyyy-MM-dd" );
		}
		else
		{
			Alert( "系统提示：\\n\\n请勿非法操作！", "GameTimes.aspx" );
		}
		#endregion

		#region 统计游戏时间
		string sql2 = "select sum(GameTime) as GameTime from TChangeRecord where datediff(dd,DateADD(dd," + Con_ValiDay + ",'" + RegisterTM + "'),EndTime)<=0 and (UserID1=" + Userid + " or UserID2=" + Userid + " or UserID3=" + Userid + " or UserID4=" + Userid + ")";
		sd = DbSession.Default.FromSql( sql2 ).ToDataTable(); //sqlconn.sqlReader(sql2);
		if( sd.Rows.Count > 0 )
		{
			GameTime = sd.Rows[0]["GameTime"].ToString();
			if( GameTime.ToString() == "" )
				GameTime = "0";

			#region  更新 Web_TuiguangLog 表，GameTimeCount字段
			string sql = "update Web_TuiguangLog set GameTimeCount=@GameTimeCount where Userid=@Userid";
			int Sqlstate = DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Userid",DbType.String,Userid )
				.AddInputParameter( "@GameTimeCount", DbType.String, GameTime )
				.Execute();

			if( Sqlstate >= 0 )
				Alert( "系统提示：\\n\\n更新时间成功,请继续操作！", "PrListInfo.aspx?id=" + tid );
			else
				Alert( "系统提示：\\n\\n更新时间失败，请捎后继续尝试！", null );
			#endregion
		}
		else
		{
			Alert( "系统提示：\\n\\n占无任何游戏时间统计！", null );
		}
		#endregion

		sd.Clear();
	}
}
