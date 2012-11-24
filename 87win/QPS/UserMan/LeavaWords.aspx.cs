using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.UserMan
{
    public partial class LeavaWords : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
                QPS.NEW.BLL.Leaveword  Bleave= new QPS.NEW.BLL.Leaveword();
                if (Session["username"] != null)
                {
                    //获取Uid
                    string uname = Session["username"].ToString();
                    DataSet dsUser = user.GetList("Username='" + uname + "'");
                    int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                    DataSet dsInt = Bleave.GetListLocalise("UserID='" + uid + "'");
                    GridView1.DataSource = dsInt;
                    GridView1.DataBind();
                }
            }
        }
    }
}
