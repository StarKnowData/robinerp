using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web
{
    public partial class Yxzx : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string query = "select DContent from Document where DType='5' ";
            DataSet ds = Maticsoft.DBUtility.DbHelperSQL.Query(query);
            RepeaterYx.DataSource = ds;
            RepeaterYx.DataBind();
        }
    }
}
