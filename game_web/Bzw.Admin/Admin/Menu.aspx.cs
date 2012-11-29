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


public partial class Admin_Menu : AdminBasePage
{
    public string GetSession;
    public string ids = string.Empty;

    protected void Page_Load(object sender, EventArgs e)
    {
		GetSession = AdminInfo["UserGroup"].ToString(); 
        //读取当前登录管理员的权限   杨大胜 2009-4-1
		DataTable dt = DbSession.Default.FromSql( "select ModelNo from Web_Manage_Popedom where AdminID=" + AdminInfo["ID"].ToString() ).ToDataTable();

        if (dt.Rows.Count > 0)
        {
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                ids += "," + dt.Rows[i]["ModelNo"].ToString().Trim();
            }

            ids = ids.Substring(1);
        }
    }
}
