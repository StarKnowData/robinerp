using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.Manage.framepage
{
    public partial class managerbody : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        public static void ClearAdminSession()
        {
            //Page p = new Page();
            //p.Session["admin"] = null;
        }
    }
}
