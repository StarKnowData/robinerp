using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using QPS.BLL;

namespace QPS.Web.AdminControl
{
    public partial class DocumentInfro : System.Web.UI.Page
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            
            if(!IsPostBack)
            {
                Bind();
            }
        }

        /// <summary>
        /// 绑定
        /// </summary>
        public void Bind()
        {
            QPS.NEW.BLL.Document dc = new QPS.NEW.BLL.Document();
            ds = dc.SelectList();
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();

        }

        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "Select")//查看
            {
                string ID = e.CommandArgument.ToString();
                Server.Transfer("DocumentXQ.aspx?id=" + ID);
            }
            if (e.CommandName == "Update")//编辑
            {
                string ID = e.CommandArgument.ToString();
                Server.Transfer("DocumentXQ.aspx?id=" + ID);
            }
        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }
    }
}
