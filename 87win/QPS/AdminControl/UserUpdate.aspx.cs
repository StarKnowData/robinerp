using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.AdminControl
{
    public partial class UserUpdate : DataHandler.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                if (Request["UserID"]!=null)
                {
                    QPS.BLL.Users us = new QPS.BLL.Users();
                    string userid = Request["UserID"].ToString();
                    Model.Users user = us.GetUserByID(Convert.ToInt32(userid));
                    if (user!=null)
                    {
                        this.UserID.Value = Convert.ToString(user.Id);
                        this.TextUsername.Text = user.Username;
                        this.TextPhone.Text = user.Phone;
                        this.TextAddress.Text = user.Address;
                        this.TextMail.Text = user.Mail;
                    }
                }
            }
        }



        //修改
        protected void Button1_Click(object sender, EventArgs e)
        {
            int id = Convert.ToInt32(this.UserID.Value);
            string name = this.TextUsername.Text;
            //string password = this.TextPassword.Text;
            string phone = this.TextPhone.Text;
            string address = this.TextAddress.Text;
            string mail = this.TextMail.Text;
            //string type = this.TextUsertype.Text;

            QPS.BLL.Users us = new QPS.BLL.Users();
            Model.Users user = new Model.Users();
            user.Id = id;
            user.Username = name;
           // user.Password = password;
            user.Phone = phone;
            user.Mail = mail;

            if (us.UpdateUs(user))
            {
                Response.Write("<script>alert('修改成功!!');</script>");
            }
            else
            {
                Response.Write("<script>alert('修改失败!!');</script>");
            }
            


        }
    }
}
