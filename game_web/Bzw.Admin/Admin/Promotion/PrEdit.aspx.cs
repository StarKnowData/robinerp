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

public partial class Admin_Promotion_PrEdit : AdminBasePage
{
	string PrID;
	public string Userid, Truename, Phone, Address, MoneyCount, CountTime, Pass, TGUserName;

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
			PrID = tmp; //Limit.editCharacter( Limit.getFormValue( "id" ) );

		DataTable sd = new DataTable();
		string sql = "select * from Web_VTuiGuang where id=" + PrID + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader( sql );
		if( sd.Rows.Count > 0 )
		{
			Userid = sd.Rows[0]["Userid"].ToString();
			Truename = sd.Rows[0]["Truename"].ToString();
			Phone = sd.Rows[0]["Phone"].ToString();
			Address = sd.Rows[0]["Address"].ToString();
			MoneyCount = sd.Rows[0]["MoneyCount"].ToString();
			CountTime = sd.Rows[0]["CountTime"].ToString();
			Pass = sd.Rows[0]["Pass"].ToString();

			TGUserName = sd.Rows[0]["UserName"].ToString();
		}
		sd.Clear();
	}

	protected void PrEd( object sender, EventArgs e )
	{
		string Truename, Phone, Address, Pass;
		Truename = CommonManager.Web.RequestForm( "Truename", "" );//Limit.editCharacter( Limit.getFormValue( "Truename" ) );
		Phone = CommonManager.Web.RequestForm( "Phone", "" );//Limit.editCharacter( Limit.getFormValue( "Phone" ) );
		Address = CommonManager.Web.RequestForm( "Address", "" );//Limit.editCharacter( Limit.getFormValue( "Address" ) );
		Pass = CommonManager.Web.RequestForm( "Pass", "" );//Limit.editCharacter( Limit.getFormValue( "Pass" ) );

		string sql = @"update Web_TuiGuang set TrueName=@TrueName,Phone=@Phone,Address=@Address,Pass=@Pass where ID=@ID";
		
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@TrueName", DbType.String, Truename )
			.AddInputParameter( "@Phone", DbType.String, Phone )
			.AddInputParameter( "@Address", DbType.String, Address )
			.AddInputParameter( "@Pass", DbType.String, Pass )
			.AddInputParameter( "@ID", DbType.String, PrID )
			.Execute();

		Alert( "温馨提示：\\n\\n修改推广员资料成功！", "PrList.aspx" );

		/*Hashtable ind = new Hashtable();
		ind.Add( "Truename", Truename );
		ind.Add( "Phone", Phone );
		ind.Add( "Address", Address );
		ind.Add( "Pass", Pass );
		int SqlState = sqlconn.sqlExecute( ind, "[Web_Tuiguang]", "ID=" + PrID + "", 2 );
		ind.Clear();
		if( SqlState > 0 )
			Limit.outMsgBox( "温馨提示：\\n\\n修改推广员资料成功！", "PrList.aspx", true );
		else
			Limit.outMsgBox( "温馨提示：\\n\\n修改推广员资料失败！", true );
		*/
	}
}
