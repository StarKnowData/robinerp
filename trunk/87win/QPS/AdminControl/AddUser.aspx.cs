using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class AddUser : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        //Username	Nvarchar	会员用户名
        //Password	Nvarchar	会员密码
        //Phone	Nvarchar	会员移动电话
        //Address	Nvarchar	用户名
        //Mail	Nvarchar	邮箱地址
        //Usertype	Int	会员类型

        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.TextUsername.Text;
            string pwd = this.TextPassword.Text;
            string phone = this.TextPhone.Text;
            string address = this.TextAddress.Text;
            string mail = this.TextMail.Text;
            string type = this.TextUsertype.Text;

            QPS.NEW.Model.Users us = new QPS.NEW.Model.Users();
            us.Username = name;
            us.Password = pwd;
            us.Phone = phone;
            us.Address = address;
            us.Mail = mail;
            us.Usertype = int.Parse(type);

            QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
            user.Add(us);
            int i = user.Add(us);
            if (i > 0)
            {
                Response.Write("<script>alert('添加成功!!');</script>");
            }
            else
            {
                Response.Write("<script>alert('添加失败!!');</script>");
            }
        }
    }
}
