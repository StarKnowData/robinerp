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


public partial class Admin_SConfig_ServiceContent : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            txtKey.Text = BLL.Config.GetContent(BLL.Config.ItemName_ServiceContent);
        }
    }

    protected void EditFilt(object sender, EventArgs e)
    {
        //if (txtKey.Text.Trim().Length > 8000)
        //{
        //    lblMsg.Text = "保存失败：服务条款的字符数量不能超过8000！";
        //    return;
        //}

        int iRows = BLL.Config.Update(BLL.Config.ItemName_ServiceContent, txtKey.Text);

        if (iRows > 0)
        {
            lblMsg.Text = "客服中心内容设置成功！" + DateTime.Now;
        }
        else
            lblMsg.Text = "客服中心内容设置失败！";

    }

}
