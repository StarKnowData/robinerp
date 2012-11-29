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
using BCST.Cache;
using UiCommon;

public partial class Admin_UserAdmin_UpdateLoginName : AdminBasePage
{   

    protected void Page_Load(object sender, EventArgs e)
    { 
        if (!IsPostBack)
        {
			txtAdminName.Text = AdminInfo["UserName"].ToString();       
        }
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        string newAdminName = txtAdminName.Text.Trim();   
        if (newAdminName.Length == 0)
        {
            lblMsg.Text = "请输入网站后台默认管理员登录名";
            return;
        }  
          
		DbSession.Default.FromSql("update Web_manage_admin set UserName=@UserName where UserGroup=2")
			.AddInputParameter("@UserName",DbType.String ,newAdminName)
			.ToScalar();

		DataTable dt = DbSession.Default.FromSql("select * from Web_manage_admin where UserGroup=2").ToDataTable();
		BCSTCache.Default.Save<SessionCache>(StringConfig.AdminCacheName, dt.Rows[0]);
		BCSTCache.Default.Save<CookiesCache>(StringConfig.AdminCacheName, dt.Rows[0]["ID"].ToString(), 2);   

        lblMsg.Text = "登陆名修改成功！" + DateTime.Now;
		//Alert("登陆名修改成功！", "/Admin/Adminin.aspx");
    }
}
