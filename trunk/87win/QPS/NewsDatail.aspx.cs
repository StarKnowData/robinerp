using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
//using System.Xml.Linq;
using System.Text;
namespace QPS.Web
{
    public partial class NewsDatail : System.Web.UI.Page
    {
        QPS.NEW.BLL.Trends t = new QPS.NEW.BLL.Trends();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
               int  Newsid = Int32.Parse(Request.QueryString["id"].Trim());
                StringBuilder sb = new StringBuilder();
                sb.Append("ID=");
                sb.Append(Newsid);
                DataList1.DataSource = t.GetList(sb.ToString());
                DataList1.DataBind();
            }
        }
    }
}
