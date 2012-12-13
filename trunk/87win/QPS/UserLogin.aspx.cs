using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using System.Data;
using System.Collections;

namespace QPS.Web
{
    public partial class UserLogin : System.Web.UI.Page
    {
        protected void btnLogin_Click(object sender, EventArgs e)
        {
            string UserName = txbUserName.Text.Trim();
            string UserPwd = txbPwd.Text.Trim();
            QPS.NEW.BLL.Users bll = new QPS.NEW.BLL.Users();
            QPS.NEW.BLL.Enterprise Benter = new QPS.NEW.BLL.Enterprise();
            try
            {
                if (rbtuser.Checked)
                {
                    UserPwd = QPS.NEW.BLL.MD5Helper.Encode(UserPwd);
                    if (bll.Denglu(UserName, UserPwd) && txbCode.Text.Trim().Equals(Session["code"]))
                    {
                        Session["username"] = UserName;
                        Response.Redirect("MainPage.aspx", false);
                        MainMaser m = new MainMaser();
                        MainPage d = new MainPage();
                        Hashtable t = new Hashtable();
                        t.Add("username", UserName);
                        t.Add("password", UserPwd);
                        m.hashtable = t;
                        d.hashtable = t;
                    }
                }
                if (rbtBusiuser.Checked)
                {
                    UserPwd = QPS.NEW.BLL.MD5Helper.Encode(UserPwd);
                    DataSet ds = Benter.GetList("Username='" + UserName + "'and Password='" + UserPwd + "'");
                    if (ds.Tables[0].Rows.Count > 0 && txbCode.Text.Trim().Equals(Session["code"]) && ds.Tables[0].Rows[0]["IfChecked"].ToString() == "1")
                    {
                        Session["username"] = UserName;
                        Response.Redirect("BusiMan/orderMan.aspx", false);
                        MainMaser m = new MainMaser();
                        MainPage d = new MainPage();
                        Hashtable t = new Hashtable();
                        t.Add("username", UserName);
                        t.Add("password", UserPwd);
                        m.hashtable = t;
                        d.hashtable = t;
                    }
                }
                if (Session["username"] == null)
                {
                    Response.Write("<script>alert(' 登录失败!')</script>");
                    return;
                }
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert(' 登录失败!+" + ex.ToString() + "')</script>");
                return;
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            Session.Remove("username");
        }
    }
}
