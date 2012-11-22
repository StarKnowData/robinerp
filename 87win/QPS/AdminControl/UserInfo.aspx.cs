using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using QPS.BLL;
namespace QPS.Web.AdminControl
{
    public partial class UserInfo : DataHandler.BasePage
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

        /// <summary>
        /// 查询
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button1_Click(object sender, EventArgs e)
        {
            string name = this.txlinkman.Text;
            string xingm = this.txlogin.Text;
            QPS.BLL.Users user =new QPS.BLL.Users ();
            ds = user.SelectList(" Username='"+name+"' and Nickname='" +xingm +"'");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();

            //AboutBox方法，Refresh方法，SetFocus方法。
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

            QPS.BLL.Users user = new QPS.BLL.Users();

            ds = user.SelectUs(pageSize,currentpage);
            dgExamProj.DataSource = ds;
            this.Pager1.ItemCount = user.GetCount();
            dgExamProj.DataBind();

        }

        /// <summary>
        /// 新增
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button2_Click(object sender, EventArgs e)
        {
            Response.Redirect("AddUser.aspx");
            //Server.Transfer("AddUser.aspx");
            
        }
        //生成事件时激发
        protected void dgExamProj_ItemCommand(object source, DataGridCommandEventArgs e)
        {
            if (e.CommandName == "delete")
            {
                Label lab = ((Label)e.Item.FindControl("lblPack"));
                string ID = lab.Text;
                QPS.BLL.Users us = new QPS.BLL.Users();

                if (us.Delete(int.Parse(ID)))
                {
                    Bind();
                }
                Bind();
            }

            if (e.CommandName == "LinkTo")
            {
                Label lab = ((Label)e.Item.FindControl("lblPack"));
                Server.Transfer("LeaveWordXq.aspx?id=" + lab.Text);
            }

            if (e.CommandName == "InsertJF")
            {
                Label lab = ((Label)e.Item.FindControl("lblPack"));
                Server.Transfer("JfIndert.aspx?id=" + lab.Text);
            }
           
        }

        //数据绑定后激发
        protected void dgExamProj_ItemDataBound(object sender, DataGridItemEventArgs e)
        {
            if (e.Item.ItemIndex != -1)
            {
                LinkButton linkbutton = (LinkButton)e.Item.FindControl("LinkButton1");

                Label lab = ((Label)e.Item.FindControl("lblPack"));
            }
        }

        //手机号查询
        protected void bntChaXun_Click(object sender, EventArgs e)
        {
            string phone = this.txtPhone.Text;
            QPS.BLL.Users user = new QPS.BLL.Users();
            ds = user.SelectList(" Phone='" + phone + "'");
            dgExamProj.DataSource = ds;
            dgExamProj.DataBind();
        }




        //private void BindData()
        //{
        //    int currentpage = RequestUtil.getInt(base.Request, "CurrentPage");
        //    int check = 1;
        //    int specialid = RequestUtil.getInt(base.Request, "specialid");
        //    int images = RequestUtil.getInt(base.Request, "images");
        //    int slide = RequestUtil.getInt(base.Request, "slide");
        //    int num6 = RequestUtil.getInt(base.Request, "top1");
        //    int totop = RequestUtil.getInt(base.Request, "totop");
        //    int tohot = RequestUtil.getInt(base.Request, "tohot");
        //    int recommend = RequestUtil.getInt(base.Request, "recommend");
        //    currentpage = (currentpage < 1) ? 1 : currentpage;
        //    if (this.Pager1.CurrentIndex > 0)
        //    {
        //        currentpage = this.Pager1.CurrentIndex;
        //    }
        //    int pageSize = this.Pager1.PageSize;
        //    this.ArticleList.DataSource = ObjectFactory.Instance.GetArticleDao.GetDataTable(check, this.id, specialid, images, slide, num6, totop, tohot, recommend, currentpage, pageSize);
        //    this.Pager1.ItemCount = ObjectFactory.Instance.GetArticleDao.GetCount(check, this.id, specialid, images, slide, num6, totop, tohot, recommend);
        //    this.DataBind();
        //}


    }
}
