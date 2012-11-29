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

public partial class Admin_Sconfig_AdminModifyLog : AdminBasePage
{
    public int TableId;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("09");

        if (!IsPostBack )
        {
            DataBindList();
        }

    }
    public void DataBindList()
    {
        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
            .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
            .AddInputParameter("@CurrentPage", DbType.Int32, anpPageIndex.CurrentPageIndex)
            .AddInputParameter("@Columns", DbType.String, "*")
            .AddInputParameter("@TableName", DbType.String, "Web_AdminModifyLog")
            .AddInputParameter("@Wheres", DbType.String, " ")
            .AddInputParameter("@KeyName", DbType.String, "ID")
            .AddInputParameter("@OrderBy", DbType.String, "AddTime desc")
            .ToDataSet();
        if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
        {
            anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
            //anpPageIndex.CurrentPageIndex = PageIndex;

            PrizesHList.DataSource = ds.Tables[1];
            PrizesHList.DataBind();
            PrizesHList.Visible = true;
            NoPrizesHList.Visible = false;
        }
        else
        {
            this.NoPrizesHList.Visible = true;
            PrizesHList.Visible = false;
        }
    }
    protected void WebPager1_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
    {
        this.anpPageIndex.CurrentPageIndex = e.NewPageIndex;
        DataBindList();
    }
}
