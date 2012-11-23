using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web
{
    public partial class Alert : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string query = "select DContent from Document where DType='2' ";
            // === modified by jeffery
            //DataSet ds = Maticsoft.DBUtility.DbHelperSQL.Query(query);
            QPS.NEW.DAL.SQLHelper sqlHelper = new NEW.DAL.SQLHelper(null);
            DataSet ds = sqlHelper.GetDataSet(query, CommandType.Text, null);
            // ===
            Repeater1.DataSource = ds;
            Repeater1.DataBind();
        }
    }
}
