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

using Utility;
using Bzw.Data;
using BCST.Common;

public partial class Admin_Promotion_PrCs : AdminBasePage
{
	public string ConfigID, Con_ValidDay, Con_OnlineTime, Con_ValidUserAddMoney, Con_CardInPercent, Con_GetMoneyPercent, Con_RegMoney;
	public string Con_ValidUserMoney, Con_MinClearingMoney, Con_MoneyChangeRate;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "13" );

		DataTable sd = new DataTable();
		string sql = "select * from Web_Config where id=1";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
		if( sd.Rows.Count > 0 )
		{
			ConfigID = sd.Rows[0]["ID"].ToString();

			Con_ValidDay = sd.Rows[0]["Con_ValidDay"].ToString();
			Con_OnlineTime = sd.Rows[0]["Con_OnlineTime"].ToString();
			Con_ValidUserAddMoney = sd.Rows[0]["Con_ValidUserAddMoney"].ToString();
			Con_CardInPercent = sd.Rows[0]["Con_CardInPercent"].ToString();
			Con_GetMoneyPercent = sd.Rows[0]["Con_GetMoneyPercent"].ToString();
			Con_RegMoney = sd.Rows[0]["Con_RegMoney"].ToString();
			Con_ValidUserMoney = sd.Rows[0]["Con_ValidUserMoney"].ToString();
			Con_MinClearingMoney = sd.Rows[0]["Con_MinClearingMoney"].ToString();
			Con_MoneyChangeRate = sd.Rows[0]["Con_MoneyChangeRate"].ToString();
		}
		sd.Clear();
	}

	protected void PrCsEdit( object sender, EventArgs e )
	{
		string msg = "温馨提示：\\n\\n[{0}] 请输入大于或等于零的数字";
		string Con_ValidDay, Con_OnlineTime, Con_ValidUserAddMoney, Con_CardInPercent, Con_GetMoneyPercent, Con_RegMoney;
		string Con_ValidUserMoney, Con_MinClearingMoney, Con_MoneyChangeRate;

		Con_ValidDay = CommonManager.Web.RequestForm( "Con_ValidDay", "" );//Limit.editCharacter( Limit.getFormValue( "Con_ValidDay" ) );
		if( !Common.IsPositiveNumber( Con_ValidDay ) )
		{
			Alert( string.Format( msg, "推广的提成有效时间" ), null );
			return;
		}

		Con_OnlineTime = CommonManager.Web.RequestForm( "Con_OnlineTime", "" );//Limit.editCharacter( Limit.getFormValue( "Con_OnlineTime" ) );
		if( !Common.IsPositiveNumber( Con_OnlineTime ) )
		{
			Alert( string.Format( msg, "有效推广的玩家在线游戏时间" ), null );
			return;
		}

		Con_ValidUserAddMoney = CommonManager.Web.RequestForm( "Con_ValidUserAddMoney", "" );//Limit.editCharacter( Limit.getFormValue( "Con_ValidUserAddMoney" ) );
		if( !Common.IsPositiveNumber( Con_ValidUserAddMoney ) )
		{
			Alert( string.Format( msg, "一个有效推广给推广员的提成" ), null );
			return;
		}

		Con_CardInPercent = CommonManager.Web.RequestForm( "Con_CardInPercent", "" );//Limit.editCharacter( Limit.getFormValue( "Con_CardInPercent" ) );
		if( !Common.IsPositiveNumber( Con_CardInPercent ) )
		{
			Alert( string.Format( msg, "被推广的玩家每充值一块钱推广员所得到的金币值" ), null );
			return;
		}

		Con_GetMoneyPercent = CommonManager.Web.RequestForm( "Con_GetMoneyPercent", "" );//Limit.editCharacter( Limit.getFormValue( "Con_GetMoneyPercent" ) );
		if( !CommonManager.String.IsInteger( Con_GetMoneyPercent ) )
			Con_GetMoneyPercent = "1";

		Con_RegMoney = CommonManager.Web.RequestForm( "Con_RegMoney", "" );//Limit.editCharacter( Limit.getFormValue( "Con_RegMoney" ) );
		if( !Common.IsPositiveNumber( Con_RegMoney ) )
		{
			Alert( string.Format( msg, "玩家填入推荐人即可获得的金币数" ), null );
			return;
		}

		Con_ValidUserMoney = CommonManager.Web.RequestForm( "Con_ValidUserMoney", "" );//Limit.editCharacter( Limit.getFormValue( "Con_ValidUserMoney" ) );
		if( !Common.IsPositiveNumber( Con_ValidUserMoney ) )
		{
			Alert( string.Format( msg, "被推荐玩家成为有效推广后的奖励金币数" ), null );
			return;
		}

		Con_MinClearingMoney = CommonManager.Web.RequestForm( "Con_MinClearingMoney", "" );//Limit.editCharacter( Limit.getFormValue( "Con_MinClearingMoney" ) );
		if( !Common.IsPositiveNumber( Con_MinClearingMoney ) )
		{
			Alert( string.Format( msg, "推广账户最低要达到XX金币，才能够结算" ), null );
			return;
		}

		Con_MoneyChangeRate = CommonManager.Web.RequestForm( "Con_MoneyChangeRate", "" );//Limit.editCharacter( Limit.getFormValue( "Con_MoneyChangeRate" ) );
		if( !CommonManager.String.IsInteger( Con_MoneyChangeRate ) )
			Con_MoneyChangeRate = "1";

		string sql = @"UPDATE [Web_Config] SET 
						[Con_ValidDay] = @Con_ValidDay,[Con_OnlineTime] = @Con_OnlineTime,
						[Con_ValidUserAddMoney] = @Con_ValidUserAddMoney,
						[Con_CardInPercent] = @Con_CardInPercent,[Con_GetMoneyPercent] = @Con_GetMoneyPercent,
						[Con_RegMoney] = @Con_RegMoney,[Con_ValidUserMoney] = @Con_ValidUserMoney,
						[Con_MinClearingMoney] = @Con_MinClearingMoney,
						[Con_MoneyChangeRate] = @Con_MoneyChangeRate
						WHERE ID=@ID
					";
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Con_ValidDay", DbType.String, Con_ValidDay )
			.AddInputParameter( "@Con_OnlineTime", DbType.String, Con_OnlineTime )
			.AddInputParameter( "@Con_ValidUserAddMoney", DbType.String, Con_ValidUserAddMoney )
			.AddInputParameter( "@Con_CardInPercent", DbType.String, Con_CardInPercent )
			.AddInputParameter( "@Con_GetMoneyPercent", DbType.String, Con_GetMoneyPercent )
			.AddInputParameter( "@Con_RegMoney", DbType.String, Con_RegMoney )
			.AddInputParameter( "@Con_ValidUserMoney", DbType.String, Con_ValidUserMoney )
			.AddInputParameter( "@Con_MinClearingMoney", DbType.String, Con_MinClearingMoney )
			.AddInputParameter( "@Con_MoneyChangeRate", DbType.String, Con_MoneyChangeRate )
			.AddInputParameter( "@ID", DbType.String, ConfigID )
			.Execute();

		Alert( "温馨提示：\\n\\n推广相关参数设置成功！", "PrCs.aspx" );
		/*
		Hashtable ind = new Hashtable();
		ind.Add( "Con_ValidDay", Con_ValidDay );
		ind.Add( "Con_OnlineTime", Con_OnlineTime );
		ind.Add( "Con_ValidUserAddMoney", Con_ValidUserAddMoney );
		ind.Add( "Con_CardInPercent", Con_CardInPercent );
		ind.Add( "Con_GetMoneyPercent", Con_GetMoneyPercent );
		ind.Add( "Con_RegMoney", Con_RegMoney );
		ind.Add( "Con_ValidUserMoney", Con_ValidUserMoney );
		ind.Add( "Con_MinClearingMoney", Con_MinClearingMoney );
		ind.Add( "Con_MoneyChangeRate", Con_MoneyChangeRate );
		ind.Add( "RegWallet", RegWallet );

		int SqlState = sqlconn.sqlExecute( ind, "[Web_Config]", "id=" + ConfigID + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n推广相关参数设置成功！", "PrCs.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n推广相关参数设置失败！", true );*/
	}
}
