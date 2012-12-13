using System;
using System.Collections.Generic;
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
            // === modified by jeffery
            //DataSet ds = Maticsoft.DBUtility.DbHelperSQL.Query(query);
            QPS.NEW.DAL.SQLHelper sqlhelper = new NEW.DAL.SQLHelper(null);
            DataSet ds = sqlhelper.GetDataSet(
                query,
                System.Data.CommandType.Text,
                null
                );
            // ===
            RepeaterYx.DataSource = ds;
            RepeaterYx.DataBind();
        }
    }
}
