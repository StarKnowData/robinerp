using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

namespace QPS.Web.Manage.AdminControl
{
    public partial class DingDan : DataHandler.BasePage
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

            QPS.NEW.BLL.Orderform of = new QPS.NEW.BLL.Orderform();
            ds = of.SelectRoom(pageSize, currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = of.GetCount();
            dgExamProj.DataBind();
        }


        //查询
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txtId.Text;
            string xingm = this.txtName.Text;
            QPS.NEW.BLL.Orderform of = new QPS.NEW.BLL.Orderform();
            if (name != "" && xingm != "")
            {
                ds = of.SelectList(Convert.ToInt32(name), xingm);
            }
            else
            {
                if (name != "")
                {
                    ds = of.SelectList( Convert.ToInt32(name));
                }
                else if (xingm != "")
                {
                    ds = of.SelectList(xingm);
                }
            }
            //ds = of.SelectList("id = '" + name + "' or (select UserName From Users where id= o.Userid) = '" + xingm + "' ");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }


        //新增
        protected void Button2_Click(object sender, EventArgs e)
        {

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


        // 生成事件时激发
        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            string command = e.CommandName.ToString();
            //两个参数  1.当前订单ID，2.当前订单状态
            string strArgument = e.CommandArgument.ToString();
            QPS.NEW.BLL.Orderform of = new QPS.NEW.BLL.Orderform();

            switch (command)
            { 
                case "changStart":
                        string[] Argument = strArgument.Split('|');
                        string id = Argument[0].ToString();
                        string type = Argument[1].ToString();
                        of.UpdateType(id,type);
                        Bind();
                    break;
                case "delete":

                    of.Delete(Convert.ToInt32(strArgument));
                        Bind();
                    break;

                case "DeleteIs":
                    string[] Arguments = strArgument.Split('|');
                    string ids = Arguments[0].ToString();
                    string examine = Arguments[1].ToString();
                    of.UpdateIsDelete(ids, examine);
                    Bind();
                    break;
                default:
                    break;
            }


        }

        //数据绑定后激发
        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {

        }

        //查询
        protected void Button3_Click(object sender, EventArgs e)
        {
            string Rname = this.TextRname.Text;
            //string zhuangt = this.TextType.Text;
            QPS.NEW.BLL.Orderform of = new QPS.NEW.BLL.Orderform();
            ds = of.SelectList("(select Name from Room where id=o.roomid)= '" + Rname + "' ");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }

        public string GetStart(int startID)
        {
            string tempStart = string.Empty;
            switch (startID)
            { 
                case 0:
                    tempStart = "未定";
                    break;
                case 1:
                    tempStart = "己定";
                    break;
                default:
                    tempStart = "未知";
                    break;
            }
            return tempStart;
        }


        public string GetName(string tempStr)
        {
            string str = string.Empty;
            if (string.IsNullOrEmpty(tempStr))
                str = "己删除";
            else
                str = tempStr;
            return str;
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
