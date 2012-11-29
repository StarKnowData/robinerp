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
using Utility;
using Bzw.Data;
using BCST.Common;

public partial class Admin_Del_AdminUser : AdminBasePage
{
    public string Admin_Userids;

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel(string.Empty);

        string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
        {
			Admin_Userids = tmp;//Limit.getFormValue( "id" );

            if (!Page.IsPostBack)
            {
                Del_AdminUsers();
            }
        }
    }

    protected void Del_AdminUsers()
    {
        string ADname = string.Empty;
        string sql1 = "select * from web_manage_admin Where ID='" + Admin_Userids + "'";
		DataTable dt = DbSession.Default.FromSql( sql1 ).ToDataTable(); //sqlconn.sqlReader(sql1);
        if (dt.Rows.Count > 0)
        {
            ADname = dt.Rows[0]["UserName"].ToString();
        }
        dt.Clear();

        string sql = "delete from [web_manage_admin] Where ID='" + Admin_Userids + "';";
        sql += " delete Web_Manage_Popedom where AdminID=" + Admin_Userids;
        //sqlconn.sqlReader(sql);
		DbSession.Default.FromSql( sql ).Execute();

		/*
        Hashtable ind = new Hashtable();
        string WindwosOs = Environment.OSVersion.ToString();
        string UserAdmin = Session["AdminName"].ToString(); //当前用户名
        string UserIp = sharecode.GetUsersIP();             //当前IP
        string ErrorOs = "删除管理员ID为" + Admin_Userids + "成功！";
        ind.Add("LogUser", UserAdmin);
        ind.Add("LogIp", UserIp);
        ind.Add("OS", WindwosOs);
        ind.Add("ErrorPas", ErrorOs);
        ind.Add("Result", "1");
        ind.Add("LoginTime", DateTime.Now);
        int SqlState = sqlconn.sqlExecute(ind, "[web_Log]", 1);*/

		string adminName = AdminInfo["UserName"].ToString();
        string descript = "删除管理员信息！帐号：" + ADname;
        string system = Common.GetOS;
		
		new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);

		Response.Write( "<script>alert('温馨提示：\\n\\n删除管理员成功！');location.href='Add_AdminUser.aspx';</script>" );
    }
}
