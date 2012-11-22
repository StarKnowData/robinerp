using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;

namespace QPS.Web
{
    public partial class NewsCenter : System.Web.UI.Page
    {
        QPS.NEW.BLL.Trends  Btrend = new QPS.NEW.BLL.Trends ();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                DataSet recommendds = Btrend.GetList();
                Dlrecommand.DataSource = recommendds;
                Dlrecommand.DataBind();
            }
        }
        protected void dlrecommand_ItemCommand(object source, DataListCommandEventArgs e)
        {

            if (e.CommandName == "ShowDetail")
            {
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("NewsDatail.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }
    }
}
