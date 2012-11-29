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

public partial class Admin_SConfig_Prices : AdminBasePage
{
	public string ConfigID, MoneyToViptimeWeek, MoneyToViptimeMonth, MoneyToViptimeHYear, MoneyToViptimeYear, RegMoney;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "15" );

		DataTable sd = new DataTable();
		string sql = "select * from Web_Config where id=1";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
		if( sd.Rows.Count > 0 )
		{
			ConfigID = sd.Rows[0]["ID"].ToString();
			MoneyToViptimeWeek = sd.Rows[0]["MoneyToViptimeWeek"].ToString();
			MoneyToViptimeMonth = sd.Rows[0]["MoneyToViptimeMonth"].ToString();
			MoneyToViptimeHYear = sd.Rows[0]["MoneyToViptimeHYear"].ToString();
			MoneyToViptimeYear = sd.Rows[0]["MoneyToViptimeYear"].ToString();
			RegMoney = sd.Rows[0]["RegWallet"].ToString();
		}
		sd.Clear();
	}

	protected void EditPric( object sender, EventArgs e )
	{
		string sqlMoneyToViptimeWeek, sqlMoneyToViptimeMonth, sqlMoneyToViptimeHYear, sqlMoneyToViptimeYear, sqlRegMoney;

		sqlMoneyToViptimeWeek = CommonManager.Web.RequestForm( "MoneyToViptimeWeek", "" );//Limit.editCharacter( Limit.getFormValue( "MoneyToViptimeWeek" ) );
		if( !CommonManager.String.IsInteger( sqlMoneyToViptimeWeek ) )
			sqlMoneyToViptimeWeek = "1";
		sqlMoneyToViptimeMonth = CommonManager.Web.RequestForm( "MoneyToViptimeMonth", "" );//Limit.editCharacter( Limit.getFormValue( "MoneyToViptimeMonth" ) );
		if( !CommonManager.String.IsInteger( sqlMoneyToViptimeMonth ) )
			sqlMoneyToViptimeMonth = "1";
		sqlMoneyToViptimeHYear = CommonManager.Web.RequestForm( "MoneyToViptimeHYear", "" );//Limit.editCharacter( Limit.getFormValue( "MoneyToViptimeHYear" ) );
		if( !CommonManager.String.IsInteger( sqlMoneyToViptimeHYear ) )
			sqlMoneyToViptimeHYear = "1";
		sqlMoneyToViptimeYear = CommonManager.Web.RequestForm( "MoneyToViptimeYear", "" );//Limit.editCharacter( Limit.getFormValue( "MoneyToViptimeYear" ) );
		if( !CommonManager.String.IsInteger( sqlMoneyToViptimeYear ) )
			sqlMoneyToViptimeYear = "1";
		sqlRegMoney = CommonManager.Web.RequestForm( "RegMoney", "" );
		if( !CommonManager.String.IsInteger( sqlRegMoney ) )
		{
			sqlRegMoney = "1";
		}

		string sql = @"UPDATE [Web_Config] SET 
						[MoneyToViptimeWeek] = @MoneyToViptimeWeek,[MoneyToViptimeMonth] = @MoneyToViptimeMonth,
						[MoneyToViptimeHYear] = @MoneyToViptimeHYear,[MoneyToViptimeYear] = @MoneyToViptimeYear,[RegWallet] = @Con_RegMoney
						WHERE ID=@ID
					";
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@MoneyToViptimeWeek", DbType.String, sqlMoneyToViptimeWeek )
			.AddInputParameter( "@MoneyToViptimeMonth", DbType.String, sqlMoneyToViptimeMonth )
			.AddInputParameter( "@MoneyToViptimeHYear", DbType.String, sqlMoneyToViptimeHYear )
			.AddInputParameter( "@MoneyToViptimeYear", DbType.String, sqlMoneyToViptimeYear )
			.AddInputParameter( "@Con_RegMoney", DbType.String, sqlRegMoney )
			.AddInputParameter( "@ID", DbType.String, ConfigID )
			.Execute();

		Alert( "温馨提示：\\n\\n设置成功！", "Prices.aspx" );

		/*
		Hashtable ind = new Hashtable();
		ind.Add( "MoneyToViptimeWeek", sqlMoneyToViptimeWeek );
		ind.Add( "MoneyToViptimeMonth", sqlMoneyToViptimeMonth );
		ind.Add( "MoneyToViptimeHYear", sqlMoneyToViptimeHYear );
		ind.Add( "MoneyToViptimeYear", sqlMoneyToViptimeYear );
		int SqlState = sqlconn.sqlExecute( ind, "[Web_Config]", "id=" + ConfigID + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\nVip价格设置成功！", "Prices.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\nVip价格设置失败！", true );*/
	}
}
