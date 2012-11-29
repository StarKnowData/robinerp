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
public partial class Admin_Sconfig_SystemStat : AdminBasePage
{   
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
		DataSet ds = DbSession.Default.FromProc( "Web_PSystemStat" ).ToDataSet();
        if (ds.Tables.Count > 0 && ds.Tables[0].Rows.Count > 0)
        {
            PrizesHList.DataSource = ds.Tables[0];
            PrizesHList.DataBind();
        }       
    }
   
}
