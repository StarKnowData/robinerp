using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;
using System.Data;
using Bzw.Data;
using System.Configuration;
using UiCommon;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_MatchApply2 : System.Web.UI.Page
    {
          protected global::System.Web.UI.HtmlControls.HtmlInputButton btnExit;
          protected global::System.Web.UI.HtmlControls.HtmlInputButton imageField2;
          protected global::System.Web.UI.WebControls.HiddenField hids;
          protected global::System.Web.UI.WebControls.HiddenField hide;
          protected global::System.Web.UI.WebControls.HiddenField hidIsApply;
          protected global::System.Web.UI.WebControls.Panel panShow;
          protected global::System.Web.UI.WebControls.Label lblMsg;
          protected global::System.Web.UI.WebControls.HiddenField hiduid;
          public string MatchID;
          public string MatchName;
          public string MatchSend;
          public string StartTime;
          public string EndTime;
          public string NeedMoney;
          public string MatchContent;
          public string MatchDate;
          public string LimitPeople;
          public DateTime ServerTime;
          public string JsServerTime, JsStartTime;
          protected void Page_Load(object sender, EventArgs e)
          {
              if (!UserLoginInfo.IsLogin)
              {
                  //判断是否从平台跳转过来的
                  string uid = CommonManager.Web.Request("userid", "");
                  string token = CommonManager.Web.Request("token", "");
                  if (CommonManager.String.IsInteger(uid) && token.Trim().Length > 0)
                  {
                      string un = new BLL.Member().GetNameByUserID(uid, token);
                      if (!string.IsNullOrEmpty(un))
                      {
                          UserLoginInfo.SetInfo(uid, un);

                      }
                      else
                      {
                          return;
                      }
                  }
              }
           if (Request.QueryString["id"] == null || !Utility.Common.IsNumber(Request.QueryString["id"]))
                  {
                      return;
                  }
           hiduid.Value = UiCommon.UserLoginInfo.UserID;
           
                  DataTable dt = DbSession.Default.FromSql("select top 1 * from Web_VTContestRoom where startTime>@NowDate and contestid=@ContestID order by StartTime")
                      .AddInputParameter("@NowDate", DbType.DateTime, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"))
                      .AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"])
                      .ToDataTable();
                  if (dt.Rows.Count > 0)
                  {
                      MatchID = dt.Rows[0]["ContestID"].ToString();
                      MatchName = dt.Rows[0]["ComName"].ToString();
                      StartTime = dt.Rows[0]["StartTime"].ToString();
                      EndTime = dt.Rows[0]["EndTime"].ToString();
                      MatchSend = dt.Rows[0]["AwardContent"].ToString();
                      NeedMoney = dt.Rows[0]["EntryFee"].ToString();
                      MatchContent = dt.Rows[0]["MatchContent"].ToString();
                      LimitPeople = dt.Rows[0]["UpPeople"].ToString();
                      hids.Value = StartTime;
                      hide.Value = MatchID;
                      DateTime dtime = Convert.ToDateTime(StartTime);
                      MatchDate = dtime.Month + " 月" + dtime.Day + " 日 " + dtime.ToString("HH:mm") + " - " + Convert.ToDateTime(EndTime).ToString("HH:mm");

                      int count = (int)DbSession.Default.FromSql("select count(1) from TContestUserRecord where userid=" + UiCommon.UserLoginInfo.UserID + " and contestid=" + MatchID + " and ContestCount=0").ToScalar();
                      if (count != 0)
                      {
                      //   imageField2.Disabled = true;
                         //  imageField2.Value = "已报名";
                       
                          imageField2.Style["display"] = "none";
                          btnExit.Style["display"] = "inline";
                          hidIsApply.Value = "1";
                      }
                      else
                      {
                          imageField2.Style["display"] = "inline";
                          btnExit.Style["display"] = "none";
                          hidIsApply.Value = "0";
                      }
                      ServerTime = Convert.ToDateTime(DbSession.Default.FromSql("SELECT GETDATE()").ToScalar());
                      JsServerTime = ServerTime.Year + "," + ServerTime.Month + "," + ServerTime.Day + "," + ServerTime.Hour + "," + ServerTime.Minute + "," + ServerTime.Second;
                      DateTime MatchStartTime = Convert.ToDateTime(StartTime);
                      JsStartTime = MatchStartTime.Year + "," + MatchStartTime.Month + "," + MatchStartTime.Day + "," + MatchStartTime.Hour + "," + MatchStartTime.Minute + "," + MatchStartTime.Second;
                      //int sendTypeID = Convert.ToInt32(dt.Rows[0]["SendTypeID"].ToString());
                      //DataTable dt2 = DbSession.Default.FromSql("select top 10 * from Web_MatchAwardConfig where TypeID=@TypeID order by Rank").AddInputParameter("@TypeID", DbType.Int32, sendTypeID).ToDataTable();
                      //if (dt2.Rows.Count > 0)
                      //{
                      //    rptAward.DataSource = dt2;
                      //    rptAward.DataBind();
                      //}

                  }
                  else
                  {
                      panShow.Visible = false;
                      // imageField2.Disabled = true;
                  }

                  dt.Clear();
              }
              
           
          ////报名
          //protected void button5_ServerClick(object sender, EventArgs e)
          //{
          //    if (Request.QueryString["id"] == null || !Utility.Common.IsNumber(Request.QueryString["id"]))
          //    {
          //        Response.Redirect("/MatchList.aspx");
          //    }
          //    DateTime dt1 = Convert.ToDateTime(hids.Value);
          //    if (DateTime.Compare(dt1, DateTime.Now) < 0)
          //    {
          //        lblMsg.Text = "抱歉，比赛已开始！";
          //        return;
                   
          //    }
              
          //    Dictionary<string, object> dic = new Dictionary<string, object>();
          //    DbSession.Default.FromProc("Web_pApplyMatch").AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
          //        .AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"].ToString())
          //        .AddReturnValueParameter("@ReturnValue", DbType.Int32)
          //       .Execute(out dic);
          //    if (dic.Count <= 0)
          //    {
          //        lblMsg.Text = "抱歉，报名失败，可能是服务器繁忙，请稍后再试！";
          //        return;
                  
          //    }

          //    if (dic["ReturnValue"].ToString() == "-1")
          //    {
          //        lblMsg.Text = "抱歉，报名失败，您的" + ConfigurationManager.AppSettings["moneyName"].ToString() + "不足！";
          //        return;
               
          //    }
          //    if (dic["ReturnValue"].ToString() == "-2")
          //    {
          //        lblMsg.Text = "已成功报名！";
          //        return;
               
          //    }
          //    lblMsg.Text = "报名成功！";
         
              
          //}
          ////退赛
          //protected void btnExit_ServerClick(object sender, EventArgs e)
          //{
          //    DateTime dt1 = Convert.ToDateTime(hids.Value);
          //    if (DateTime.Compare(dt1, DateTime.Now) < 0)
          //    {
          //        lblMsg.Text = "抱歉，比赛已开始，不能退赛！";
          //        return;
                
          //    }
          //    DbSession.Default.FromProc("Web_pExitMatch")
          //        .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
          //        .AddInputParameter("@ContestID", DbType.Int32, hide.Value)
          //        .Execute();
          //    lblMsg.Text = "退赛成功！";
              
          //}
    }
}
