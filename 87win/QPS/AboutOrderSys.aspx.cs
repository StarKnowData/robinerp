using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web
{
    public partial class AboutOrderSys : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string query = "select DContent from Document where DType='1' ";
            DataSet ds = Maticsoft.DBUtility.DbHelperSQL.Query(query);
            Repeater1.DataSource = ds;
            Repeater1.DataBind();
        }
    }
}
