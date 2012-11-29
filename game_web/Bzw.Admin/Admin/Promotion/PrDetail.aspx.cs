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

public partial class Admin_Promotion_PrDetail : AdminBasePage
{
	protected string ShouYi = string.Empty;
	
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "13" );

		string param = CommonManager.Web.Request("params","");
		if( string.IsNullOrEmpty( param ) || !CommonManager.String.IsInteger( param ) )
			return;

		DataTable dt = DbSession.Default.FromSql("select isnull(sum(GetMoney),0) as shouyi from web_vTGpayClearing where TGUserID=@UserID")
			.AddInputParameter( "@UserID", DbType.Int32, param ).ToDataTable();
		if( dt.Rows.Count <= 0 )
			return;
		ShouYi = dt.Rows[0]["shouyi"].ToString();
		dt.Clear();

		string where = " and TGUserID=" + param;
		DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
				.AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
				.AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
				.AddInputParameter("@Columns", DbType.String, "*")
				.AddInputParameter("@TableName", DbType.String, "web_vTGpayClearing")
				.AddInputParameter("@Wheres", DbType.String, where)
				.AddInputParameter("@KeyName", DbType.String, "RecordID")
				.AddInputParameter("@OrderBy", DbType.String, "RecordID desc")
				.ToDataSet();
		if (ds.Tables.Count  > 0)
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;
			if (ds.Tables[1].Rows.Count > 0)
			{
				NoPrListinfos.Visible = false;
				PrListinfos.Visible = true;
				PrListinfos.DataSource = ds.Tables[1];
				PrListinfos.DataBind();
			}
			else
			{
				NoPrListinfos.Visible = true;
				PrListinfos.Visible = false;
			}
		}
		



		/*Dictionary<string, object> output = new Dictionary<string, object>();

		dt = DbSession.Default.FromProc( "Bzw_GetTuiGuangInfo" )
			.AddInputParameter( "@TG_UserID", DbType.Int32, param )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter("@PageIndex", DbType.Int32, PageIndex)
			.AddOutputParameter( "@RecordCount", DbType.Int32, 4 )
			.ToDataTable(out output);

		anpPageIndex.RecordCount = (int)output["RecordCount"];
		anpPageIndex.CurrentPageIndex = PageIndex;
		

		if( dt.Rows.Count > 0 )
		{
			NoPrListinfos.Visible = false;
			PrListinfos.Visible = true;
			PrListinfos.DataSource = dt;
			PrListinfos.DataBind();
			int sum = 0;
			foreach( DataRow row in dt.Rows )
			{
				sum += (int)row["ShouYi"];
			}
			ShouYiCountInPage = sum.ToString();
		}
		else
		{
			NoPrListinfos.Visible = true;
			PrListinfos.Visible = false;
		}*/
	}
}
