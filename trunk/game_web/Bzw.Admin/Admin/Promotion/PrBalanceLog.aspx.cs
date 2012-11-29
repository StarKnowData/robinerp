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
using System.Collections.Generic;

public partial class Admin_Promotion_PrBalanceLog : AdminBasePage
{
	protected string BalanceMoney = "";
	

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "13" );

		string param = CommonManager.Web.Request("params","");
		if( string.IsNullOrEmpty( param ) || !CommonManager.String.IsInteger( param ) )
		    return;

		DataTable dt = DbSession.Default.FromSql("select isnull(sum(Money),0) as BalanceMoney from web_VTGBalanceLog where UserID=@UserID")
		    .AddInputParameter( "@UserID", DbType.Int32, param ).ToDataTable();
		if( dt.Rows.Count <= 0 )
		    return;
		BalanceMoney = dt.Rows[0]["BalanceMoney"].ToString();

		dt.Clear();

		string where = " and UserID=" + param;
		DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
				.AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
				.AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
				.AddInputParameter("@Columns", DbType.String, "*")
				.AddInputParameter("@TableName", DbType.String, "web_VTGBalanceLog")
				.AddInputParameter("@Wheres", DbType.String, where )
				.AddInputParameter("@KeyName", DbType.String, "Id")
				.AddInputParameter("@OrderBy", DbType.String, "Id desc")
				.ToDataSet();



		if (ds.Tables.Count > 0)
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;
			if (ds.Tables[1].Rows.Count > 0)
			{
				NoPrListinfos.Visible = false;
				PrBalanceLog.Visible = true;
				PrBalanceLog.DataSource = ds.Tables[1];
				PrBalanceLog.DataBind();
			}
			else
			{
				NoPrListinfos.Visible = true;
				PrBalanceLog.Visible = false;
			}
		}
	}
}
