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
using BCST.Common;
public partial class Admin_Adminin : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (AdminInfo != null)
        {

        }
        else
        {
            CommonManager.Web.ResponseEnd("/admin/Default.aspx", true);
        }
    }
}
