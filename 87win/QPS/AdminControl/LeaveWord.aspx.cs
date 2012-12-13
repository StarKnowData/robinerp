using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using QPS.BLL;
using System.Data;
using System.Web.UI.HtmlControls;
using System.Configuration;
using System.Web.UI.WebControls.WebParts;

namespace QPS.Web.Manage.AdminControl
{
    public partial class LeaveWord : DataHandler.BasePage
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
            int currentpage = Convert.ToInt32(Request["CurrentPage"]);
            int check = 1;
            currentpage = (currentpage < 1) ? 1 : currentpage;
            if (this.Pager1.CurrentIndex > 0)
            {
                currentpage = this.Pager1.CurrentIndex;
            }
            int pageSize = this.Pager1.PageSize;

            QPS.NEW.BLL.Leaveword lw = new QPS.NEW.BLL.Leaveword();
            ds = lw.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = lw.GetCount();
            dgExamProj.DataBind();

        }

        //查询事件
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txlinkman.Text;
            string login = this.txlogin.Text;
             QPS.NEW.BLL.Leaveword lw =new QPS.NEW.BLL.Leaveword();

             dgExamProj.DataSource = lw.SelectList("(select UserName from Users where id= a.UserID) = '" + name + "'");
             dgExamProj.DataBind();
        }
        protected void DataPager1_PageChanged1(object sender, EventArgs e)
        {
           
        }


        //生成事件时激发
        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "delete")//删除
            {
                string ID = e.CommandArgument.ToString();
                QPS.BLL.Leaveword lw = new Leaveword();

                if (lw.Delete(int.Parse(ID)))
                {
                    Response.Write("<script>alert('删除成功!');</script>");
                }
                Bind();
            }

            if (e.CommandName == "LinkTo")//查看
            {
                string ID = e.CommandArgument.ToString();
                Server.Transfer("LeaveWordXq.aspx?id=" + ID);
            }

        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        protected void Pager1_Command(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }


        public string GetName(string tempStr)
        {
            string str = string.Empty;
            if (string.IsNullOrEmpty(tempStr))
                str = "该用户己删除";
            else
                str = tempStr;
            return str;
        }
    }
}
