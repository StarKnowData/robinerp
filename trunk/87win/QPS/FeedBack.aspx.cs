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
        QPS.Model.Leaveword mleave = new QPS.Model.Leaveword();
        QPS.BLL.Leaveword Bleave = new QPS.BLL.Leaveword();
        QPS.BLL.Users user = new QPS.BLL.Users();
        int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["username"] != null)
            {
                string uname = Session["username"].ToString();
                dsUser = user.GetList("Username='" + uname + "'");
                txbname.Text = dsUser.Tables[0].Rows[0]["Nickname"].ToString();
                userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
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

