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

public partial class Admin_GameInfo_GameType : AdminBasePage
{
    public int tableids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

        DataTable sd = new DataTable();
        string sql = "select * from web_GameType order by typeid desc";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
			TypeListInfo.DataSource = sd;
			TypeListInfo.DataBind();
        }
        else
            this.NoTypeList.Visible = true;
    }
}
