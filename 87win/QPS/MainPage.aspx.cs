using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using System.Data;
using System.Collections;
using System.Data.SqlClient;
namespace QPS.Web
{
    public partial class MainPage : System.Web.UI.Page
    {
        QPS.BLL.Trends Btrend = new QPS.BLL.Trends();
        QPS.BLL.Room room = new QPS.BLL.Room();
        private static Hashtable _hashtable;
        public Hashtable hashtable
        {
            set { _hashtable = value; }
            get { return _hashtable; }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                DataSet recommendds = Btrend.GetTopList (7);
                Dlrecommand.DataSource = recommendds;
                Dlrecommand.DataBind();
                //DataList1.DataSource=  room.GetAllList();
                //DataList1.DataBind();
                this.GetRecommendRoom();
            }
        }


        private void GetRecommendRoom()
        {
            string tempstr = string.Empty;
            QPS.BLL.Room room = new QPS.BLL.Room();
            DataTable dt = room.GetDataTableList("select top 50 * from Room where IfRecommend=0 order by id desc");
            if (dt!=null)
            {
                for (int i = 0; i < dt.Rows.Count;i++ )
                {
                    tempstr += "<li><span><a href=\"RoomDetail.aspx?id=" + dt.Rows[i]["id"].ToString() + "\"><img src=\"/" + dt.Rows[i]["ImagePath"].ToString() + "\" alt=\"" + dt.Rows[i]["Name"].ToString() + "\"></a></span><p><a href=\"RoomDetail.aspx?id=" + dt.Rows[i]["id"].ToString() + "\">" + dt.Rows[i]["Name"].ToString() + "</a></p></li>\r\n";
                }
            }
            this.RecommendRoom.Text = tempstr;
        }


        protected void dlrecommand_ItemCommand(object source, DataListCommandEventArgs e)
        {
            if (e.CommandName == "ShowDetail")
            {
                Dlrecommand.Enabled = true;
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("NewsDatail.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }

        protected void LinkButton1_Click(object sender, EventArgs e)
        {
            string username = hashtable["username"].ToString();
            string password = hashtable["password"].ToString();
            string key = "14efe3a1820b457b95da41b70fdfebc9";
            DataHandler.PostService ps = new DataHandler.PostService();
            ps.Url = "http://game.87win.cn/UserHandler.aspx";//接口地址
            string _tmp = "action=login&username=" + username + "&password=" + password + "&key=" + key;
            string sign = System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile(_tmp, "md5").ToLower();
            ps.Add("username", username);//用户名
            ps.Add("password", password);//密码
            ps.Add("sign", sign);//签名验证
            ps.Add("action", "login");//登录
            ps.Add("url", "http://game.87win.cn/Manage/Default.aspx");//登录成功后，跳转地址
            ps.Post();
        }

        protected void LinkButton2_Click(object sender, EventArgs e)
        {

        }

        protected void Dlrecommand_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
