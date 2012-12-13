using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;

namespace QPS.Web
{
    public partial class RoomDetail : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Room room = new QPS.NEW.BLL.Room();
        QPS.NEW.BLL.Poster poster = new QPS.NEW.BLL.Poster();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                int id = Int32.Parse(Request.QueryString["id"].Trim());
                StringBuilder sb = new StringBuilder();
                sb.Append("Id=");
                sb.Append(id);
                ds = room.GetList(sb.ToString());
                DataList2.DataSource = ds;
                DataList2.DataBind();
                DataList1.DataSource = ds;
                DataList1.DataBind();
                //DataSet recommendds = room.GetList(5, "IfRecommend=1", "RecommendTime");
                //Dlrecommand.DataSource = recommendds;
                //Dlrecommand.DataBind();
                //DataList3.DataSource = poster.GetList("");
                //DataList3.DataBind();
            }
        }
        protected void DataList1_ItemCommand(object source, DataListCommandEventArgs e)
        {

            if (e.CommandName == "Order")
            {
                if (Session["username"] == null)
                {
                    Response.Write("<script>alert('请先登录,预定失败！')</script>");
                    //    string c="<script language=javascript><!--var LiveAutoInvite0 = '您好，来自%IP%的朋友';        var LiveAutoInvite1 = '来自首页的对话';  var LiveAutoInvite2 = ' 网站商务通 主要功能：<br>1、主动邀请<br>2、即时沟通<br>3、查看即时访问动态<br>4、访问轨迹跟踪<br>5、内部对话<br>6、不安装任何插件也实现双向文件传输<br><br><b>如果您有任何问题请接受此邀请以开始即时沟通</b>';src='http://dgt.zoosnet.net/JS/LsJS.aspx?siteid=DGT32500128&float=1'></script>";
                    //Response.Write(c);
                    return;
                }
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("Order.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }
        protected void dlrecommand_ItemCommand(object source, DataListCommandEventArgs e)
        {

            if (e.CommandName == "ShowDetail")
            {
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("Detail.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }
    }
}
