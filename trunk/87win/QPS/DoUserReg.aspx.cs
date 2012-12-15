using System;
using System.Collections.Generic;

using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS
{
    public partial class DoUserReg : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            QPS.NEW.BLL.Users Buser = new QPS.NEW.BLL.Users();
            QPS.NEW.Model.Users Uuser = new QPS.NEW.Model.Users();
            QPS.NEW.BLL.Enterprise Euser = new QPS.NEW.BLL.Enterprise();
            QPS.NEW.Model.Enterprise Muser = new QPS.NEW.Model.Enterprise();
            int result = -1;

            string userType=Request.QueryString["type"].ToString();
            string username = Request.QueryString["username"].ToString();
            string address = Request.QueryString["add"].ToString();
            string mail = Request.QueryString["mail"].ToString();
            string pwd=Request.QueryString["pwd"].ToString();
            string phone = Request.QueryString["phone"].ToString();
            string nickname = Request.QueryString["nickname"].ToString();


            if (userType == "user")
            {
                Uuser.Username = username;
                Uuser.Address = address;
                Uuser.Mail = mail;
                Uuser.Password = pwd;
                Uuser.Phone = phone;
                Uuser.Nickname = nickname;
                Uuser.Action = "regist";
                Uuser.Sign = "48c93e18ffbe4878b344cc1749ff6dc8";
                Uuser.Usertype = 0;

                result = Buser.Add(Uuser);
                if (result == 1)
                {
                    Response.Write("1");
                }
                else if (result == -1)
                {
                    Response.Write("0");
                }
                else
                {
                    Response.Write("-1");
                }
            }
            if (userType == "enterprise")
            {
                Muser.Username = username;
                Muser.Address = address;
                Muser.Mail = mail;
                Muser.Password = pwd;
                Muser.Phone = phone;
                Muser.Nickname = nickname;

                Muser.IfChecked = 0;

                result = Euser.Add(Muser);

                if (result == 1)
                {
                    Response.Write("1");
                }
                else if (result == -1)
                {
                    Response.Write("0");
                }
                else
                {
                    Response.Write("-1");
                }
            }
        }

    }
}