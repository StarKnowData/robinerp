using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web
{
    public partial class FeedBack : System.Web.UI.Page
    {
        public DataSet dsUser;
        QPS.NEW.Model.Leaveword mleave = new QPS.NEW.Model.Leaveword();
        QPS.NEW.BLL.Leaveword Bleave = new QPS.NEW.BLL.Leaveword();
        QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
        int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["username"] != null)
            {
                string uname = Session["username"].ToString();
                dsUser = user.GetList(uname);
                txbname.Text = dsUser.Tables[0].Rows[0]["NickName"].ToString();
                userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["UserID"]);
            }
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            mleave.title = txtTitle.Text.Trim();
            mleave.UserID = userid;
            mleave.Content = txbContent.Text.Trim();
            Bleave.Add(mleave);
            Response.Write("<script>alert('留言成功!')</script>");
        }

        protected void btnSubmit_Click1(object sender, EventArgs e)
        {

        }
        }
    }

