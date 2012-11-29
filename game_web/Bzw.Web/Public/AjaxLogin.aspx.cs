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

public partial class AjaxLogin_AjaxLogin : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        try
        {
            string position = CommonManager.Web.Request("position", "");
            if (!string.IsNullOrEmpty(position) && position == "index")
            {
                //校验验证码
                string vali = CommonManager.Web.Request("vali", "");
                if (string.IsNullOrEmpty(vali) || !CommonManager.String.IsInteger(vali))
                {
                    Response.Write("ValiError");
                    return;
                }
                if (Session["CodeImageV"] == null || vali != Session["CodeImageV"].ToString())
                {
                    Response.Write("ValidateExpair");
                    return;
                }
                Session["CodeImageV"] = "";
            }

            string sqlUserName = CommonManager.Web.RequestUrlDecode("username", "");
            string sqlpassword = CommonManager.Web.RequestUrlDecode("password", "");

            BLL.LoginResults lr = new BLL.Member().Login(sqlUserName, sqlpassword);
            if (lr == BLL.LoginResults.MemberNameInvalid || lr == BLL.LoginResults.PasswordInvalid)
            {
                Response.Write("False");
            }
            else if (lr == BLL.LoginResults.Locked)
            {
                Response.Write("NoPass");
            }
            else if (lr == BLL.LoginResults.Succeed)
            {
                new BLL.Member().UpdateLastLogin(sqlUserName, Utility.Common.RequestIP);

                Response.Write("True");
            }
        }
        catch (Exception ex)
        {
            Response.Write("Error");
            //Response.Write("Message:" + ex.Message + "Source:" + ex.Source + "StackTrace:" + ex.StackTrace);
        }
    }
}
