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
using System.Text;
using BCST.Common;
public partial class Admin_SConfig_TaxStatiEveryday : AdminBasePage
{

	public int listids = 0;
	protected long TotalTax;

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		//游戏名称
		DataTable dt = DbSession.Default.FromSql( "select * from TGameNameInfo " ).ToDataTable();
		CommonManager.Web.BindListControl( dt, ddlGameName, "ComName", "NameID", new ListItem( "==全部==", "0" ) );

		StringBuilder where = new StringBuilder();
		string date = CommonManager.Web.Request( "dd", "" );
		string type = CommonManager.Web.Request( "type", "" );

		if( CommonManager.String.IsDateTime( date ) )
		{
			where.AppendFormat( " and dateadd(day,-1,StatTime) = '{0} 00:00:00'", date );
		}
		if( CommonManager.String.IsInteger( type ) )
		{
			where.AppendFormat( " and NameID={0}", type );
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_vTaxStatEveryday" )
			.AddInputParameter( "@Wheres", DbType.String, where.ToString() )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "StatTime desc" )
			.ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			rptList.Visible = true;
			rptList.DataSource = ds.Tables[1];
			rptList.DataBind();
			NoRecord.Visible = false;

			GetTotalTax( where.ToString() );
		}
		else
		{
			this.NoRecord.Visible = true;
			rptList.Visible = false;
		}

	}

	protected void GetTotalTax( string where )
	{
		TotalTax = DbSession.Default.FromSql( "select isnull(sum(Convert(bigint,Tax)),0) from Web_vTaxStatEveryday where 1=1 " + where ).ToScalar<long>();
	}

}
