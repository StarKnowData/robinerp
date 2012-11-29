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

public partial class Admin_SConfig_PFPrices : AdminBasePage
{
    
    public int TableID;
    protected void Page_Load(object sender, EventArgs e)
    {
       
        AdminPopedom.IsHoldModel("15");   

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_ClearFasciPropDefine" )
		   .AddInputParameter( "@Wheres", DbType.String, "" )
		   .AddInputParameter( "@KeyName", DbType.String, "ID" )
		   .AddInputParameter( "@OrderBy", DbType.String, "ID" )
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			ProList.DataSource = ds.Tables[1];
			ProList.DataBind();
			ProList.Visible = true;
			NoProList.Visible = false;
		}
		else
		{
			ProList.Visible = false;
			NoProList.Visible = true;
		}  
    }
}
