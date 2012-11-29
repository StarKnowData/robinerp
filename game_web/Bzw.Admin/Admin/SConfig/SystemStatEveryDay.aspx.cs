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
public partial class Admin_Sconfig_SystemStatEveryDay : AdminBasePage
{
    public string strDateTime = string.Empty;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("09");
        txtDate.Attributes.Add("onfocus", "WdatePicker()");
        if (!IsPostBack )
        {
            DataBindList();
        }
    }
    public void DataBindList()
    {
        string date = DateTime.Now.ToString ("yyyy-MM-dd HH:mm:ss");
        if ( Request.QueryString["Date"] != null && Request.QueryString["Date"].ToString().Length > 0)
        {
            date = Request.QueryString["Date"].ToString();
        }
        strDateTime = date;
		DataSet ds = DbSession.Default.FromProc( "Web_PSystemStatForToday" )
            .AddInputParameter("@DateTM", DbType.DateTime, date)
            .ToDataSet();
        if (ds.Tables.Count > 0 && ds.Tables[0].Rows.Count > 0)
        {
            PrizesHList.DataSource = ds.Tables[0];
            PrizesHList.DataBind();
        }      
    }

    protected void btnStat_Click(object sender, EventArgs e)
    {
        string date = this.txtDate.Text.Trim();
        Response.Redirect("SystemStatEveryDay.aspx?Date=" + date); 
    }
   
}
