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

namespace QPS.Web
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
            
            }
        }


        /// <summary>
        /// 登陆
        /// </summary>imgbtn_Click
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //protected void Button1_Click(object sender, EventArgs e)
        //{
        //    string name = this.txtName.Text;
        //    string pwd = this.txtPwd.Text;

        //    QPS.Model.Users model = new QPS.Model.Users();
        //    model.Username = name;
        //    model.Password = pwd;

        //    QPS.BLL.Users bll = new QPS.BLL.Users();
        //    bool b = bll.Denglu(name, pwd);
        //    if (b)
        //    {
        //        Response.Redirect("");
        //    }
        //}

        //注册
        protected void LinkButton1_Click(object sender, EventArgs e)
        {
            Response.Redirect("ZhuCehy.aspx");
        }

        protected void imgbtn_Click(object sender, ImageClickEventArgs e)
        {
            string role = "";
             string code = (string)Session["CheckCodes"];
             if (code == checkcode.Value)
             {
                    string name = this.txtAdminname.Text;
                    string pwd = this.txtAdminPW.Text;

                    QPS.NEW.BLL.Users bll = new QPS.NEW.BLL.Users();
                    bool b = bll.Denglu(name, QPS.NEW.BLL.MD5Helper.Encode(pwd),1);
                    if (b)
                    {
                        Session["admin"] = name;
                        Response.Redirect("main.aspx");
                    }
                    else
                    {
                        Response.Write("<script>alert('帐号或密码错误!!');</script>");
                    }
             }
             else
             {
                 Response.Write("<script>alert('验证码输入错误!!');</script>");
             }
           
        }

    }
}
