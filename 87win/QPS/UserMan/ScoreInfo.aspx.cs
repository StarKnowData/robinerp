using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.UserMan
{
    public partial class ScoreInfo : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                QPS.BLL.Users user = new QPS.BLL.Users();
                QPS.BLL.Integral Bint = new QPS.BLL.Integral();
                if (Session["username"] != null)
                {
                    //获取Uid
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList("Username='" + uname + "'");
                    int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                    DataSet dsInt = Bint.GetListlocalize("UserId='" + uid + "'");
                    GridView1.DataSource = dsInt;
                    GridView1.DataBind();
                    if (Bint.GetSum(uid).Tables[0].Rows[0][0].ToString() == "0")
                    { lblSum.Text =" 0"; }
                    lblSum.Text = Bint.GetSum(uid).Tables[0].Rows[0][0].ToString();
                }
            }
        }
    }
}
