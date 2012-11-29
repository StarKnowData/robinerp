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
public partial class Admin_SConfig_MoneyStatiEveryday : AdminBasePage
{
	
	public int listids = 0;	

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "09" );

		StringBuilder where = new StringBuilder();
		string date = CommonManager.Web.Request( "dd", "" );
		if( CommonManager.String.IsDateTime( date ) )
		{
			where.AppendFormat( " and dateadd(day,-1,StatTime) = '{0} 00:00:00'", date );
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_MoneyStatEveryday" )
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
		}
		else
		{
			this.NoRecord.Visible = true;
			rptList.Visible = false;
		}

	}	
}
