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

public partial class Admin_News_News : AdminBasePage
{
    public int tableids;
    string Cids;
    string SqlW;
    string para = "";
    string sqlrecommendation, sqlIstop, sqlthrough;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("10");

        DataTable sd1 = new DataTable();
        string sql1 = "select TypeID,TypeName from Web_NewsType order by Typeid desc";
		sd1 = DbSession.Default.FromSql( sql1 ).ToDataTable(); //sqlconn.sqlReader(sql1);
        if (sd1.Rows.Count > 0)
        {
			TypeList.DataSource = sd1;
			TypeList.DataBind();
        }
        sd1.Clear();

		Cids = CommonManager.Web.Request( "cid", "" ); //Limit.editCharacter(Limit.getFormValue("cid"));
		sqlrecommendation = CommonManager.Web.Request( "recommendation", "" ); //Limit.editCharacter(Limit.getFormValue("recommendation"));
		sqlIstop = CommonManager.Web.Request( "Istop", "" ); //Limit.editCharacter(Limit.getFormValue("Istop"));
		sqlthrough = CommonManager.Web.Request( "through", "" ); //Limit.editCharacter(Limit.getFormValue("through"));

        if (sqlrecommendation.ToString() == "1")
        {
            SqlW = " and recommendation=1";
            para = "recommendation=1";
        }
        else if (sqlIstop.ToString() == "1")
        {
			SqlW = " and Istop=1";
            para = "Istop=1";
        }
        else if (sqlthrough.ToString() == "1")
        {
			SqlW = " and through=0";
            para = "through=0";
        }
        else if (Cids.ToString() != "")
        {
			SqlW = " and News_Type =" + Cids + "";
            para = "Cid=" + Cids + "";
        }
        else
        {
            SqlW = "";
            para = "";
        }

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_NewsData" )
		   .AddInputParameter( "@Wheres", DbType.String, SqlW )
		   .AddInputParameter( "@KeyName", DbType.String, "News_ID" )
		   .AddInputParameter( "@OrderBy", DbType.String, "News_ID desc" )
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			NewsList.DataSource = ds.Tables[1];
			NewsList.DataBind();
			NewsList.Visible = true;
			NoNewsList.Visible = false;
		}
		else
		{
			NewsList.Visible = false;
			NoNewsList.Visible = true;
		}

		/*
        DataTable sd = new DataTable();
        string[] sql = new string[2];
        sql[0] = "select * from Web_NewsData " + SqlW + " order by News_ID desc";
        //Response.Write(sql[0] + "<br>");
        sql[1] = "select count(*) from Web_NewsData " + SqlW + "";
        //Response.Write(sql[1]);
        string url = "News.aspx";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Vlist = (Repeater)Page.FindControl("NewsList");
            Vlist.DataSource = sd;
            Vlist.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoNewsList.Visible = true;
        sd.Clear();*/
    }
}
