using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.AdminControl
{
    public partial class Qyhy : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
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
            QPS.NEW.BLL.Enterprise ep = new QPS.NEW.BLL.Enterprise();
            ds = ep.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = ep.GetCount();
            dgExamProj.DataBind();
        }


        //查询
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txlinkman.Text;
            string xingm = this.txlogin.Text;
            QPS.NEW.BLL.Enterprise ep = new QPS.NEW.BLL.Enterprise();
            ds = ep.GetList(" Username='" + name + "' or Nickname='" + xingm + "'");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();

        }
        //新增
        protected void Button2_Click(object sender, EventArgs e)
        {

        }

        //生成事件时
        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            string strArgument = e.CommandArgument.ToString();
            if (e.CommandName == "delete")
            {
                string id = e.CommandArgument.ToString();
                QPS.NEW.BLL.Enterprise ep = new QPS.NEW.BLL.Enterprise();
                try
                {
                    ep.DeleteById(Convert.ToInt32(id));
                    Bind();
                }
                catch (Exception ex)
                { }

            }

            if (e.CommandName == "LinkTo")
            {
                //Label lab = ((Label)e.Item.FindControl("lblPack"));
                Response.Redirect("RoomUpdate.aspx?id=" + e.CommandArgument.ToString());
            }
            if (e.CommandName == "Ifchecked")
            {
                string[] Argument = strArgument.Split('|');
                string id = Argument[0].ToString();
                string examine = Argument[1].ToString();
                NEW.BLL.Enterprise ep = new QPS.NEW.BLL.Enterprise();
                ep.UpdateChecked(id, examine);
                Bind();

            }

        }

        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        /// <summary>
        /// 分页
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Pager1_Command(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }


        public string GetChecked(int startID)
        {
            string tempStart = string.Empty;
            switch (startID)
            {
                case 0:
                    tempStart = "待定";
                    break;
                case 1:
                    tempStart = "通过";
                    break;
                default:
                    tempStart = "未知";
                    break;
            }
            return tempStart;
        }
    }
}
