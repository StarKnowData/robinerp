using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;


public partial class Admin_SConfig_LastLoginGameCount : AdminBasePage
{
    public string LastLoginGameCount;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("15");

        DataTable sd = new DataTable();
        string sql = "select top 1 * from Web_Config ";
        sd = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
             
            LastLoginGameCount = sd.Rows[0]["LastLoginGameCount"].ToString();
        }
        sd.Clear();
    }

    protected void EditConfig(object sender, EventArgs e)
    {
        string sqlLastLoginGameCount;
        sqlLastLoginGameCount = CommonManager.Web.RequestForm("LastLoginGameCount", "");
        if (!CommonManager.String.IsInteger(sqlLastLoginGameCount))
            sqlLastLoginGameCount = "10";
        DbSession.Default.FromSql("Update Web_Config set LastLoginGameCount="+sqlLastLoginGameCount ).Execute();
        Alert("温馨提示：\\n\\n设置成功！", "LastLoginGameCount.aspx");
    }
}
