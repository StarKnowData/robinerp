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
    public partial class Poster : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                Bind();
            }
        }

        //绑定
        public void Bind()
        {
            int currentpage = Convert.ToInt32(Request["CurrentPage"]);
            int check = 1;
            currentpage = (currentpage < 1) ? 1 : currentpage;
            if (this.Pager1.CurrentIndex > 0)
            {
                currentpage = this.Pager1.CurrentIndex;
            }
            int pageSize = this.Pager1.PageSize;

            QPS.BLL.Poster poster = new QPS.BLL.Poster();
            ds = poster.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = poster.GetCount();
            dgExamProj.DataBind();
        }


        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "LinkTo")//修改
            {
                Response.Redirect("PosterUpdate.aspx?id=" + e.CommandArgument.ToString());
            }

            if (e.CommandName == "delete")
            {
                string id = e.CommandArgument.ToString();
                QPS.BLL.Room rm = new QPS.BLL.Room();
                try
                {
                    rm.Delete(Convert.ToInt32(id));
                    Bind();
                }
                catch (Exception ex)
                { }
            }

        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        protected void Pager1_Command1(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }
    }
}
