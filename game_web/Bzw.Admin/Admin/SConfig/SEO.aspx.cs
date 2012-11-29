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

public partial class Admin_SConfig_SEO : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            txtKey.Text = BLL.Config.GetContent(BLL.Config.ItemName_SeoKey);
            txtDesc.Text = BLL.Config.GetContent(BLL.Config.ItemName_SeoDesc);
        }
    }

    protected void EditFilt(object sender, EventArgs e)
    {
        if (txtKey.Text.Trim().Length > 500)
        {
            lblMsg.Text = "保存失败：META-KEYWORDS的字符个数不能超过500！";
            return;
        }

        if (txtDesc.Text.Trim().Length > 500)
        {
            lblMsg.Text = "保存失败：META-DESCRIPTION的字符个数不能超过500！";
            return;
        }

        int iRows = BLL.Config.Update(BLL.Config.ItemName_SeoKey, txtKey.Text);

        iRows += BLL.Config.Update(BLL.Config.ItemName_SeoDesc, txtDesc.Text);

        if (iRows > 0)
        {
            UiCommon.StringConfig.SetContent(BLL.Config.ItemName_SeoKey, txtKey.Text);
            UiCommon.StringConfig.SetContent(BLL.Config.ItemName_SeoDesc, txtDesc.Text);
            lblMsg.Text = "SEO内容设置成功！"+DateTime.Now;
        }
        else
            lblMsg.Text = "SEO内容设置失败！";

    }

}
