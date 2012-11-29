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


public partial class Admin_SConfig_Accept : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            txtKey.Text = BLL.Config.GetContent(BLL.Config.ItemName_Accept);
        }
    }

    protected void EditFilt(object sender, EventArgs e)
    {
        //if (txtKey.Text.Trim().Length > 8000)
        //{
        //    lblMsg.Text = "保存失败：服务条款的字符数量不能超过8000！";
        //    return;
        //}

        int iRows = BLL.Config.Update(BLL.Config.ItemName_Accept, txtKey.Text);

        if (iRows > 0)
        {
            lblMsg.Text = "服务条款设置成功！" + DateTime.Now;
        }
        else
            lblMsg.Text = "服务条款设置失败！";

    }

}
