using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.UserMan
{
    public partial class Personnal : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["username"] != null)
            {
                lblpersonnalinfo.Text = Session["username"].ToString();
            }
            string date = DateTime.Now.ToLongDateString().ToString();
            date += DateTime.Now.ToLongTimeString().ToString();
            lbldate.Text = date;
        }
    }
}
