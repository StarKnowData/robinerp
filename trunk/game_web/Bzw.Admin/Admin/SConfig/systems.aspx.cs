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


public partial class Admin_SConfig_systems : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("03");

        if (!IsPostBack)
        {
            BindData();
        }
    }

    private void BindData()
    {
        string sql = "select * from Web_System";
		DataTable dt = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (dt.Rows.Count > 0)
        {
            sysList.DataSource = dt.DefaultView;
            sysList.DataBind();
        }
    }
}
