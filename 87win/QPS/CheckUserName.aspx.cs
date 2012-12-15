using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS
{
    public partial class CheckUserName : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string userName = Request.QueryString["userName"].ToString();
            QPS.NEW.BLL.Users user = new NEW.BLL.Users();

            int num = user.SelectUser(userName);

            if(num>0)
            {
                Response.Write("no");
            }
            else
            {
                Response.Write("yes");
            }

        }
    }
}