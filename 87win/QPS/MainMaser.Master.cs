using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Collections;
namespace QPS.Web
{
    public partial class MainMaser : System.Web.UI.MasterPage
    {          
        private static  Hashtable    _hashtable;
        public Hashtable hashtable
        {
            set { _hashtable = value; }
            get { return _hashtable; }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session["username"] == null)
                {
                    unLog.Visible = true;
                    userLoginfo.Visible = false;
                    this.Panel1.Visible = false;
                }
                if (Session["username"] != null)
                {
                    Label1.Text = Session["username"].ToString();
                    unLog.Visible = false;
                    userLoginfo.Visible = true;
                    Panel1.Visible = true;
                }
            }
        }
        protected void LinkButton1_Click(object sender, EventArgs e)
        {
            string username = hashtable["username"].ToString();
            string password = hashtable["password"].ToString();
            string key = "14efe3a1820b457b95da41b70fdfebc9";
            DataHandler.PostService ps = new DataHandler.PostService();
            ps.Url = "http://59.175.238.107:8080/UserHandler.aspx";//接口地址
            string _tmp = "action=login&username=" + username + "&password=" + password + "&key=" + key;
            string sign = System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile(_tmp, "md5").ToLower();
            ps.Add("username", username);//用户名
            ps.Add("password", password);//密码
            ps.Add("sign", sign);//签名验证
            ps.Add("action", "login");//登录
            ps.Add("url", "http://59.175.238.107:8080/Manage/Default.aspx");//登录成功后，跳转地址
            ps.Post();
        }
    }
}
