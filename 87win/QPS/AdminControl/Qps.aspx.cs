using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.Manage.AdminControl
{
    public partial class Qps : DataHandler.BasePage
    {
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
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
            QPS.NEW.BLL.Room rm = new QPS.NEW.BLL.Room();
            ds = rm.Select(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = rm.GetCount();
            dgExamProj.DataBind();
        }

        /// <summary>
        /// 查询
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txtName.Text;
            string Type = this.txtType.Text;
            QPS.NEW.BLL.Room rm = new QPS.NEW.BLL.Room();
            ds = rm.GetList(" Name='" + name + "' or RoomType='" + Type + "'");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }

        /// <summary>
        /// 新增
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button2_Click(object sender, EventArgs e)
        {
            Response.Redirect("RoomInsert.aspx");
        }

        /// <summary>
        /// 生成事件时激发
        /// </summary>
        /// <param name="source"></param>
        /// <param name="e"></param>
        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            //两个参数  1.当前订单ID，2.当前订单状态
            string strArgument = e.CommandArgument.ToString();
            if (e.CommandName == "delete")
            {
                string id = e.CommandArgument.ToString();
                QPS.NEW.BLL.Room pt = new QPS.NEW.BLL.Room();
                try
                {
                    pt.Delete(Convert.ToInt32(id));
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

            if (e.CommandName == "changStart")
            {
                string[] Argument = strArgument.Split('|');
                string id = Argument[0].ToString();
                string type = Argument[1].ToString();
                NEW.BLL.Room rm = new QPS.NEW.BLL.Room();
                rm.UpdateRecommend(id, type,DateTime.Now);
                Bind();
            }

            if (e.CommandName == "Examine")
            {
                string[] Argument = strArgument.Split('|');
                string id = Argument[0].ToString();
                string examine = Argument[1].ToString();
                NEW.BLL.Room rm = new QPS.NEW.BLL.Room();
                rm.UpdateExamine(id, examine, DateTime.Now);
                Bind();
            }
        }
        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        //分页
        protected void Pager1_Command1(object sender, CommandEventArgs e)
        {
            int num = Convert.ToInt32(e.CommandArgument);
            this.Pager1.CurrentIndex = num;
            this.Bind();
        }

        //查询(价格 地域)
        protected void Button3_Click(object sender, EventArgs e)
        {
            string Price = this.TextPrice.Text;
            string Are = this.TextAre.Text;
            QPS.BLL.Room rm = new QPS.BLL.Room();
            ds = rm.GetList(" RoomPrice='" + Price + "' or Are='" + Are + "'");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }

        public string GetType(string typeID)
        {
            string tempType = string.Empty;
            switch (typeID)
            {
                case "1":
                    tempType = "标准";
                    break;

                case "0":
                    tempType = "豪华";
                    break;

                Default:
                    break;
            }
            return tempType;
        }

        public string GetStart(int startID)
        {
            string tempStart = string.Empty;
            switch (startID)
            {
                case 0:
                    tempStart = "否";
                    break;
                case 1:
                    tempStart = "是";
                    break;
                default:
                    tempStart = "未知";
                    break;
            }
            return tempStart;
        }

        public string GetExamine(int startID)
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
