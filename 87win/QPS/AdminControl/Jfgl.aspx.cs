using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.AdminControl
{
    public partial class Jfgl : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack )
            {
                Bind();
            }
        }

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
            QPS.NEW.BLL.Integral intgl = new QPS.NEW.BLL.Integral();
            ds = intgl.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = intgl.GetCount();
            dgExamProj.DataBind();
        }

        //查询
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txlogin.Text;
            QPS.NEW.BLL.Integral intgl = new QPS.NEW.BLL.Integral();
            ds = intgl.SelectByName(name);
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }

        /// <summary>
        /// 分页事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void pager_Command(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }

        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            string m_commandName = e.CommandName.ToString();
            string m_commandArg = e.CommandArgument.ToString();
            switch (m_commandName)
            { 
                case "editItem"://修改

                    this.Bind();
                    break;

                case "delete"://删除
                    QPS.NEW.BLL.Integral il = new QPS.NEW.BLL.Integral();
                    il.Delete(Convert.ToInt32(m_commandArg));
                    this.Bind();
                    break;

                case "JiFen"://积分
                    Response.Redirect("Jfxq.aspx?userid=" + m_commandArg);
                    break;
            }
        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

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
