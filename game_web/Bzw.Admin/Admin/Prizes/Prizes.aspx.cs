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

public partial class Admin_Prizes_Prizes : AdminBasePage
{
    public int TableIds;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("11");

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_Award" )
				.AddInputParameter( "@Wheres", DbType.String, "" )
				.AddInputParameter( "@KeyName", DbType.String, "Award_id" )
				.AddInputParameter( "@OrderBy", DbType.String, "Award_id desc" )
				.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				PrizesList.Visible = true;
				NoPrizesList.Visible = false;
				PrizesList.DataSource = ds.Tables[1];
				PrizesList.DataBind();
			}
			else
			{
				PrizesList.Visible = false;
				NoPrizesList.Visible = true;
			}
		}

		/*
        DataTable sd = new DataTable();
        string para = "";
        string[] sql = new string[2];
        sql[0] = "select * from Web_Award order by Award_id desc";
        sql[1] = "select count(*) from Web_Award";
        string url = "Prizes.aspx";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Vista = (Repeater)Page.FindControl("PrizesList");
            Vista.DataSource = sd;
            Vista.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoPrizesList.Visible = true;
        sd.Clear();
		 */
    }
}
