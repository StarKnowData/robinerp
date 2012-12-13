using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.BusiMan
{
    public partial class ModPwd : System.Web.UI.Page
    {

        public DataSet ds;
        QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
        QPS.NEW.Model.Enterprise Muser = new QPS.NEW.Model.Enterprise();
        static int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] != null)
                {
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList("Username='" + uname + "'");
                    userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                }
            }
        }

        protected void btnModPwd_Click(object sender, EventArgs e)
        {
            try
            {
                QPS.NEW.BLL.Enterprise Buser = new QPS.NEW.BLL.Enterprise();
              QPS.NEW.Model.Enterprise   Muser =Buser.GetModel(userid);
                // === modified by jeffery
                //if (txfOriginalPwd.Value != Buser.GetModel(userid).Password)
              if (QPS.NEW.BLL.MD5Helper.Encode(txfOriginalPwd.Value) != Muser.Password)
                // ===
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
                Muser.Password = txfModPwd.Value;
                Buser.Update(Muser);
                Response.Write("<script>alert('密码修改成功！ ')</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('修改失败!')</script>");
            }
        }
    }
}