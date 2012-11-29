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

public partial class Admin_Games_GameNames : AdminBasePage
{
    public int tableids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_VGameNameInfo" )
		   .AddInputParameter( "@Wheres", DbType.String, "" )
		   .AddInputParameter( "@KeyName", DbType.String, "NameID" )
           .AddInputParameter("@OrderBy", DbType.String, "NameID")
		   .ToDataSet();

		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			GameNamesList.DataSource = ds.Tables[1];
			GameNamesList.DataBind();
			GameNamesList.Visible = true;
		}
		else
		{
			GameNamesList.Visible = false;
		}

		/*
        DataTable sd = new DataTable();
        string para = "";
        string[] sql = new string[2];
        sql[0] = @"select n.*,nc.KindName as kindname,ts.DLLFileName,ts.DeskPeople 
                    from [TGameNameInfo] as n left outer join [TGameKindInfo] as nc on n.Kindid=nc.KindId
                          left outer join [TGameServerInfo] as ts on n.NameID=ts.NameID";
        sql[1] = "select count(0) from TGameNameInfo ";
        string url = "GameNames.aspx";

        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Vistas = (Repeater)Page.FindControl("GameNamesList");
            Vistas.DataSource = sd;
            Vistas.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            sd.Clear();*/
    }
}
