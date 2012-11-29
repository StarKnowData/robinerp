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

public partial class Admin_SConfig_JpPrices : AdminBasePage
{
    public int TableID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("15");

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "TPropDefine" )
				.AddInputParameter( "@Wheres", DbType.String, " and proptype=0" )
				.AddInputParameter( "@KeyName", DbType.String, "PropID" )
				.AddInputParameter( "@OrderBy", DbType.String, "PropID desc" )
				.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				ProList.Visible = true;
				NoProList.Visible = false;
				ProList.DataSource = ds.Tables[1];
				ProList.DataBind();
			}
			else
			{
				NoProList.Visible = false;
				ProList.Visible = true;
			}
		}

		/*
        DataTable sd = new DataTable();
        string para = "";
        string[] sql = new string[2];
        sql[0] = "select ROW_NUMBER() OVER(ORDER BY PropID DESC) AS RowNumber,*  from TPropDefine";
        sql[1] = "select Count(*)  from TPropDefine";
        string url = "JpPrices.aspx";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Viste = (Repeater)Page.FindControl("ProList");
            Viste.DataSource = sd;
            Viste.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoProList.Visible = true;
        sd.Clear();*/
    }
}
