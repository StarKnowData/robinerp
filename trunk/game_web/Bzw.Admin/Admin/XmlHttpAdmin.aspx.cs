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

public partial class Admin_XmlHttpUser : UiCommon.BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        try
        {
            string stype = Common.GetStringOfUrl("type");
            switch (stype)
            {
                //1.判断用户是否登录
                case "islogin":
                    if (UiCommon.UserLoginInfo.IsLogin)
                    {
                        Response.Write("1");//表示已登录
                    }
                    else
                    {
                        Response.Write("0");//表示未登录
                    }
                    break;
                //2.判断游戏ID号是否存在
                case "nameidexist":
                    ExistNameID();
                    break;
                default:

                    break;
            }
        }
        catch (Exception ex)
        {
            Response.Write(ex.Message + ex.Source + ex.StackTrace);
        }
    }

    public void ExistNameID()
    {
        string nameid = Common.SqlEncode(Common.GetStringOfUrl("nameid"));
        if (new BLL.Game().ExistNameID(nameid))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }
}
