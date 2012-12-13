using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
using System.Collections;

namespace QPS.Web
{
    public partial class RoomOrder : System.Web.UI.Page
    {
        private static Hashtable _hashtable;
        public Hashtable hashtable
        {
            set { _hashtable = value; }
            get { return _hashtable; }
        }
        private static string username = String.Empty;
        QPS.NEW.BLL.Room room = new QPS.NEW.BLL.Room();
        public string[] items;
        public DataSet ds;
        public DataSet dsorder;
        string condition = String.Empty;
        private static int i = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                // === modified by jeffery
                //dsorder = Maticsoft.DBUtility.DbHelperSQL.Query("SELECT Are,count(Are) as 'Sum' FROM Room GROUP BY Are ");
                QPS.NEW.DAL.SQLHelper sqlHelper = new NEW.DAL.SQLHelper(null);
                dsorder = sqlHelper.GetDataSet("SELECT Are,count(Are) as 'Sum' FROM Room GROUP BY Are ",
                    CommandType.Text,
                    null);
                // ===

                DataList2.DataSource = dsorder;
                DataList2.DataBind();

                bind();
                //if (Session["username"] ==null)
                //{
                //    unLog.Visible = true;
                //    userLoginfo.Visible = false;
                //}
                //if (Session["username"] != null)
                //{
                //    username = Session["username"].ToString();
                //    Label1.Text = username;
                //    unLog.Visible = false;
                //    userLoginfo.Visible = true;
                //    string query = "select DContent from Document where DType='5' ";
                //    DataSet doc = Maticsoft.DBUtility.DbHelperSQL.Query(query);
                //    Repeater1.DataSource = doc;
                //    Repeater1.DataBind();

                //}

            }
        }
        protected void DataList1_ItemCommand(object source, DataListCommandEventArgs e)
        {
            if (e.CommandName == "ShowDetail")
            {
                StringBuilder sb = new StringBuilder();
                sb.Append("RoomDetail.aspx?id=");
                sb.Append(e.CommandArgument.ToString());
                Response.Redirect(sb.ToString());
            }
        }
        protected void DataList2_ItemCommand(object source, DataListCommandEventArgs e)
        {
            if (e.CommandName == "order")
            {
                string s = e.CommandArgument.ToString();
                ds = room.GetList("Are='" + s + "' and IfRecommend=1 and IfExamine=1");
                DataList1.DataSource = ds;
                DataList1.DataBind();
            }
        }
        protected void lbt2050_Click(object sender, EventArgs e)
        {
            condition = String.Empty;
            condition = "RoomPrice between 20 and 50";
            ds = room.GetList("RoomPrice between 20 and 50 and IfRecommend=1 and IfExamine=1");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }

        protected void lbt50100_Click(object sender, EventArgs e)
        {
            condition = String.Empty;
            condition = "RoomPrice between 50 and 100";
            ds = room.GetList("RoomPrice between 50 and 100  and IfRecommend=1 and IfExamine=1");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }

        protected void lbt100200_Click(object sender, EventArgs e)
        {
            condition = String.Empty;
            condition = "RoomPrice between 100 and 200";
            ds = room.GetList(" RoomPrice between 100 and 200  and IfRecommend=1 and IfExamine=1");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }

        protected void lbt200300_Click(object sender, EventArgs e)
        {
            condition = String.Empty;
            condition = "RoomPrice between 20 and 50";
            ds = room.GetList("RoomPrice between 200 and 300  and IfRecommend=1 and IfExamine=1");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }
        protected void lbt300_Click(object sender, EventArgs e)
        {
            ds = room.GetList("RoomPrice  > 300  and IfRecommend=1 and IfExamine=1");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }

        protected void lbtPriceOrder_Click(object sender, EventArgs e)
        {
            if (i == 0)
            {
                condition += "order by RoomPrice  desc ";
                ds = room.GetAllList("RoomPrice  desc");
                DataList1.DataSource = ds;
                DataList1.DataBind();
                i = 1;
                return;
            }
            if (i == 1)
            {
                condition += "order by RoomPrice  acs ";
                ds = room.GetAllList("RoomPrice  asc");
                DataList1.DataSource = ds;
                DataList1.DataBind();
                i = 0;
                return;
            }
        }
        //protected void Button1_Click(object sender, EventArgs e)
        //{
        //    string query = textfield.Text.Trim();
        //    ds = room.GetList("Name like '%" + query + "%' or Are like '%" + query + "%' or Address like '%"+query+"%'and IfRecommend=1 and IfExamine=1 ");
        //    DataList1.DataSource = ds;
        //    DataList1.DataBind();
        //}

        protected void LinkButton1_Click(object sender, EventArgs e)
        {
            ds = room.GetAllList("RecommendTime  asc");
            DataList1.DataSource = ds;
            DataList1.DataBind();
        }

        protected void LinkButton2_Click(object sender, EventArgs e)
        {
            string username = hashtable["username"].ToString();
            string password = hashtable["password"].ToString();
            string key = "14efe3a1820b457b95da41b70fdfebc9";
            DataHandler.PostService ps = new DataHandler.PostService();
            //ps.Url = "http://59.175.238.107:8080/Yxzx.aspx";//接口地址

            ps.Url = "http://game.87win.cn/Manage/Login.aspx";//接口地址

            string _tmp = "action=login&username=" + username + "&password=" + password + "&key=" + key;
            string sign = System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile(_tmp, "md5").ToLower();
            ps.Add("username", username);//用户名
            ps.Add("password", password);//密码
            ps.Add("sign", sign);//签名验证
            ps.Add("action", "login");//登录
            ps.Add("url", "http://59.175.238.107:8080/Manage/Default.aspx");//登录成功后，跳转地址
            ps.Post();
        }


        /// <summary>
        /// 截取字符串函数
        /// </summary>
        /// <param name="Str">所要截取的字符串</param>
        /// <param name="Num">截取字符串的长度</param>
        /// <returns></returns>
        public static string GetSubString(string Str, int Num)
        {
            if (Str == null || Str == "")
                return "";
            string outstr = "";
            int n = 0;
            foreach (char ch in Str)
            {
                n += System.Text.Encoding.Default.GetByteCount(ch.ToString());
                if (n > Num)
                    break;
                else
                    outstr += ch;
            }
            outstr = n > Num ? outstr + "......" : outstr;
            return outstr;
        }

        protected void lbtPriceOrder_Click_up(object sender, EventArgs e)
        {

        }
        //首页
        protected void lblfirst_Click(object sender, EventArgs e)
        {
            if (this.lblcurrent.Text == "1")
            { }
            else
            {
                currentPage = 1;
                bind();
            }
        }


        //上一页
        protected void lbtnform_Click(object sender, EventArgs e)
        {
            if (this.lblcurrent.Text != "1")
            {
                currentPage = int.Parse(this.lblcurrent.Text) - 1;
                this.lblcurrent.Text = currentPage.ToString();
                bind();
            }
        }
        //下一页
        protected void lbtnnext_Click(object sender, EventArgs e)
        {
            if (this.lblall.Text == this.lblcurrent.Text)
            {
            }
            else
            {
                currentPage = int.Parse(this.lblcurrent.Text) + 1;
                this.lblcurrent.Text = currentPage.ToString();
                bind();
            }
        }


        //尾页
        protected void lbllast_Click(object sender, EventArgs e)
        {
            if (this.lblall.Text != this.lblcurrent.Text)
            {
                this.lblcurrent.Text = this.lblall.Text;
                currentPage = int.Parse(this.lblall.Text);
                bind();
            }
        }
        //页面跳转
        protected void btngo_Click(object sender, EventArgs e)
        {
            if (int.Parse(txtnum.Text) > int.Parse(lblall.Text) || int.Parse(txtnum.Text) < 0)
            { }
            else
            {
                currentPage = Convert.ToInt32(this.txtnum.Text);
                bind();
            }
        }
        int pageCount;//总页数
        int currentPage = 1;//第定义当前页

        private void bind()//绑定数据源
        {
            ds = room.GetList("IfRecommend=1 and IfExamine=1");
            //DataList1.DataSource = ds;
            //DataList1.DataBind();
            //创建数据源
            PagedDataSource pds = new PagedDataSource();
            //ds.Tables[0].DefaultView;
            pds.DataSource = ds.Tables[0].DefaultView;
            //允许分页
            pds.AllowPaging = true;
            //设置每页显示记录数
            pds.PageSize = int.Parse("6");
            //获取总页数
            pageCount = pds.PageCount;
            this.lblall.Text = pageCount.ToString();
            pds.CurrentPageIndex = currentPage - 1;
            //当前页
            this.lblcurrent.Text = Convert.ToString(currentPage);
            //数据绑定
            this.DataList1.DataSource = pds;
            this.DataList1.DataBind();
        }

        protected void allone_Click(object sender, EventArgs e)
        {
            ds = room.GetList("IfRecommend=1 and IfExamine=1");
            //DataList1.DataSource = ds;
            //DataList1.DataBind();
            //创建数据源
            PagedDataSource pds = new PagedDataSource();
            //ds.Tables[0].DefaultView;
            pds.DataSource = ds.Tables[0].DefaultView;
            //允许分页
            pds.AllowPaging = true;
            //设置每页显示记录数
            pds.PageSize = int.Parse("6");
            //获取总页数
            pageCount = pds.PageCount;
            this.lblall.Text = pageCount.ToString();
            pds.CurrentPageIndex = currentPage - 1;
            //当前页
            this.lblcurrent.Text = Convert.ToString(currentPage);
            //数据绑定
            this.DataList1.DataSource = pds;
            this.DataList1.DataBind();
        }

        protected void alltwo_Click(object sender, EventArgs e)
        {
            ds = room.GetList("IfRecommend=1 and IfExamine=1");
            //DataList1.DataSource = ds;
            //DataList1.DataBind();
            //创建数据源
            PagedDataSource pds = new PagedDataSource();
            //ds.Tables[0].DefaultView;
            pds.DataSource = ds.Tables[0].DefaultView;
            //允许分页
            pds.AllowPaging = true;
            //设置每页显示记录数
            pds.PageSize = int.Parse("6");
            //获取总页数
            pageCount = pds.PageCount;
            this.lblall.Text = pageCount.ToString();
            pds.CurrentPageIndex = currentPage - 1;
            //当前页
            this.lblcurrent.Text = Convert.ToString(currentPage);
            //数据绑定
            this.DataList1.DataSource = pds;
            this.DataList1.DataBind();
        }

        protected void ButSearch_Click(object sender, EventArgs e)
        {
            string query = textfield.Text.Trim();
            ds = room.GetList("Name like '%" + query + "%' or Are like '%" + query + "%' or Address like '%" + query + "%'and IfRecommend=1 and IfExamine=1 ");
            //DataList1.DataSource = ds;
            //DataList1.DataBind();
            //创建数据源
            PagedDataSource pds = new PagedDataSource();
            //ds.Tables[0].DefaultView;
            pds.DataSource = ds.Tables[0].DefaultView;
            //允许分页
            pds.AllowPaging = true;
            //设置每页显示记录数
            pds.PageSize = int.Parse("6");
            //获取总页数
            pageCount = pds.PageCount;
            this.lblall.Text = pageCount.ToString();
            pds.CurrentPageIndex = currentPage - 1;
            //当前页
            this.lblcurrent.Text = Convert.ToString(currentPage);
            //数据绑定
            this.DataList1.DataSource = pds;
            this.DataList1.DataBind();
        }
    }
}

