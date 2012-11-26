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
                QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
                QPS.NEW.BLL.Integral Bint = new QPS.NEW.BLL.Integral();
                if (Session["username"] != null)
                {
                    //获取Uid
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList(uname);
                    int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["UserID"]);
                    DataSet dsInt = Bint.GetListlocalize("UserID='" + uid + "'");
                    GridView1.DataSource = dsInt;
                    GridView1.DataBind();
                    // === modified by jeffery 
                    DataTable dt = Bint.GetSum(uid).Tables[0];

                    if (dt == null || dt.Rows.Count <= 0 || dt.Rows[0][0].ToString().Trim() == "")
                    {
                        lblSum.Text = " 0";
                    }
                    else
                    {
                        lblSum.Text = Bint.GetSum(uid).Tables[0].Rows[0][0].ToString();
                    }
                    // ===
                }
            }
        }
    }
}
