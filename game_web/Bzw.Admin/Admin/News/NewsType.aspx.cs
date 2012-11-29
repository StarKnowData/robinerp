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

public partial class Admin_News_NewsType : AdminBasePage
{
    public int TableId;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("10");

		DataTable dt = DbSession.Default.FromSql( "select * from Web_NewsType order by typeid desc" ).ToDataTable();
		if( dt.Rows.Count > 0 )
		{
			News_TypeList.DataSource = dt;
			News_TypeList.DataBind();
			News_TypeList.Visible = true;
			NoNews_TypeList.Visible = false;
		}
		else
		{
			News_TypeList.Visible = false;
			NoNews_TypeList.Visible = true;
		}

		/*
        DataTable sd = new DataTable();
        string sql = "select * from Web_NewsType order by typeid desc";
        sd = sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
            Repeater Vista = (Repeater)Page.FindControl("News_TypeList");
            Vista.DataSource = sd;
            Vista.DataBind();
        }
        else
            this.NoNews_TypeList.Visible = true;
        sd.Clear();*/
    }
}
