using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web
{
    public partial class UserHandler : System.Web.UI.Page
    {
        public static Hashtable ht;
        public DataSet ds;
        QPS.BLL.Users Buser = new QPS.BLL.Users();
        QPS.Model.Users Muser = new QPS.Model.Users();
        QPS.BLL.Integral BInt = new QPS.BLL.Integral();
        static int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                ht = new Hashtable();
                if (Request.QueryString["action"] != null)
                {
                    string action = Request.QueryString["action"];
                    ht.Add("action", action);
                }
                if (Request.QueryString["username"] != null)
                {
                    string username = Request.QueryString["username"];
                    ht.Add("username", username);
                }
                if (Request.QueryString["password"] != null)
                {
                    string password = Request.QueryString["password"];
                    ht.Add("password", password);
                }
                if (Request.QueryString["newpassword"] != null)
                {
                    string newpassword = Request.QueryString["newpassword"];
                    ht.Add("newpassword", newpassword);
                }
                if (Request.QueryString["nickname"] != null)
                {
                    string nickname = Request.QueryString["nickname"];
                    ht.Add("nickname", nickname);
                }
                if (Request.QueryString["originalscore"] != null)
                {
                    string originalscore = Request.QueryString["originalscore"];
                    ht.Add("originalscore", originalscore);
                }
                if (Request.QueryString["score"] != null)
                {
                    string score = Request.QueryString["score"];
                    ht.Add("score", score);
                }
                if (Request.QueryString["sign"] != null)
                {
                    string sign = Request.QueryString["sign"];
                    ht.Add("sign", sign);
                }
                Response.Write(getResult(ht["action"].ToString()));
            }
        }
        public string getResult(string action)
        {
            switch (action)
            {
                case "register":
                    if (validate("register"))
                    {
                        Muser.Username = ht["username"].ToString();
                        Muser.Nickname = ht["nickname"].ToString();
                        Muser.Password = ht["password"].ToString();
                        Muser.Sign = "";
                        Muser.Usertype = 0;
                        if (Buser.Add(Muser) > 0)
                        {
                            return "true";
                        }
                        else
                        {
                            return "false";
                        }
                    }
                    else
                    {
                        return "false";
                    }
                case "login":
                    if (validate("login"))
                    {
                        if (Buser.Denglu(ht["username"].ToString(), ht["password"].ToString()))
                        {
                            Session["username"] = ht["username"].ToString();
                            return "true";
                        }
                        else
                        {
                            return "false";
                        }
                    }
                    else
                    {
                        return "false";
                    }
                case "score":
                    if (validate("score"))
                    {
                        string uname = ht["username"].ToString();
                        DataSet dsUser = Buser.GetList("Username='" + uname + "'");
                        userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                        QPS.Model.Integral  u = BInt.GetModel(userid);
                        if (u.Content == (int)ht["originalscore"])
                        {
                            u.Content = +(int)ht["score"];
                            if (BInt.Update(u))
                            {
                                return "true";
                            }
                            else
                                return "fales";
                        }
                        else
                        {
                            return "false";
                        }
                    }
                    else { return "false"; }
                case "editpwd":
                    if (validate("editpwd"))
                    {
                        string uname = ht["username"].ToString();
                        DataSet dsUser = Buser.GetList("Username='" + uname + "'");
                        userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                        QPS.Model.Users u = Buser.GetModel(userid);
                        u.Password = ht["newpassword"].ToString();
                        if (Buser.Update(u))
                        {
                            return "true";
                        }
                        else
                        {
                            return "false";
                        }
                    }
                    else { return "false"; }
                case "logout":
                    if (validate("logout"))
                    {
                        if (Session["username"] != null)
                        {
                            Session.Remove("username");
                            return "true";
                        }
                        else
                        {
                            return "false";
                        }
                    }
                    else
                    {
                        return "false";
                    }
                default: return "false";
            }
        }
        public bool validate(string action)
        {
            StringBuilder sbsign = new StringBuilder();
            string sign = ht["sign"].ToString();
            switch (action)
            {
                case "login":
                    string logkey = "14efe3a1820b457b95da41b70fdfebc9";
                    sbsign.Append("action=");
                    sbsign.Append(action);
                    sbsign.Append("&username=");
                    sbsign.Append(ht["username"].ToString());
                    sbsign.Append("&password=");
                    sbsign.Append(ht["password"].ToString());
                    sbsign.Append("&key=");
                    sbsign.Append(logkey);
                    break;
                case "register":
                    string regkey = "48c93e18ffbe4878b344cc1749ff6dc8";
                    sbsign.Append("action=");
                    sbsign.Append(action);
                    sbsign.Append("&username=");
                    sbsign.Append(ht["username"].ToString());
                    sbsign.Append("&password=");
                    sbsign.Append(ht["password"].ToString());
                    sbsign.Append("&nickname=");
                    sbsign.Append(ht["nickname"].ToString());
                    sbsign.Append("&key=");
                    sbsign.Append(regkey);
                    break;
                case "editpwd":
                    string pwdKey = "dfd8915f711b45c78c2b15ef70528699";
                    sbsign.Append("action=");
                    sbsign.Append(action);
                    sbsign.Append("&username=");
                    sbsign.Append(ht["username"].ToString());
                    sbsign.Append("&newpassword=");
                    sbsign.Append(ht["newpassword"].ToString());
                    sbsign.Append("&key=");
                    sbsign.Append(pwdKey);
                    break;
                case "logout":
                    string logoutKey = "245454123b0d45c8b89cfc4748b7cb7c";
                    sbsign.Append("action=");
                    sbsign.Append(action);
                    sbsign.Append("&key=");
                    sbsign.Append(logoutKey);
                    break;
            }
            string newsign = System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile(sbsign.ToString(), "MD5").ToLower();
            if (sign == newsign)
            {
                return true;
            }
            else
                return false;
        }
    }
}

