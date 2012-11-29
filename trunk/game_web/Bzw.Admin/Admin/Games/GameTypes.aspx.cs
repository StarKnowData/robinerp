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

public partial class Admin_Games_GameTypes : AdminBasePage
{
    public int tableids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
           .AddInputParameter("@TableName", DbType.String, "Web_VGameKindList")
		   .AddInputParameter( "@Wheres", DbType.String, "" )
		   .AddInputParameter( "@KeyName", DbType.String, "KindID" )
		   .AddInputParameter( "@OrderBy", DbType.String, "IDSort desc,KindID desc" )
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex; 
			GameTypesList.DataSource = ds.Tables[1];
			GameTypesList.DataBind();
			GameTypesList.Visible = true;
		}
		else
		{
			GameTypesList.Visible = false;
		}		
    }
}
