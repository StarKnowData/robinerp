using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Bzw.Data;
using System.Data;

 
    public partial class Admin_Users_User_Lock : AdminBasePage
    {
      static  string limitid="0";
      static string limitip = "0";
      static string limitmcode = "0";
      static string limithard = "0";
        string userid = "";
        string ip = "";
        string mcode = "";
        string hard = "";
        protected void Page_Load(object sender, EventArgs e)
        {
           
                AdminPopedom.IsHoldModel("04");
                if (!IsPostBack)
                {
                    if (!string.IsNullOrEmpty(Request.QueryString["limitID"]) && Request.QueryString["limitID"] == "1")
                    {
                        chkID.Checked = true;
                        limitid = "1";
                    }

                    if ((!string.IsNullOrEmpty(Request.QueryString["limitIP"])) && Convert.ToBoolean(Request.QueryString["limitIP"]))
                    {

                        chkIP.Checked = true;
                        limitip = "1";
                    }
                    if ((!string.IsNullOrEmpty(Request.QueryString["limitMcode"])) && Convert.ToBoolean(Request.QueryString["limitMcode"]))
                    {
                        chkMcode.Checked = true;
                        limitmcode = "1";
                    }
                    if ((!string.IsNullOrEmpty(Request.QueryString["limitHard"])) && Convert.ToBoolean(Request.QueryString["limitHard"]))
                    {
                        chkHard.Checked = true;
                        limithard = "1";
                    }

                }   
 
        }

        protected void btnSure_Click(object sender, EventArgs e)
        {
            string strid = (chkID.Checked) ? "1" : "0";
            string strip = (chkIP.Checked) ? "1" : "0";
            string strmcode = (chkMcode.Checked) ? "1" : "0";
            string strhard = (chkHard.Checked) ? "1" : "0";
            userid = Request.QueryString["uid"];

            ip = Request.QueryString["ip"];
            mcode = Request.QueryString["m"];
            hard = Request.QueryString["h"];
            string strMsg = "";
            if (limitid != strid)
            {
            //    Response.Write(limitid + ":" + strid + ":" + userid);
                Utility.SqlHelper.ExecuteNonQuery( CommandType.Text,"update tusers set [disabled]=" + strid+" where userid="+userid);
                strMsg += "<br/>帐号修改成功！";
            }
            if (limitip != strip)
            {
                if ((int)DbSession.Default.FromSql("select count(*) from TGameIPRule where AccessIPChar='" + ip + "'").ToScalar() > 0)
                {
                    Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, "update TGameIPRule set LimitedLogon=" + strip + " ,OverTime='"+DateTime.Now.AddYears(10)+"' where AccessIPChar='" + ip + "'");
                }
                else
                {
                    Utility.SqlHelper.ExecuteNonQuery(CommandType.Text,"insert into TGameIPRule(AccessIPChar,LimitedLogon,OverTime) values('" + ip + "'," + strip + ",'"+DateTime.Now.AddYears(10)+"')");
                }
                strMsg += "<br/>IP修改成功！";
            }
          if (limitmcode != strmcode)
            {
                if (strmcode == "1")
                {
                    if (mcode == "")
                    {
                        Response.Write("不能为空！");
                        Response.End();
                    }
                    Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, "insert into TLockCode(LockCode,LockHard) values('" + mcode + "','')");
                }
                else
                {
                    Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, "delete from TLockCode  where LockCode='" + mcode + "'");
                }
                strMsg += "<br/>机器码修改成功！";
            }
          if (limithard != strhard)
          {
              if (strhard == "1")
              {
                  if (hard.Replace('*', '\\') == "")
                  {
                      Response.Write("不能为空！");
                      Response.End();
                  }
                  Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, "insert into TLockCode(LockCode,LockHard) values('','"+hard.Replace('*','\\')+"')");
              }
              else
              {
                  Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, "delete from TLockCode  where LockHard='" + hard.Replace('*','\\') + "'");
              }
              strMsg += "<br/>硬盘编码修改成功！";
          }
            limitid = "0";
            limitip = "0";
            limitmcode = "0";
            limithard = "0";
            Response.Write(strMsg);
            Response.End();
        }
    }
 
