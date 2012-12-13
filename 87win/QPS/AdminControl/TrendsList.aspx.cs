using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.AdminControl
{
    public partial class TrendsList : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                
                
                Bind();
            }
        }

        //
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

            QPS.NEW.BLL.Trends ts = new QPS.NEW.BLL.Trends();
            ds =ts.Select(pageSize,currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = ts.GetCount();
            dgExamProj.DataBind();
        }



        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "delete")//删除
            {
                string ID = e.CommandArgument.ToString();
                QPS.NEW.BLL.Trends ts = new QPS.NEW.BLL.Trends();
                if (ts.Delete(int.Parse(ID)))
                {
                    Response.Write("<script>alert('删除成功!');</script>");
                }
                Bind();
            }
            if (e.CommandName == "LinkTo")//查看
            {
                string ID = e.CommandArgument.ToString();
                Server.Transfer("TrendsListXQ.aspx?id=" + ID);
            }
        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        //分页
        protected void Pager1_Command(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }

        protected void bntInsert_Click(object sender, EventArgs e)
        {
            Server.Transfer("TrendsInsert.aspx");
        }

       
    }
}
