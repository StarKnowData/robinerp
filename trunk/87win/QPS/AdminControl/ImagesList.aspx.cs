using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;


namespace QPS.Web.AdminControl
{
    public partial class ImagesList : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                Bind();
            }
        }

        void Bind()
        {
            int currentpage = Convert.ToInt32(Request["CurrentPage"]);
            int check = 1;
            currentpage = (currentpage < 1) ? 1 : currentpage;
            if (this.Pager1.CurrentIndex > 0)
            {
                currentpage = this.Pager1.CurrentIndex;
            }
            int pageSize = this.Pager1.PageSize;

            QPS.BLL.Ad a = new QPS.BLL.Ad();

            ds = a.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = a.GetCount();
            dgExamProj.DataBind();
        }


        //分页
        protected void Pager1_Command(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }

        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "Update")//修改
            {
                Response.Redirect("ImagesUpdate.aspx?id=" + e.CommandArgument.ToString());
            }
        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }
    }
}
