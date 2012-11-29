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

public partial class Admin_SConfig_DaoJuLog : AdminBasePage
{
    public int TableID;
    public Int64 sum;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("15");
		string where = "";
		string urlp = CommonManager.Web.RequestUrlDecode( "un", "" );
		if( !string.IsNullOrEmpty( urlp ) )
			where += " and UserName='" + urlp + "'";
		
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_VPropBuyGive" )
				.AddInputParameter( "@Wheres", DbType.String, where )
				.AddInputParameter( "@KeyName", DbType.String, "Id" )
				.AddInputParameter( "@OrderBy", DbType.String, "Id desc" )
				.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				PropList.Visible = true;
				NoPropList.Visible = false;
				PropList.DataSource = ds.Tables[1];
				PropList.DataBind();
               
			}
			else
			{
				NoPropList.Visible = false;
				PropList.Visible = true;
			}
		}
		/*
        DataTable sd = new DataTable();
        string para = "";
        string[] sql = new string[2];
		string ordertmp = " order by b.id desc";

		string tmp = "select b.*,u.*,tu.UserName,isnull(gu.UserName,'') as TargetUserName from [TPropBuyGive] as b left outer join [TPropDefine] as u on b.Propid=u.Propid left outer join [TUsers] as tu on b.UserID=tu.UserID left outer join [TUsers] as gu on b.TargetID=gu.UserID";

		string urlp = CommonManager.Web.RequestUrlDecode("un","");
		if( !string.IsNullOrEmpty( urlp ) )
			tmp += " where tu.UserName='" + urlp + "'";

		tmp += ordertmp;

		sql[0] = tmp;
		
        sql[1] = "select Count(*)  from TPropBuyGive";
        string url = "DaoJuLog.aspx";
        PageLink page_set = new PageLink(url, 20, 10, para, sql);
        page_set.paraLinkType = paraLinkShow.middling.ToString();
        sd = page_set.get_table();
        if (sd.Rows.Count > 0)
        {
            Repeater Viste = (Repeater)Page.FindControl("PropList");
            Viste.DataSource = sd;
            Viste.DataBind();
            this.pageList.Text = page_set.pageList();
        }
        else
            this.NoPropList.Visible = true;
        sd.Clear();*/
	}

    protected void PropList_ItemDataBound(object sender, RepeaterItemEventArgs e)
    {
        if (e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem)
        {
            HtmlTableCell ce1 = (HtmlTableCell)e.Item.FindControl("td1");
         
            sum += Convert.ToInt64(ce1.InnerText);
           
        }
        if (e.Item.ItemType == ListItemType.Footer)
        {
            
        }

    }
 

    
}
