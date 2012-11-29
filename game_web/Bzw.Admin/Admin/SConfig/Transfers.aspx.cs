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

public partial class Admin_SConfig_Transfers : AdminBasePage
{
	public string ConfigID, TransferLessAllMoney, TransferMultiple, TransferLessMoney, TransferTax, MaxTransTax;
	protected string VipTransferTax = "";
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "08" );

		DataTable sd = new DataTable();
		string sql = "select * from Web_Config where id=1";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader( sql );
		if( sd.Rows.Count > 0 )
		{
			ConfigID = sd.Rows[0]["ID"].ToString();
			TransferLessAllMoney = sd.Rows[0]["TransferLessAllMoney"].ToString();
			TransferMultiple = sd.Rows[0]["TransferMultiple"].ToString();
			TransferLessMoney = sd.Rows[0]["TransferLessMoney"].ToString();
			TransferTax = sd.Rows[0]["TransferTax"].ToString();
			MaxTransTax = sd.Rows[0]["MaxTransTax"].ToString();
			VipTransferTax = sd.Rows[0]["VipTransferTax"].ToString();
		}
		sd.Clear();
	}

	protected void TranEdit( object sender, EventArgs e )
	{
		string TransferLessAllMoney, TransferMultiple, TransferLessMoney, TransferTax, MaxTransTax;

		TransferLessAllMoney = CommonManager.Web.RequestForm( "TransferLessAllMoney", "" );// Limit.editCharacter( Limit.getFormValue( "TransferLessAllMoney" ) );
		if( !CommonManager.String.IsInteger( TransferLessAllMoney ) )
			TransferLessAllMoney = "1";

		TransferMultiple = CommonManager.Web.RequestForm( "TransferMultiple", "" );//Limit.editCharacter( Limit.getFormValue( "TransferMultiple" ) );
		if (!CommonManager.String.IsInteger(TransferMultiple) || Convert.ToInt32(TransferMultiple) <= 0)
		{
			//TransferMultiple = "1";
			CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[赠送积分的倍数]请输入大于零的数字！');location.href=location.href;", true);
			return;
		}
		TransferLessMoney = CommonManager.Web.RequestForm( "TransferLessMoney", "" );// Limit.editCharacter( Limit.getFormValue( "TransferLessMoney" ) );
		if( !CommonManager.String.IsInteger( TransferLessMoney ) )
			TransferLessMoney = "1";

		TransferTax = CommonManager.Web.RequestForm( "TransferTax", "" );//Limit.editCharacter( Limit.getFormValue( "TransferTax" ) );
		if( !CommonManager.String.IsInteger( TransferTax ) )
			TransferTax = "1";

		string vipttax = CommonManager.Web.RequestForm( "VipTransferTax", "" );//Limit.editCharacter( Limit.getFormValue( "VipTransferTax" ) );
		if( !CommonManager.String.IsInteger( vipttax ) )
			vipttax = "1";

		MaxTransTax = CommonManager.Web.RequestForm( "MaxTransTax", "" );//Limit.editCharacter( Limit.getFormValue( "MaxTransTax" ) );
		if( !CommonManager.String.IsInteger( MaxTransTax ) )
			MaxTransTax = "1";

		string sql = @"UPDATE [Web_Config] SET 
						[TransferLessMoney] = @TransferLessMoney,[TransferLessAllMoney] = @TransferLessAllMoney,
						[TransferTax] = @TransferTax,[TransferMultiple] = @TransferMultiple,
						[MaxTransTax] = @MaxTransTax,[VipTransferTax] = @VipTransferTax
						WHERE ID=@ID
					";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TransferLessMoney", DbType.String, TransferLessMoney )
			.AddInputParameter( "@TransferLessAllMoney", DbType.String, TransferLessAllMoney )
			.AddInputParameter( "@TransferTax", DbType.String, TransferTax )
			.AddInputParameter( "@TransferMultiple", DbType.String, TransferMultiple )
			.AddInputParameter( "@MaxTransTax", DbType.String, MaxTransTax )
			.AddInputParameter( "@VipTransferTax", DbType.String, vipttax )
			.AddInputParameter( "@ID", DbType.String, ConfigID )
			.Execute();

		Alert( "温馨提示：\\n\\n用户转账参数设置成功！", "Transfers.aspx" );

		/*
		Hashtable ind = new Hashtable();
		ind.Add( "TransferLessAllMoney", TransferLessAllMoney );
		ind.Add( "TransferMultiple", TransferMultiple );
		ind.Add( "TransferLessMoney", TransferLessMoney );
		ind.Add( "TransferTax", TransferTax );
		ind.Add( "MaxTransTax", MaxTransTax );
		ind.Add( "VipTransferTax", vipttax );

		int SqlState = sqlconn.sqlExecute( ind, "[Web_Config]", "id=" + ConfigID + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n用户转帐参数设置成功！", "Transfers.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n用户转帐参数设置失败！", true );*/
	}
}
