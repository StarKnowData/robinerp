using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.UserMan
{
    public partial class ModPwd : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
        QPS.NEW.Model.Users Muser = new QPS.NEW.Model.Users();
        static int   userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] != null)
                {
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList(uname);
                    userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["UserID"]);
                }
                else 
                {
                    Response.Write("<script>alert('请先登录')</script>");
                    return;
                }
            }
        }
        protected void btnModPwd_Click(object sender, EventArgs e)
        {
            try
            {
                // === modified bu jeffery
                //DataHandler.PageAction pa = new DataHandler.PageAction();
                // ===
                QPS.NEW.BLL.Users Buser = new QPS.NEW.BLL.Users();
                QPS.NEW.Model.Users Muser = Buser.GetModel(userid);
                // === modified by jeffery
                //if (pa.getStatus(pa.ModifyPwd("http://59.175.238.107:8080", Session["username"].ToString(), txfModPwd.Value, "dfd8915f711b45c78c2b15ef70528699")) != "true")
                //{
                //    Response.Write("<script>alert('修改密码失败')</script>");
                //    return;
                //}
                // ===
                if (QPS.NEW.BLL.MD5Helper.Encode( txfOriginalPwd.Value) != Muser.Password)
                {
                    Response.Write("<script>alert('原始密码错误，请重新输入')</script>");
                    return;
                }
                if (txfModPwd.Value != txfRepwd.Value)
                {
                    Response.Write("<script>alert('确认密码与修改密码不一致，请重新输入')</script>");
                    return;
                }
                if (txfModPwd.Value == string.Empty)
                {
                    Response.Write("<script>alert('确认密码不能为空，请重新输入')</script>");
                    return;
                }
                Muser.Password =QPS.NEW.BLL.MD5Helper.Encode( txfModPwd.Value);
                Muser.Usertype = 0;
                user.Update(Muser);
               
                Response.Write("<script>alert('密码修改成功!')</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('修改失败!"+ex.ToString()+"')</script>"); 
            }
        }
    }
}
