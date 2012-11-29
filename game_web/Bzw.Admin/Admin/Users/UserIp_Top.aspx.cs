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

public partial class Admin_Users_UserIp_Top : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");

        DataTable sd = new DataTable();
        string sql = "select top 100 count(*) as ipcount,RegisterIP from Web_Users group by RegisterIP order by count(*) desc";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
			UserRegIp.DataSource = sd;
			UserRegIp.DataBind();
        }
        else
            Response.Write("暂无任何记录！");
    }
}
