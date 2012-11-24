using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.UserMan
{
    public partial class PersonnalInfo : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
        QPS.NEW.Model.Users Muser = new QPS.NEW.Model.Users();
      static  int  userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] != null)
                {
                    string uname = Session["username"].ToString();
                    txfUserName.Value = uname;
                    DataSet dsUser = user.GetList("Username='" + uname + "'");
                    txfPhone.Value= dsUser.Tables[0].Rows[0]["Phone"].ToString();
                    txfEmail.Value = dsUser.Tables[0].Rows[0]["Mail"].ToString();
                    txfNickName.Value = dsUser.Tables[0].Rows[0]["NickName"].ToString();
                    txfAddress.Value = dsUser.Tables[0].Rows[0]["Address"].ToString(); 
                    userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                }
            }
        }

        protected void btnModify_Click(object sender, EventArgs e)
        {
            try
            {
                Muser.Id = userid;
                if (txfUserName.Value == String.Empty)
                {
                    Response.Write("<script>alert('用户名不能为空，请重新输入')</script>");
                    return;
                }
                if (txfPhone.Value == String.Empty)
                {
                    Response.Write("<script>alert('电话不能为空，请重新输入')</script>");
                    return;
                }
                if (txfNickName.Value == String.Empty)
                {
                    Response.Write("<script>alert('昵称不能为空，请重新输入')</script>");
                    return;
                }
                Muser.Username = txfUserName.Value;
                Muser.Phone = txfPhone.Value;
                Muser.Mail = txfEmail.Value;
                Muser.Nickname = txfNickName.Value;
                Muser.Address = txfAddress.Value;
                user.Update(Muser);
                Session["username"] = Muser.Username;
                Response.Write("<script>alert('修改成功')</script>");
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('修改失败')</script>");
                return;
            }
        }
    }
}
